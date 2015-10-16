// Union.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Forwards/Reflection.h"
#include "../Math/Math.h"
#include "Nullable.h"

template <typename ... T>
struct Union final
{
	///////////////////////
	///   Inner Types   ///
private:

	/** Honestly if you need a Union of more than 255 types you're doing something wrong. */
	using Index = byte;

	/** Aliasis a type_sequence holding the types supported by this Union. */
	using Seq = stdEXT::type_sequence<T...>;

	////////////////////////
	///   Constructors   ///
public:

	Union() = default;
	Union(const Union& copy)
		: Union()
	{
		self = copy;
	}
	Union(Union&& move)
		: Union()
	{
		self = std::move(move);
	}
	~Union()
	{
		Nullify();
	}

	template <typename F>
	Union(F&& value)
		: Union()
	{
		Set(std::forward<F>(value));
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns whether this Union is currently holding a value. */
	FORCEINLINE bool HasValue() const
	{
		return _index.HasValue();
	}

	/** Returns the type of the currently heald value.
	* NOTE: Returns 'null' if this Union is not currently holding a value. */
	const TypeInfo* GetCurrentType() const
	{
		if (_index.HasValue())
		{
			return Invoke<const TypeInfo*>([](const auto& a) { return &TypeOf(a); });
		}
		else
		{
			return nullptr;
		}
	}

	/** Destroys the currently held value. */
	void Nullify()
	{
		if (HasValue())
		{
			// Destroy the value
			Invoke([](auto& v) -> void
			{
				using F = std::decay_t<decltype(v)>;
				v.~F();
			});
			_index.Nullify();
		}
	}

	/** Returns the current value as a Variant. 
	* WARNING: This function will fail if this Variant is not currently holding a value. */
	Variant Get();

	/** Returns the current value as an ImmutableVariant. 
	* WARNING: This function will fail if this Variant is not currently holding a value. */
	ImmutableVariant Get() const;

	/** Sets the current value of this Union. */
	template <typename F>
	void Set(F&& value)
	{
		Index newIndex = IndexOf<F>();

		// If we have a currently loaded value
		if (_index.HasValue())
		{
			// If the currently loaded value is of the same type as the new value
			if (_index.GetValue() == newIndex)
			{
				// Just assign directly
				Get<F>() = std::forward<F>(value);
				return;
			}
			else
			{
				// Delete current value
				Nullify();
			}
		}

		new (_value.GetValue()) F(std::forward<F>(value));
		_index = newIndex;
	}

	/** Gets the current value of this Union as the given type.
	* WARNING: This function will fail if this Variant is not currently holding a value. */
	template <typename F>
	F& Get()
	{
		assert(HasValue() && _index.GetValue() == IndexOf<F>());
		return *_value.template GetValueAs<F>();
	}

	/** Gets the current value of this Union as the given type.
	* WARNING: This function will fail if this Variant is not currently holding a value. */
	template <typename F>
	const F& Get() const
	{
		assert(_index.HasValue() && _index.GetValue() == IndexOf<F>());
		return *_value.template GetValueAs<F>();
	}

	/** Invokes the given function on the current value.
	* WARNING: If this Union is not holding a value, this function will fail. */
	template <typename R = void, typename Func>
	R Invoke(const Func& func)
	{
		using Invoker = R (void*, const Func&);	
		Invoker* funcs[] = { CreateInvoker<T, R, Func>()... };
		
		assert(HasValue());
		return funcs[_index.GetValue()](_value.GetValue(), func);
	}

	/** Invokes the given function on the current value.
	* WARNING: If this Union is not holding a value, this function will fail. */
	template <typename R = void, typename Func>
	R Invoke(const Func& func) const
	{
		using Invoker = R (const void*, const Func&);
		Invoker* funcs[] = { CreateInvoker<T, R, Func>()... };

		assert(HasValue());
		return funcs[_index.GetValue()](_value.GetValue(), func);
	}

private:

	/** Returns the index of the given type. */
	template <typename S>
	static constexpr Index IndexOf()
	{
		static_assert(Seq::template Contains<S>(), "The given type does not exist in this Union.");
		return IndexOf<S>(0, Seq{});
	}

	/** Recursively finds the index of the given type. */
	template <typename S, typename C, typename ... F>
	static constexpr Index IndexOf(Index current, stdEXT::type_sequence<C, F...>)
	{
		return std::is_same<S, C>::value ? current : IndexOf<S>(current + 1, stdEXT::type_sequence<F...>{});
	}

	/** End case, never actually reached. */
	template <typename S>
	static constexpr Index IndexOf(Index current, stdEXT::type_sequence<>)
	{
		return 0;
	}

	/** Creates a function that invokes a function of the given type ("Func") on a type-erased
	* instance of "F", returning an instance of "R".
	* Used by the "Invoke" method. */
	template <typename F, typename R, typename Func>
	/*MSVCS: constexpr*/ auto CreateInvoker()
	{
		return [](void* arg, const Func& func) -> R
		{
			return func(*static_cast<F*>(arg));
		};
	}

	/** Creates a function that invokes a function of the given type ("Func") on a type-erased
	* instance of "F", returning an instance of "R".
	* Used by the "Invoke" method. */
	template <typename F, typename R, typename Func>
	/*MSVCS: constexpr*/ auto CreateInvoker() const
	{
		return [](const void* arg, const Func& func) -> R
		{
			return func(*static_cast<const F*>(arg));
		};
	}

	/** Returns the size of the largest type among the types suppored by this Union. */
	static constexpr std::size_t GetMaxSize()
	{
		return GetMaxSize(Seq{});
	}

	/** Returns the size of the largest type among the types suppored by this Union. */
	template <typename F, typename ... MoreF>
	static constexpr std::size_t GetMaxSize(stdEXT::type_sequence<F, MoreF...>)
	{
		return Max(sizeof(F), GetMaxSize(stdEXT::type_sequence<MoreF...>{}));
	}

	/** Returns the size of the largest type among the types suppored by this Union. */
	static constexpr std::size_t GetMaxSize(stdEXT::type_sequence<>)
	{
		return 0;
	}

	/////////////////////
	///   Operators   ///
public:

	Union& operator=(const Union& copy)
	{
		if (this != &copy)
		{
			if (copy.HasValue())
			{
				// Copy the value
				copy.Invoke([this](const auto& v) -> void
				{
					this->Set(v);
				});
			}
			else
			{
				Nullify();
			}
		}

		return self;
	}
	Union& operator=(Union&& move)
	{
		if (this != &move)
		{
			if (move.HasValue())
			{
				// Move the value
				move.Invoke([this](auto& v) -> void
				{
					this->Set(std::move(v));
				});
				move.Nullify();
			}
			else
			{
				Nullify();
			}
		}

		return self;
	}

	template <typename F>
	Union& operator=(F&& value)
	{
		Set(std::forward<F>(value));
		return self;
	}

	////////////////
	///   Data   ///
private:

	Nullable<Index> _index;

	// For some reason, again ONLY ON MSVC, I have to store this as a static constexpr variable,
	// rather than just putting "GetMaxSize()" into the StaticBuffer size
	static constexpr std::size_t Size = GetMaxSize();
	StaticBuffer<Size> _value;
};
