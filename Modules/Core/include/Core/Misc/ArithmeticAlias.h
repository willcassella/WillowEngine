// ArithmeticAlias.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <type_traits>

/** Aliases an arithmetic type.
* T - the type to alias. 
* Cookie - throwaway type to prevent alias overlapping. */
template <typename T, typename CookieT>
struct ArithmeticAlias
{
	///////////////////////
	///   Information   ///
public:

	static_assert(std::is_arithmetic<T>::value, "'T' must be an arithmetic type.");

	////////////////////////
	///   Constructors   ///
public:

	constexpr ArithmeticAlias()
		: _value{}
	{
		// All done
	}
	constexpr ArithmeticAlias(T value)
		: _value{ value }
	{
		// All done
	}

	template <typename F>
	ArithmeticAlias(ArithmeticAlias<T, F> value) = delete;

	/////////////////////
	///   Operators   ///
public:

	/** Assignment operators. */
	constexpr ArithmeticAlias& operator+=(ArithmeticAlias rhs)
	{
		*this = *this + rhs;
		return *this;
	}
	constexpr ArithmeticAlias& operator-=(ArithmeticAlias rhs)
	{
		*this = *this - rhs;
		return *this;
	}
	constexpr ArithmeticAlias& operator*=(ArithmeticAlias rhs)
	{
		*this = *this * rhs;
		return *this;
	}
	constexpr ArithmeticAlias& operator/=(ArithmeticAlias rhs)
	{
		*this = *this / rhs;
		return *this;
	}
	constexpr ArithmeticAlias& operator+=(T rhs)
	{
		*this = *this + rhs;
		return *this;
	}
	constexpr ArithmeticAlias& operator-=(T rhs)
	{
		*this = *this + rhs;
		return *this;
	}
	constexpr ArithmeticAlias& operator*=(T rhs)
	{
		*this = *this * rhs;
		return *this;
	}
	constexpr ArithmeticAlias& operator/=(T rhs)
	{
		*this = *this / rhs;
		return *this;
	}

	template <typename F>
	void operator+=(ArithmeticAlias<T, F> rhs) = delete;

	template <typename F>
	void operator-=(ArithmeticAlias<T, F> rhs) = delete;

	template <typename F>
	void operator*=(ArithmeticAlias<T, F> rhs) = delete;

	template <typename F>
	void operator/=(ArithmeticAlias<T, F> rhs) = delete;

	/** Conversion operator. */
	constexpr operator T() const
	{
		return _value;
	}

	/** Comparison operators. */
	friend constexpr bool operator==(ArithmeticAlias lhs, ArithmeticAlias rhs)
	{
		return lhs._value == rhs._value;
	}
	friend constexpr bool operator!=(ArithmeticAlias lhs, ArithmeticAlias rhs)
	{
		return lhs._value != rhs._value;
	}
	friend constexpr bool operator<(ArithmeticAlias lhs, ArithmeticAlias rhs)
	{
		return lhs._value < rhs._value;
	}
	friend constexpr bool operator<=(ArithmeticAlias lhs, ArithmeticAlias rhs)
	{
		return lhs._value <= rhs._value;
	}
	friend constexpr bool operator>(ArithmeticAlias lhs, ArithmeticAlias rhs)
	{
		return lhs._value > rhs._value;
	}
	friend constexpr bool operator>=(ArithmeticAlias lhs, ArithmeticAlias rhs)
	{
		return lhs._value >= rhs._value;
	}
	friend constexpr bool operator==(ArithmeticAlias lhs, T rhs)
	{
		return lhs._value == rhs;
	}
	friend constexpr bool operator!=(ArithmeticAlias lhs, T rhs)
	{
		return lhs._value != rhs;
	}
	friend constexpr bool operator<(ArithmeticAlias lhs, T rhs)
	{
		return lhs._value < rhs;
	}
	friend constexpr bool operator<=(ArithmeticAlias lhs, T rhs)
	{
		return lhs._value <= rhs;
	}
	friend constexpr bool operator>(ArithmeticAlias lhs, T rhs)
	{
		return lhs._value > rhs;
	}
	friend constexpr bool operator>=(ArithmeticAlias lhs, T rhs)
	{
		return lhs._value >= rhs;
	}
	friend constexpr bool operator==(T lhs, ArithmeticAlias rhs)
	{
		return lhs == rhs._value;
	}
	friend constexpr bool operator!=(T lhs, ArithmeticAlias rhs)
	{
		return lhs != rhs._value;
	}
	friend constexpr bool operator<(T lhs, ArithmeticAlias rhs)
	{
		return lhs < rhs._value;
	}
	friend constexpr bool operator<=(T lhs, ArithmeticAlias rhs)
	{
		return lhs <= rhs._value;
	}
	friend constexpr bool operator>(T lhs, ArithmeticAlias rhs)
	{
		return lhs > rhs._value;
	}
	friend constexpr bool operator>=(T lhs, ArithmeticAlias rhs)
	{
		return lhs >= rhs._value;
	}

