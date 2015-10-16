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
	using Seq = stdEXT::type_sequence<T...>;

	////////////////////////
	///   Constructors   ///
public:

	Union() = default;
	Union(const Union& copy)
	{
		// TODO
	}
	Union(Union&& move)
	{
		// TODO
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

	FORCEINLINE bool HasValue() const
	{
		return _index.HasValue();
	}

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

	template <typename F>
	F& Get()
	{
		assert(HasValue() && _index.GetValue() == IndexOf<F>());
		return *_value.template GetValueAs<F>();
	}

	template <typename F>
	const F& Get() const
	{
		assert(_index.HasValue() && _index.GetValue() == IndexOf<F>());
		return *_value.template GetValueAs<F>();
	}

	const TypeInfo* GetCurrentType() const
	{
		if (_index.HasValue())
		{
			return CallFunction<const TypeInfo*>([](const auto& a) { return &TypeOf(a); });
		}
		else
		{
			return nullptr;
		}
	}

	void Nullify()
	{
		if (HasValue())
		{
			// Destroy the value
			CallFunction([](auto& v) { v.~decltype(v)(); });
			_index.Nullify();
		}
	}

	/** Calls the given function on the current value.
	* WARNING: If this Union is not holding a value, this function will fail. */
	template <typename R = void>
	R CallFunction(const auto& func)
	{
		using Func = decltype(func);
		using Invoker = R (void*, const Func&);	
		constexpr Invoker* funcs[] = { CreateInvoker<T, R, Func>()... };
		
		assert(HasValue());
		return funcs[_index.GetValue()](_value.GetValue(), func);
	}

	/** Calls the given function on the current value.
	* WARNING: If this Union is not holding a value, this function will fail. */
	template <typename R = void>
	R CallFunction(const auto& func) const
	{
		using Func = decltype(func);
		using Invoker = R (const void*, const Func&);
		constexpr Invoker* funcs[] = { CreateInvoker<T, R, Func>()... };

		assert(HasValue());
		return funcs[_index.GetValue()](_value.GetValue(), func);
	}

private:

	/** Returns the index of the given type. */
	template <typename S>
	static constexpr Index IndexOf()
	{
		static_assert(Seq::template Contains<S>(), "The given type does not exist in this Union.");
		return IndexOf(0, Seq{});
	}

	/** Returns the index of the given type. */
	template <typename S, typename C, typename ... F>
	static constexpr Index IndexOf(Index current, stdEXT::type_sequence<C, F...>)
	{
		return IndexOf(current + 1, stdEXT::type_sequence<F...>{});
	}

	/** Returns the index of the given type. */
	template <typename S, typename ... F>
	static constexpr Index IndexOf(Index current, stdEXT::type_sequence<S, F...>)
	{
		return current;
	}

	/** Creates a function that invokes a function of the given type ("Func") on a type-erased
	* instance of "F", returning an instance of "R".
	* Used by the "CallFunction" method. */
	template <typename F, typename R, typename Func>
	constexpr auto CreateInvoker()
	{
		return [](void* arg, const Func& func) -> R
		{
			return func(*static_cast<F*>(arg));
		};
	}

	/** Creates a function that invokes a function of the given type ("Func") on a type-erased
	* instance of "F", returning an instance of "R".
	* Used by the "CallFunction" method. */
	template <typename F, typename R, typename Func>
	constexpr auto CreateInvoker() const
	{
		return [](const void* arg, const Func& func) -> R
		{
			return func(*static_cast<const F*>(arg));
		};
	}

	static constexpr std::size_t GetMaxSize()
	{
		return GetMaxSize(Seq{});
	}

	template <typename F, typename ... MoreF>
	static constexpr std::size_t GetMaxSize(stdEXT::type_sequence<F, MoreF...>)
	{
		return Max(sizeof(F), GetMaxSize(stdEXT::type_sequence<MoreF...>{}));
	}

	template <typename F>
	static constexpr std::size_t GetMaxSize(stdEXT::type_sequence<F>)
	{
		return sizeof(F);
	}

	/////////////////////
	///   Operators   ///
public:

	Union& operator=(const Union& copy)
	{
		// TODO
		return self;
	}
	Union& operator=(Union&& move)
	{
		// TODO
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
	StaticBuffer<GetMaxSize()> _value;
};
