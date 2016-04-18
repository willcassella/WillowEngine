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
	static constexpr T Degrees_To_Radians = T{ 0.0174533f };

	/** Multiplication factor for converting radians to degrees. */
	static constexpr T Radians_To_Degrees = T{ 57.2958f };

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
	constexpr T get_radians() const
	{
		return this->_radians;
	}

	/** Sets the current value in radians. */
	constexpr void set_radians(T value)
	{
		this->_radians = value;
	}

	/** Returns the current value in degrees. */
	constexpr T get_degrees() const
	{
		return this->_radians * Radians_To_Degrees;
	}

	/** Sets the current value in degrees. */
	constexpr void set_degrees(T value)
	{
		this->_radians = value * Degrees_To_Radians;
	}

	/////////////////////
	///   Operators   ///
public:

	/** Converts this object to the underlying type. */
	constexpr operator T() const
	{
		return this->_radians;
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
constexpr TAngle<T> radians(T value)
{
	return{ value };
}

/** Constructs an angle in degrees. */
template <typename T>
constexpr TAngle<T> degrees(T value)
{
	return{ value * TAngle<T>::Degrees_To_Radians };
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
