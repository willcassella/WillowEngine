// Angle.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Reflection/StructInfo.h"

/** An arithmetic value representing an angle (internally stored as radians). */
template <typename T>
struct TAngle final
{
	/////////////////////
	///   Constants   ///
public:

	/** Multiplication factor for converting degrees to radians. */
	static constexpr T DegreesToRadians = T{ 0.0174533f };

	/** Multiplication factor for converting radians to degrees. */
	static constexpr T RadiansToDegrees = T{ 57.2958f };

	////////////////////////
	///   Constructors   ///
public:

	constexpr TAngle()
		: _radians{ 0 }
	{
		// All done
	}
	constexpr TAngle(T radians)
		: _radians{ radians }
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns the current value in radians. */
	constexpr T GetRadians() const
	{
		return _radians;
	}

	/** Sets the current value in radians. */
	constexpr void SetRadians(T value)
	{
		_radians = value;
	}

	/** Returns the current value in degrees. */
	constexpr T GetDegrees() const
	{
		return _radians * RadiansToDegrees;
	}

	/** Sets the current value in degrees. */
	constexpr void SetDegrees(T value)
	{
		_radians = value * DegreesToRadians;
	}

	/////////////////////
	///   Operators   ///
public:

	/** Converts this object to the underlying type. */
	constexpr operator T() const
	{
		return _radians;
	}

	/** Coversion operator for casting between precisions. */
	template <typename F>
	explicit operator TAngle<F>()
	{
		return{ static_cast<F>(_radians) };
	}

	////////////////
	///   Data   ///
private:

	T _radians;
};

/** Alias for scalar angles. */
using Angle = TAngle<Scalar>;

/////////////////////
///   Functions   ///

/** Constructs an angle in radians. */
template <typename T>
constexpr TAngle<T> Radians(T value)
{
	return{ value };
}

/** Constructs an angle in degrees. */
template <typename T>
constexpr TAngle<T> Degrees(T value)
{
	return{ value * TAngle<T>::DegreesToRadians };
}

//////////////////////
///   Operations   ///

namespace Implementation
{
	template <typename T>
	struct TypeOf < TAngle<T> > final
	{
		/** Defined below. */
		static const StructInfo StaticTypeInfo;

		FORCEINLINE static const StructInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const StructInfo& Function(const TAngle<T>& /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	template <typename T>
	const StructInfo TypeOf<TAngle<T>>::StaticTypeInfo = TypeInfoBuilder<TAngle<T>>("TAngle");
}
