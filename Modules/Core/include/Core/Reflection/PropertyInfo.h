// PropertyInfo.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <functional>
#include "Variant.h"

/////////////////
///   Types   ///

enum PropertyFlags : byte
{
	PF_None = 0,				/** No special considerations need to be made for this property. */
	PF_EditorOnly = (1 << 0)	/** This property should only be exposed to the editor. */
};
REFLECTABLE_ENUM(CORE_API, PropertyFlags)

/** A class representing information for a Property (part of the public API for a compound). */
struct CORE_API PropertyInfo final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT

	friend Property;
	friend ImmutableProperty;

	template <typename T, class TypeInfoT>
	friend struct TypeInfoBuilder;

	////////////////////////
	///   Constructors   ///
private:

	PropertyInfo(CString name, CString description, CString category, PropertyFlags flags);
	
	///////////////////
	///   Methods   ///
public:

	/** Formats the state of this PropertyInfo as a String. */
	FORCEINLINE String ToString() const
	{
		return GetName();
	}

	/** Returns the name of this Property. */
	FORCEINLINE CString GetName() const
	{
		return _name;
	}

	/** Returns a description of this Property. */
	FORCEINLINE CString GetDescription() const
	{
		return _description;
	}

	/** Returns the category this Property belongs to. */
	FORCEINLINE CString GetCategory() const
	{
		return _category;
	}

	/** Returns the flags on this property. */
	FORCEINLINE PropertyFlags GetFlags() const
	{
		return _flags;
	}

	/** Returns whether this property is read-only. */
	FORCEINLINE bool IsReadOnly() const
	{
		return _isReadOnly;
	}

	/** Returns the type information for this Property. */
	FORCEINLINE const TypeInfo& GetPropertyType() const
	{
		return *_propertyType;
	}

	/** Returns the type information for the owner of this Property. */
	FORCEINLINE const CompoundInfo& GetOwnerType() const
	{
		return *_ownerType;
	}

	/** Gets this Property from the given owner.
	* WARNING: 'owner' must be castable to the type that owns this property. */
	Property GetFromOwner(Variant owner) const;

	/** Gets this Property from the given owner. 
	* WARNING: 'owner' must be castable to the type that owns this property. */
	ImmutableProperty GetFromOwner(ImmutableVariant owner) const;

	/** Gets this Property from the given owner.
	* WARNING: 'owner' must be castable to the type that owns this property. */
	template <typename T>
	Property GetFromOwner(T& owner) const;

	/** Gets this Property from the given owner.
	* WARNING: 'owner' must be castable to the type that owns this property. */
	template <typename T>
	ImmutableProperty GetFromOwner(const T& owner) const;

	////////////////
	///   Data   ///
private:

	CString _name;
	CString _description;
	CString _category;
	const TypeInfo* _propertyType;
	const CompoundInfo* _ownerType;
	std::function<String (const void*)> _toString;
	std::function<String (void*, const String&)> _fromString;
	std::function<void (const void*, ArchiveWriter&)> _toArchive;
	std::function<void (void*, const ArchiveReader&)> _fromArchive;
	PropertyFlags _flags;
	bool _isReadOnly;
};

/** Type encapsulating access to a mutable (though possible read-only) Property. */
struct CORE_API Property final
{
	///////////////////////
	///   Information   ///
public:

	friend PropertyInfo;
	friend ImmutableProperty;

	////////////////////////
	///   Constructors   ///
private:

	Property(const PropertyInfo& info, void* owner);

	///////////////////
	///   Methods   ///
public:

	/** Returns the information for this Property. */
	FORCEINLINE const PropertyInfo& GetInfo() const
	{
		return *_info;
	}

	/** Returns this property's type. */
	FORCEINLINE const TypeInfo& GetType() const
	{
		return _info->GetPropertyType();
	}

	/** Returns whether this Property may be formatted as a String. */
	bool HasToStringImplementation() const;

	/** Formats the state of this Property as a String. 
	* WARNING: Check 'HasToStringImplementation()' first. */
	String ToString() const;

	/** Returns whether this Property may be set from a String. */
	bool HasFromStringImplementation() const;

	/** Parses this Property from a String, returning the remainder of the string. 
	* WARNING: This function will fail if this is a read-only property. Check 'HasFromStringImplementation()' first. */
	String FromString(const String& string);

	/** Returns whether this Property may be serialized to an Archive. */
	bool HasToArchiveImplementation() const;

	/** Serializes this property to the given archive. 
	* WARNING: Check 'HasToArchiveImplementation()' first. */
	void ToArchive(ArchiveWriter& writer) const;

	/** Returns whether this Property may be deserialized from an Archive. */
	bool HasFromArchiveImplementation() const;

	/** Deserializes this property from the given archive.
	* WARNING: This will fail if this is a read-only property. Check 'HasFromArchiveImplementation()' first. */
	void FromArchive(const ArchiveReader& reader);

	////////////////
	///   Data   ///
private:

	const PropertyInfo* _info;
	void* _owner;
};

/** Type encapsulating access to an immutable property. */
struct CORE_API ImmutableProperty final
{
	///////////////////////
	///   Information   ///
public:

	friend PropertyInfo;

	////////////////////////
	///   Constructors   ///
public:

	/** Encapsulates a mutable property as an immutable property. */
	ImmutableProperty(const Property& prop);

private:

	ImmutableProperty(const PropertyInfo& info, const void* owner);

	///////////////////
	///   Methods   ///
public:

	/** Returns the information for this property. */
	FORCEINLINE const PropertyInfo& GetInfo() const
	{
		return *_info;
	}

	/** Returns the type of this property. */
	FORCEINLINE const TypeInfo& GetType() const
	{
		return _info->GetPropertyType();
	}

	/** Returns whether this ImmutableProperty may be formatted as a String. */
	bool HasToStringImplementation() const;

	/** Formats the state of this ImmutableProperty as a String. 
	* WARNING: Check 'HasToStringImplementation()' first. */
	String ToString() const;

	/** Returns whether this ImmutableProperty may be serialized to an Archive. */
	bool HasToArchiveImplementation() const;

	/** Serializes the state of this ImmutableProperty to the given archive. 
	* WARNING: Check 'HasToArchiveImplementation()' first. */
	void ToArchive(ArchiveWriter& writer) const;

	////////////////
	///   Data   ///
private:

	const PropertyInfo* _info;
	const void* _owner;
};

///////////////////
///   Methods   ///

template <typename T>
Property PropertyInfo::GetFromOwner(T& owner) const
{
	return this->GetFromOwner(Variant(owner));
}

template <typename T>
ImmutableProperty PropertyInfo::GetFromOwner(const T& owner) const
{
	return this->GetFromOwner(ImmutableVariant(owner));
}
