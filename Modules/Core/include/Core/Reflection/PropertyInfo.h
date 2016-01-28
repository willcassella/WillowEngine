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
REFLECTABLE_ENUM(PropertyFlags)

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

	/** Gets this Property on the given owner.
	* WARNING: 'owner' must be castable to the type that owns this property. */
	Property Get(Variant owner) const;

	/** Gets this Property on the given owner. 
	* WARNING: 'owner' must be castable to the type that owns this property. */
	ImmutableProperty Get(ImmutableVariant owner) const;

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

	/** Formats the state of this Property as a String. */
	String ToString() const;

	/** Parses this Property from a String, a returns the remainder of the string. 
	* WARNING: This function will fail if this is a read-only property. */
	String FromString(const String& string);

	/** Serializes this property to the given archive. */
	void ToArchive(ArchiveWriter& writer) const;

	/** Deserializes this property from the given archive.
	* WARNING: This will fail if this is a read-only property. */
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

	/** Formats the state of this property as a String. */
	String ToString() const;

	/** Serializes this property to the given archive. */
	void ToArchive(ArchiveWriter& writer) const;

	////////////////
	///   Data   ///
private:

	const PropertyInfo* _info;
	const void* _owner;
};

/////////////////////
///   Functions   ///

/** You can't call 'FromString' on an ImmutableProperty. */
String FromString(ImmutableProperty, const String&) = delete;

/** You can't call 'FromArchive' on an ImmutableProperty. */
void FromArchive(ImmutableProperty, const ArchiveReader&) = delete;