	template <typename F>
	void operator==(ArithmeticAlias<T, F> rhs) = delete;

	template <typename F>
	void operator!=(ArithmeticAlias<T, F> rhs) = delete;

	template <typename F>
	void operator<(ArithmeticAlias<T, F> rhs) = delete;

	template <typename F>
	void operator<=(ArithmeticAlias<T, F> rhs) = delete;

	template <typename F>
	void operator>(ArithmeticAlias<T, F> rhs) = delete;

	template <typename F>
	void operator>=(ArithmeticAlias<T, F> rhs) = delete;

	/** Arithmetic operators. */
	friend constexpr ArithmeticAlias operator+(ArithmeticAlias lhs, ArithmeticAlias rhs)
	{
		return lhs._value + rhs._value;
	}
	friend constexpr ArithmeticAlias operator-(ArithmeticAlias lhs, ArithmeticAlias rhs)
	{
		return lhs._value - rhs._value;
	}
	friend constexpr ArithmeticAlias operator*(ArithmeticAlias lhs, ArithmeticAlias rhs)
	{
		return lhs._value * rhs._value;
	}
	friend constexpr ArithmeticAlias operator/(ArithmeticAlias lhs, ArithmeticAlias rhs)
	{
		return lhs._value / rhs._value;
	}
	friend constexpr ArithmeticAlias operator+(ArithmeticAlias lhs, T rhs)
	{
		return lhs._value + rhs;
	}
	friend constexpr ArithmeticAlias operator-(ArithmeticAlias lhs, T rhs)
	{
		return lhs._value - rhs;
	}
	friend constexpr ArithmeticAlias operator*(ArithmeticAlias lhs, T rhs)
	{
		return lhs._value * rhs;
	}
	friend constexpr ArithmeticAlias operator/(ArithmeticAlias lhs, T rhs)
	{
		return lhs._value / rhs;
	}
	friend constexpr ArithmeticAlias operator+(T lhs, ArithmeticAlias rhs)
	{
		return lhs + rhs._value;
	}
	friend constexpr ArithmeticAlias operator-(T lhs, ArithmeticAlias rhs)
	{
		return lhs - rhs._value;
	}
	friend constexpr ArithmeticAlias operator*(T lhs, ArithmeticAlias rhs)
	{
		return lhs * rhs._value;
	}
	friend constexpr ArithmeticAlias operator/(T lhs, ArithmeticAlias rhs)
	{
		return lhs / rhs._value;
	}

	template <typename F>
	void operator+(ArithmeticAlias<T, F> rhs) = delete;

	template <typename F>
	void operator-(ArithmeticAlias<T, F> rhs) = delete;

	template <typename F>
	void operator*(ArithmeticAlias<T, F> rhs) = delete;

	template <typename F>
	void operator/(ArithmeticAlias<T, F> rhs) = delete;

	////////////////
	///   Data   ///
private:

	T _value;
};
