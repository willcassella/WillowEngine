// Variant.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "TypeInfo.h"

/////////////////
///   Types   ///

/** Basically a wrapper over "void*" */
struct CORE_API Variant final : Contract::Proxy<Variant>
{
	////////////////////////
	///   Constructors   ///
public:

	/** Constructs a Variant to a value of any type
	* 'value' - The value to reference
	* 'type' - The type of the value */
	Variant(void* value, const TypeInfo& type)
		: _value(value), _type(&type)
	{
		assert(value != nullptr);
	}

	/** Constructs a Variant to a value of any type (except Variant types). */
	template <typename T, WHERE(!std::is_same<T, Variant>::value && !std::is_same<T, ImmutableVariant>::value)>
	Variant(T& value)
		: _value(&value), _type(&TypeOf(value))
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns the referenced value. */
	FORCEINLINE void* GetValue()
	{
		return _value;
	}

	/** Returns the referenced value. */
	FORCEINLINE const void* GetValue() const
	{
		return _value;
	}

	/** Returns the type of the referenced value */
	FORCEINLINE const TypeInfo& GetType() const
	{
		return *_type;
	}

	// TODO: Documentation
	FORCEINLINE String ToString() const
	{
		return _type->GetToStringImplementation()(_value);
	}

	// TODO: Documentation
	FORCEINLINE String FromString(const String& string)
	{
		return _type->GetFromStringImplementation()(_value, string);
	}

	// TODO: Documentation
	FORCEINLINE void ToArchive(ArchiveNode& node) const
	{
		_type->GetToArchiveImplementation()(_value, node);
	}

	// TODO: Documentation
	FORCEINLINE void FromArchive(const ArchiveNode& node)
	{
		_type->GetFromArchiveImplementation()(_value, node);
	}

	////////////////
	///   Data   ///
private:

	void* _value;
	const TypeInfo* _type;
};

/** Basically a wrapper of "const void*" */
struct CORE_API ImmutableVariant final : Contract::Proxy<ImmutableVariant>
{
	////////////////////////
	///   Constructors   ///
public:

	/** Constructs an ImmutableVariant to the value referenced by a non-immutable variant */
	ImmutableVariant(Variant value)
		: _value(value.GetValue()), _type(&value.GetType())
	{
		// All done
	}

	/** Constructs an ImmutableVariant to a value of any type
	* 'value' - The value to reference
	* 'type' - The type of the value */
	ImmutableVariant(const void* value, const TypeInfo& type)
		: _value(value), _type(&type)
	{
		assert(value != nullptr);
	}

	/** Constructs an ImmutableVariant to a value of any type (except Variant types) */
	template <typename T, WHERE(!std::is_same<T, Variant>::value && !std::is_same<T, ImmutableVariant>::value)>
	ImmutableVariant(const T& value)
		: _value(&value), _type(&TypeOf(value))
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns the value referenced by this ImmutableVariant. */
	FORCEINLINE const void* GetValue() const
	{
		return _value;
	}

	/** Returns the type of the value referenced by this ImmutableVariant */
	FORCEINLINE const TypeInfo& GetType() const
	{
		return *_type;
	}

	/** Formats the state of this ImmutableVariant as a String. */
	FORCEINLINE String ToString() const
	{
		return _type->GetToStringImplementation()(_value);
	}

	// TODO: Documentation
	FORCEINLINE void ToArchive(ArchiveNode& node) const
	{
		_type->GetToArchiveImplementation()(_value, node);
	}

	////////////////
	///   Data   ///
private:

	const void* _value;
	const TypeInfo* _type;
};

/////////////////////
///   Functions   ///

// @TODO: Documentation
template <typename TargetT>
FORCEINLINE TargetT* Cast(Variant value)
{
	if (value.GetType().IsCastableTo(TypeOf<TargetT>()))
	{
		return static_cast<TargetT*>(value.GetValue());
	}
	else
	{
		return nullptr;
	}
}

// @TODO: Documentation
template <typename TargetT>
FORCEINLINE const TargetT* Cast(ImmutableVariant value)
{
	if (value.GetType().IsCastableTo(TypeOf<TargetT>()))
	{
		return static_cast<const TargetT*>(value.GetValue());
	}
	else
	{
		return nullptr;
	}
}

/** You cannot call 'FromString' on an ImmutableVariant. */
String FromString(ImmutableVariant) = delete;

/** You cannot call 'FromArchive' on an ImmutableVariant. */
void FromArchive(ImmutableVariant) = delete;
