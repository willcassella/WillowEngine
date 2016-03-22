// Union.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <limits>
#include <algorithm>
#include "../STDE/Utility.h"
#include "../Memory/Buffers/StaticBuffer.h"

template <typename ... T>
struct Union final
{
	///////////////////////
	///   Inner Types   ///
private:

	/** Honestly if you need a Union of more than 255 types you're doing something wrong. */
	using Descriminant = byte;

	/** Aliasis a type_sequence holding the types supported by this Union. */
	using Seq = stde::type_sequence<T...>;

	static_assert(sizeof...(T) <= std::numeric_limits<Descriminant>::max(), "You have too many types in this Union.");

	////////////////////////
	///   Constructors   ///
public:

	Union()
		: _descriminant(0)
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
	Union(const Union&& move)
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
		return _descriminant != 0;
	}

	/** Returns whether the currently held value is an instance of the given type. */
	template <typename F>
	bool HasInstanceOf() const
	{
		return this->HasValue() && _descriminant == Union::DescriminantOf<F>();
	}

	template <typename F>
	bool GetValue(F& out) &
	{
		return Union::GetValueImpl(*this, out);
	}

	template <typename F>
	bool GetValue(F& out) const &
	{
		return Union::GetValueImpl(*this, out);
	}

	template <typename F>
	bool GetValue(F& out) &&
	{
		return Union::GetValueImpl(std::move(*this), out);
	}

	template <typename F>
	bool GetValue(F& out) const &&
	{
		return Union::GetValueImpl(std::move(*this), out);
	}

	/** Gets the current value of this Union as the given type.
	* WARNING: This function will fail if this Variant is not currently holding a value of the given type. */
	template <typename F>
	F& GetValue() &
	{
		assert(this->HasValue() && _descriminant == Union::DescriminantOf<F>());
		return this->FastGet<F>();
	}

	/** Gets the current value of this Union as the given type.
	* WARNING: This function will fail if this Variant is not currently holding a value of the given type. */
	template <typename F>
	const F& GetValue() const &
	{
		assert(this->HasValue() && _descriminant == Union::DescriminantOf<F>());
		return this->FastGet<F>();
	}

	/** Since this is a temporary object, you couldn't have possibly checked if it contains a value. */
	template <typename F>
	void GetValue() const && = delete;

	/** Sets the current value of this Union. */
	template <typename F>
	void SetValue(F&& value)
	{
		using DecayedF = std::decay_t<F>;
		constexpr auto newDescriminant = Union::DescriminantOf<F>();
		static_assert(newDescriminant != 0, "The given type does not exist in this Union.");

		// If we have a currently loaded value
		if (this->HasValue())
		{
			// If the currently loaded value is of the same type as the new value
			if (_descriminant == newDescriminant)
			{
				// Just assign directly
				this->FastGet<DecayedF>() = std::forward<F>(value);
				return;
			}
			else
			{
				// Delete current value
				this->Nullify();
			}
		}

		_buffer.template Emplace<DecayedF>(std::forward<F>(value));
		_descriminant = newDescriminant;
	}

	/** Invokes the given function on the current value.
	* Returns whether the given function was invoked. */
	template <typename FuncT>
	bool Invoke(FuncT&& func) &
	{
		return Union::InvokeImpl(*this, std::forward<FuncT>(func));
	}

	/** Invokes the given function on the current value.
	* Returns whether the given function was invoked. */
	template <typename FuncT>
	bool Invoke(FuncT&& func) const &
	{
		return Union::InvokeImpl(*this, std::forward<FuncT>(func));
	}

	/** Invokes the given function on the current value.
	* Returns whether the given function was invoked. */
	template <typename FuncT>
	bool Invoke(FuncT&& func) &&
	{
		return Union::InvokeImpl(std::move(*this), std::forward<FuncT>(func));
	}

	/** Invokes the given function on the current value.
	* Returns whether the given function was invoked. */
	template <typename FuncT>
	bool Invoke(FuncT&& func) const &&
	{
		return Union::InvokeImpl(std::move(*this), std::forward<FuncT>(func));
	}

	/** Invokes the given function on the currently held instance of 'F', if it exists.
	* Returns whether the given function was invoked. */
	template <typename F, typename FuncT>
	bool InvokeFor(FuncT&& func) &
	{
		return Union::InvokeForImpl(*this, std::forward<FuncT>(func));
	}

	/** Invokes the given function on the currently held instance of 'F', if it exists.
	* Returns whether the given function was invoked. */
	template <typename F, typename FuncT>
	bool InvokeFor(FuncT&& func) const &
	{
		return Union::InvokeForImpl(*this, std::forward<FuncT>(func));
	}

	/** Invokes the given function on the currently held instance of 'F', if it exists.
	* Returns whether the given function was invoked. */
	template <typename F, typename FuncT>
	bool InvokeFor(FuncT&& func) &&
	{
		return Union::Invoke(std::move(*this), std::forward<FuncT>(func));
	}

	/** Invokes the given function on the currently held instance of 'F', if it exists.
	* Returns whether the given function was invoked. */
	template <typename F, typename FuncT>
	bool InvokeFor(FuncT&& func) const &&
	{
		return Union::Invoke(std::move(*this), std::forward<FuncT>(func));
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
		_descriminant = 0;
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

	/** Implements the 'GetValue' method for various types of 'this'. */
	template <typename ThisT, typename F>
	static bool GetValueImpl(ThisT&& self, F& out)
	{
		if (self.HasValue() && self._descriminant == Union::DescriminantOf<F>())
		{
			out = stde::forward_like<ThisT>(self.template FastGet<std::decay_t<F>>());
			return true;
		}
		else
		{
			return false;
		}
	}

	/** Implements the 'Invoke' method for various types of 'this'. */
	template <typename ThisT, typename FuncT>
	static bool InvokeImpl(ThisT&& self, FuncT&& func)
	{
		using VoidT = stde::copy_cv_t<ThisT, void>*;
		using Invoker = void(VoidT, FuncT&&);
		Invoker* const invokers[] = { Union::CreateNoOpInvoker<VoidT, FuncT>(), Union::CreateInvoker<VoidT, FuncT, stde::copy_qualifiers_t<ThisT&&, T>>()... };

		invokers[self._descriminant](self._buffer.GetPointer(), std::forward<FuncT>(func));
		return self.HasValue();
	}

	/** Implements the 'InvokeFor' method for various types of 'this'. */
	template <typename ThisT, typename F, typename FuncT>
	static bool InvokeForImpl(ThisT&& self, FuncT&& func)
	{
		if (self.template HasInstanceOf<F>())
		{
			std::forward<FuncT>(func)(stde::forward_like<ThisT>(self.template FastGet<F>()));
			return true;
		}
		else
		{
			return false;
		}
	}

	/** Creates a function that invokes a function of the given type ("Func") on a type-erased instance of "F".
	* Used by the "Invoke" method. */
	template <typename VoidT, typename FuncT, typename F>
	static auto CreateInvoker()
	{
		// COMPILER NOTE: I would have made this a generic lambda, but for whatever reason (still trying to figure it out) most compilers just CANNOT handle
		// Passing generic lambdas around in the way I'd like to. Even worse, support seems to be extremely sporadic (works on Clang 3.6, but not 3.7)
		// If it had been supported, the template signature for this funtion would be 'template <typename F>', and the signature for this lambda would be
		// (auto arg, auto&& func).
		return [](VoidT arg, FuncT&& func)
		{
			std::forward<FuncT>(func)(stde::static_ptr_to_ref<F>(arg));
		};
	}

	/** Creates a function that does nothing with its arguments.
	* Used by the "Invoke" method. */
	template <typename VoidT, typename FuncT>
	static auto CreateNoOpInvoker()
	{
		return [](VoidT /*arg*/, FuncT&& /*func*/)
		{
			// Do nothing
		};
	}

	/** Returns the descriminant for the given type. */
	template <typename S>
	static constexpr Descriminant DescriminantOf()
	{
		return Union::DescriminantOf<std::decay_t<S>>(1, Seq{});
	}

	/** Recursively finds the descriminant for the given type. */
	template <typename S, typename C, typename ... F>
	static constexpr Descriminant DescriminantOf(Descriminant current, stde::type_sequence<C, F...>)
	{
		return std::is_same<S, C>::value ? current : Union::DescriminantOf<S>(current + 1, stde::type_sequence<F...>{});
	}

	/** End case, type does not exist in this Union. */
	template <typename S>
	static constexpr Descriminant DescriminantOf(Descriminant /*current*/, stde::type_sequence<>)
	{
		return 0;
	}

	/** Returns the size of the largest type among the types suppored by this Union. */
	template <typename F, typename ... MoreF>
	static constexpr std::size_t GetMaxSize(stde::type_sequence<F, MoreF...>)
	{
		return std::max(sizeof(F), Union::GetMaxSize(stde::type_sequence<MoreF...>{}));
	}

	/** Returns the size of the largest type among the types suppored by this Union. */
	static constexpr std::size_t GetMaxSize(stde::type_sequence<>)
	{
		return 0;
	}

	/** Returns the maximum alignment among the types supported by this Union. */
	template <typename F, typename ... MoreF>
	static constexpr std::size_t GetMaxAlignment(stde::type_sequence<F, MoreF...>)
	{
		return std::max(alignof(F&), Union::GetMaxAlignment(stde::type_sequence<MoreF...>{}));
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
			if (!copy.Invoke([this](auto& value) { this->SetValue(value); }))
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
			if (!copy.Invoke([this](const auto& value) { this->SetValue(value); }))
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
			if (!std::move(move).Invoke([this](auto&& value) { this->SetValue(std::move(value)); }))
			{
				this->Nullify();
			}
		}

		return *this;
	}
	Union& operator=(const Union&& move)
	{
		if (this != &move)
		{
			if (!std::move(move).Invoke([this](const auto&& value) { this->SetValue(std::move(value)); }))
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

	/** Performs an equality comparison on two Unions.
	* NOTE: If the two Unions contain different types, this returns 'false'. */
	friend bool operator==(const Union& lhs, const Union& rhs)
	{
		bool result = false;

		// Invoke the comparison operator if both unions contain the same type.
		// Note that we don't have to check for the null descriminant, since the function will not be invoked at all in that case
		if (lhs._descriminant == rhs._descriminant)
		{
			lhs.Invoke([&](const auto& value)
			{
				result = (value == rhs.GetValue<decltype(value)>());
			});
		}

		return result;
	}

	/** Performs an inequality comparison on two Unions.
	* NOTE: If the two Unions contain different types, this returns 'false'. */
	friend bool operator!=(const Union& lhs, const Union& rhs)
	{
		bool result = false;

		// Invoke the comparison operator if both unions contain the same type.
		// Note that we don't have to check for the null descriminant, since the function will not be invoked at all in that cases
		if (lhs._descriminant == rhs._descriminant)
		{
			lhs.Invoke([&](const auto& value)
			{
				result = (value != rhs.GetValue<decltype(value)>());
			});
		}

		return result;
	}

	////////////////
	///   Data   ///
private:

	// For some reason, ONLY ON MSVC, I have to store these as a static constexpr variable,
	// rather than just putting the function call directly into the template
	static constexpr std::size_t Size = GetMaxSize(Seq{});
	static constexpr std::size_t Alignment = GetMaxAlignment(Seq{});

	Descriminant _descriminant;
	StaticBuffer<Size, Alignment> _buffer;
};
