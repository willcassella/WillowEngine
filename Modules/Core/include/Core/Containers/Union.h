// Union.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <limits>
#include <algorithm>
#include "../STDE/TypeTraits.h"
#include "../Memory/Buffers/StaticBuffer.h"

template <typename ... T>
struct Union final
{
	///////////////////////
	///   Inner Types   ///
private:

	/** Honestly if you need a Union of more than 255 types you're doing something wrong. */
	using Index = byte;

	/** Aliasis a type_sequence holding the types supported by this Union. */
	using Seq = stde::type_sequence<T...>;

	static_assert(sizeof...(T) <= std::numeric_limits<Index>::max(), "You have too many types in this Union.");

	////////////////////////
	///   Constructors   ///
public:

	Union()
		: _index(0)
	{
		// All done
	}
	Union(Union& copy)
		: Union()
	{
		*this = copy;
	}
	Union(const Union& copy)
		: Union()
	{
		*this = copy;
	}
	Union(Union&& move)
		: Union()
	{
		*this = std::move(move);
	}
	~Union()
	{
		this->Nullify();
	}

	template <typename F>
	Union(F&& value)
		: Union()
	{
		this->SetValue(std::forward<F>(value));
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns whether this Union is currently holding a value. */
	FORCEINLINE bool HasValue() const
	{
		return _index != 0;
	}

	template <typename F>
	bool GetValue(F& out) &
	{
		if (_index == IndexOf<F>())
		{
			out = this->FastGet<F>();
			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename F>
	bool GetValue(F& out) const &
	{
		if (_index == IndexOf<F>())
		{
			out = this->FastGet<F>();
			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename F>
	bool GetValue(F& out) &&
	{
		if (_index == IndexOf<F>())
		{
			out = std::move(this->FastGet<F>());
			return true;
		}
		else
		{
			return false;
		}
	}

	/** Gets the current value of this Union as the given type.
	* WARNING: This function will fail if this Variant is not currently holding a value of the given type. */
	template <typename F>
	F& GetValue() &
	{
		assert(_index == IndexOf<F>());
		return this->FastGet<F>();
	}

	/** Gets the current value of this Union as the given type.
	* WARNING: This function will fail if this Variant is not currently holding a value of the given type. */
	template <typename F>
	const F& GetValue() const &
	{
		assert(_index == IndexOf<F>());
		return this->FastGet<F>();
	}

	/** Since this is a temporary object, you couldn't have possibly checked if it contains a value. */
	template <typename F>
	F&& GetValue() && = delete;

	/** Sets the current value of this Union. */
	template <typename F>
	void SetValue(F&& value)
	{
		using DecayF = std::decay_t<F>;
		constexpr auto newIndex = IndexOf<DecayF>();

		// If we have a currently loaded value
		if (this->HasValue())
		{
			// If the currently loaded value is of the same type as the new value
			if (_index == newIndex)
			{
				// Just assign directly
				this->FastGet<DecayF>() = std::forward<F>(value);
				return;
			}
			else
			{
				// Delete current value
				this->Nullify();
			}
		}

		_buffer.template Emplace<DecayF>(std::forward<F>(value));
		_index = newIndex;
	}

	/** Invokes the given function on the current value.
	* Returns whether the given function was invoked. */
	template <typename FuncT>
	bool Invoke(FuncT&& func) &
	{
		using Invoker = void(void*, FuncT&&);
		Invoker* const invokers[] = { CreateNoOpInvoker<void*, FuncT>(), CreateInvoker<T&, void*, FuncT>()... };

		invokers[_index](_buffer.GetPointer(), std::forward<FuncT>(func));
		return this->HasValue();
	}

	/** Invokes the given function on the current value.
	* Returns whether the given function was invoked. */
	template <typename FuncT>
	bool Invoke(FuncT&& func) const &
	{
		using Invoker = void(const void*, FuncT&&);
		Invoker* const invokers[] = { CreateNoOpInvoker<const void*, FuncT>(), CreateInvoker<const T&, const void*, FuncT>()... };

		invokers[_index](_buffer.GetPointer(), std::forward<FuncT>(func));
		return this->HasValue();
	}

	/** Invokes the given function on the current value.
	* Returns whether the given function was invoked. */
	template <typename FuncT>
	bool Invoke(FuncT&& func) &&
	{
		using Invoker = void(void*, FuncT&&);
		Invoker* const invokers[] = { CreateNoOpInvoker<void*, FuncT>(), CreateInvoker<T&&, void*, FuncT>()... };

		invokers[_index](_buffer.GetPointer(), std::forward<FuncT>(func));
		return this->HasValue();
	}

	/** Invokes the given function on the currently held instance of 'F', if it exists.
	* Returns whether the given function was invoked. */
	template <typename F, typename FuncT>
	bool InvokeFor(FuncT&& func) &
	{
		if (_index == IndexOf<F>())
		{
			std::forward<FuncT>(func)(this->FastGet<F>());
			return true;
		}
		else
		{
			return false;
		}
	}

	/** Invokes the given function on the currently held instance of 'F', if it exists.
	* Returns whether the given function was invoked. */
	template <typename F, typename FuncT>
	bool InvokeFor(FuncT&& func) const &
	{
		if (_index == IndexOf<F>())
		{
			std::forward<FuncT>(func)(this->FastGet<F>());
			return true;
		}
		else
		{
			return false;
		}
	}

	/** Invokes the given function on the currently held instance of 'F', if it exists.
	* Returns whether the given function was invoked. */
	template <typename F, typename FuncT>
	bool InvokeFor(FuncT&& func) &&
	{
		if (_index == IndexOf<F>())
		{
			std::forward<FuncT>(func)(std::move(this->FastGet<F>()));
			return true;
		}
		else
		{
			return false;
		}
	}

	/** Destroys the currently held value. */
	void Nullify()
	{
		// Invoke the destructor
		this->Invoke([](auto& v)
		{
			using F = std::decay_t<decltype(v)>;
			v.~F();
		});
		_index = 0;
	}

private:

	template <typename F>
	FORCEINLINE F& FastGet()
	{
		return *_buffer.template GetPointer<F>();
	}

	template <typename F>
	FORCEINLINE const F& FastGet() const
	{
		return *_buffer.template GetPointer<F>();
	}

	/** Returns the index of the given type. */
	template <typename S>
	static constexpr Index IndexOf()
	{
		static_assert(Seq::template contains<S>(), "The given type does not exist in this Union.");
		return IndexOf<S>(1, Seq());
	}

	/** Recursively finds the index of the given type. */
	template <typename S, typename C, typename ... F>
	static constexpr Index IndexOf(Index current, stde::type_sequence<C, F...>)
	{
		return std::is_same<S, C>::value ? current : IndexOf<S>(current + 1, stde::type_sequence<F...>());
	}

	/** End case, never actually reached. */
	template <typename S>
	static constexpr Index IndexOf(Index /*current*/, stde::type_sequence<>)
	{
		return 0;
	}

	/** Creates a function that invokes a function of the given type ("Func") on a type-erased instance of "F".
	* Used by the "Invoke" method. */
	template <typename F, typename EraseT, typename FuncT>
	static auto CreateInvoker()
	{
		return [](EraseT arg, FuncT&& func)
		{
			std::forward<FuncT>(func)(std::forward<F>(*static_cast<std::remove_reference_t<F>*>(arg)));
		};
	}

	/** Creates a function that does nothing with its arguments.
	* Used by the "Invoke" method. */
	template <typename EraseT, typename FuncT>
	static auto CreateNoOpInvoker()
	{
		return [](EraseT /*arg*/, FuncT&& /*func*/)
		{
			// Do nothing
		};
	}

	/** Returns the size of the largest type among the types suppored by this Union. */
	static constexpr std::size_t GetMaxSize()
	{
		return GetMaxSize(Seq());
	}

	/** Returns the size of the largest type among the types suppored by this Union. */
	template <typename F, typename ... MoreF>
	static constexpr std::size_t GetMaxSize(stde::type_sequence<F, MoreF...>)
	{
		return std::max(sizeof(F), GetMaxSize(stde::type_sequence<MoreF...>{}));
	}

	/** Returns the size of the largest type among the types suppored by this Union. */
	static constexpr std::size_t GetMaxSize(stde::type_sequence<>)
	{
		return 0;
	}

	/** Returns the maximum alignment among the types supported by this Union. */
	static constexpr std::size_t GetMaxAlignment()
	{
		return GetMaxAlignment(Seq());
	}

	/** Returns the maximum alignment among the types supported by this Union. */
	template <typename F, typename ... MoreF>
	static constexpr std::size_t GetMaxAlignment(stde::type_sequence<F, MoreF...>)
	{
		return std::max(alignof(F), GetMaxAlignment(stde::type_sequence<MoreF...>{}));
	}

	/** Returns the maximum alignment among the types supported by this Union. */
	static constexpr std::size_t GetMaxAlignment(stde::type_sequence<>)
	{
		return 0;
	}

	/////////////////////
	///   Operators   ///
public:

	Union& operator=(Union& copy)
	{
		if (this != &copy)
		{
			if (copy.HasValue())
			{
				// Copy the value
				copy.Invoke([this](auto& value)
				{
					this->SetValue(value);
				});
			}
			else
			{
				this->Nullify();
			}
		}

		return *this;
	}
	Union& operator=(const Union& copy)
	{
		if (this != &copy)
		{
			if (copy.HasValue())
			{
				// Copy the value
				copy.Invoke([this](const auto& value)
				{
					this->SetValue(value);
				});
			}
			else
			{
				this->Nullify();
			}
		}

		return *this;
	}
	Union& operator=(Union&& move)
	{
		if (this != &move)
		{
			if (move.HasValue())
			{
				// Move the value
				std::move(move).Invoke([this](auto&& value) -> void
				{
					this->SetValue(std::move(value));
				});
			}
			else
			{
				this->Nullify();
			}
		}

		return *this;
	}

	template <typename F>
	Union& operator=(F&& value)
	{
		this->SetValue(std::forward<F>(value));
		return *this;
	}

	////////////////
	///   Data   ///
private:

	// For some reason, ONLY ON MSVC< I have to store this as a static constexpr variable,
	// rather than just putting "GetMaxSize()" into the StaticBuffer size
	static constexpr std::size_t Size = GetMaxSize();
	static constexpr std::size_t Alignment = GetMaxAlignment();

	Index _index;
	StaticBuffer<Size, Alignment> _buffer;
};
