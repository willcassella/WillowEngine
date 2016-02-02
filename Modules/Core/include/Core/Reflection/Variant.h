// Variant.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "TypeInfo.h"

/////////////////
///   Types   ///

/** Basically a wrapper over "void*" */
struct CORE_API Variant final
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

	/** Returns whether 'ToString' is supported by the referenced value. */
	FORCEINLINE bool HasToStringImplementation() const
	{
		return _type->HasToStringImplementation();
	}

	/** Formats the state of this Variant as a String. 
	* WARNING: Check 'HasToStringImplementation()' first. */
	FORCEINLINE String ToString() const
	{
		assert(this->HasToStringImplementation());
		return _type->GetToStringImplementation()(_value);
	}

	/** Returns whether 'FromString' is supported by the referenced value. */
	FORCEINLINE bool HasFromStringImplementation() const
	{
		return _type->HasFromArchiveImplementation();
	}

	/** Sets the state of this Variant from a String, returning the remainder. 
	* WARNING: Check 'HasFromStringImplementation()' first. */
	FORCEINLINE String FromString(const String& string)
	{
		assert(this->HasFromStringImplementation());
		return _type->GetFromStringImplementation()(_value, string);
	}

	/** Returns whether 'ToArchive' is supported by the referenced value. */
	FORCEINLINE bool HasToArchiveImplementation() const
	{
		return _type->HasToArchiveImplementation();
	}

	/** Serializes the state of this Variant to the given archive. 
	* WARNING: Check 'HasToArchiveImplementation()' first. */
	FORCEINLINE void ToArchive(ArchiveWriter& writer) const
	{
		assert(this->HasToArchiveImplementation());
		_type->GetToArchiveImplementation()(_value, writer);
	}

	/** Returns whether 'FromArchive' is supported by the referenced value. */
	FORCEINLINE bool HasFromArchiveImplementatino() const
	{
		return _type->HasFromArchiveImplementation();
	}

	/** Deserializes the state of this Variant from the given archive.
	* WARNING: Check 'HasFromArchiveImplementation()' first. */
	FORCEINLINE void FromArchive(const ArchiveReader& reader)
	{
		assert(this->HasFromStringImplementation());
		_type->GetFromArchiveImplementation()(_value, reader);
	}

	////////////////
	///   Data   ///
private:

	void* _value;
	const TypeInfo* _type;
};

/** Basically a wrapper of "const void*" */
struct CORE_API ImmutableVariant final
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

	/** Returns whether 'ToString' is supported by the referenced value. */
	FORCEINLINE bool HasToStringImplementation() const
	{
		return _type->HasToStringImplementation();
	}

	/** Formats the state of this ImmutableVariant as a String. 
	* WARNING: Check 'HasToStringImplementation()' first. */
	FORCEINLINE String ToString() const
	{
		assert(this->HasToStringImplementation());
		return _type->GetToStringImplementation()(_value);
	}

	/** Returns whether 'ToArchive' is supported by the referenced value. */
	FORCEINLINE bool HasToArchiveImplementation() const
	{
		return _type->HasToArchiveImplementation();
	}

	/** Serializes the state of this ImmutableVariant to the given archive. 
	* WARNING: Check 'HasFromArchiveImplementation' first. */
	FORCEINLINE void ToArchive(ArchiveWriter& writer) const
	{
		assert(this->HasToArchiveImplementation());
		_type->GetToArchiveImplementation()(_value, writer);
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
