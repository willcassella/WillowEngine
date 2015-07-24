// Variant.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "TypeIndex.h"

/////////////////
///   Types   ///

/** Basically a smart wrapper over "void*" @TODO: Figure out a safer way of doing this */
struct CORE_API Variant final
{
	////////////////////////
	///   Constructors   ///
public:

	/** Constructs a Variant to 'void' */
	Variant();

	/** Constructs a Variant to a value of any type
	* 'value' - The value to reference
	* 'type' - The type of the value */
	Variant(void* value, const TypeInfo& type)
		: _value(value), _type(type)
	{
		// All done
	}

	/** Constructs a Variant to a value of any type */
	template <typename AnyType>
	Variant(AnyType& value)
		: _value(&value), _type(TypeOf(value))
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns the referenced value */
	FORCEINLINE void* GetValue() const
	{
		return _value;
	}

	/** Returns the type of the referenced value */
	FORCEINLINE const TypeInfo& GetType() const
	{
		return _type;
	}

	/////////////////////
	///   Operators   ///
public:

	template <typename AnyType>
	Variant& operator=(AnyType& value)
	{
		_value = &value;
		_type = TypeOf(value);
		return self;
	}

	////////////////
	///   Data   ///
private:

	void* _value;
	TypeIndex _type;
};

/** Basically a smart wrapper of "const void*" */
struct CORE_API ImmutableVariant final
{
	////////////////////////
	///   Constructors   ///
public:

	/** Constructs an ImmutableVariant to 'void' */
	ImmutableVariant();

	/** Constructs an ImmutableVariant to a value of any type
	* 'value' - The value to reference
	* 'type' - The type of the value */
	ImmutableVariant(const void* value, const TypeInfo& type)
		: _value(value), _type(type)
	{
		// All done
	}

	/** Constructs an ImmutableVariant to the value referenced by a non-immutable variant */
	ImmutableVariant(const Variant& var)
		: _value(var.GetValue()), _type(var.GetType())
	{
		// All done
	}

	/** Constructs an ImmutableVariant to a value of any type */
	template <typename AnyType>
	ImmutableVariant(const AnyType& value)
		: _value(&value), _type(TypeOf(value))
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns the value referenced by this ImmutableVariant */
	FORCEINLINE const void* GetValue() const
	{
		return _value;
	}

	/** Returns the type of the value referenced by this ImmutableVariant */
	FORCEINLINE const TypeInfo& GetType() const
	{
		return _type;
	}

	/////////////////////
	///   Operators   ///
public:

	ImmutableVariant& operator=(const Variant& var)
	{
		_value = var.GetValue();
		_type = var.GetType();
		return self;
	}

	template <typename AnyType>
	ImmutableVariant& operator=(const AnyType& value)
	{
		_value = &value;
		_type = TypeOf(value);
		return self;
	}

	////////////////
	///   Data   ///
private:

	const void* _value;
	TypeIndex _type;
};

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Implementation of "TypeOf" for "Variant" */
	template <>
	struct TypeOf < Variant >
	{
		static const TypeInfo& Function() = delete; // "Variant" has no static type information

		FORCEINLINE static const TypeInfo& Function(const Variant& variant)
		{
			return variant.GetType();
		}
	};

	/** Implementation of "TypeOf" for "ImmutableVariant" */
	template <>
	struct TypeOf < ImmutableVariant >
	{
		static const TypeInfo& Function() = delete; // "ImmutableVariant" has no static type information

		FORCEINLINE static const TypeInfo& Function(const ImmutableVariant& variant)
		{
			return variant.GetType();
		}
	};
}

/////////////////////
///   Functions   ///

// @TODO: Documentation
template <typename TargetType>
FORCEINLINE TargetType* Cast(const Variant& value)
{
	if (value.GetType().IsCastableTo<TargetType>())
	{
		return static_cast<TargetType*>(value.GetValue());
	}
	else
	{
		return nullptr;
	}
}

// @TODO: Documentation
template <typename TargetType>
FORCEINLINE const TargetType* Cast(const ImmutableVariant& value)
{
	if (value.GetType().IsCastableTo<TargetType>())
	{
		return static_cast<const TargetType*>(value.GetValue());
	}
	else
	{
		return nullptr;
	}
}
