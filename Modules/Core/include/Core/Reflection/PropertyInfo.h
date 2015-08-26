// PropertyInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <functional>
#include "Variant.h"

/////////////////
///   Types   ///

enum PropertyFlags : uint32
{
	PF_None = 0,
	PF_NoSerialize = 1 << 0,
	PF_Set_SerializeOnly = 1 << 1
};

/** Enumeration of the different access types for properties. Each is mutually exclusive. */
enum class PropertyAccess : byte
{
	Field,				// Fields are properties that are gauranteed to live within the object that owns them. They may be gotten or set directly.
	NoSetField,			// NoSetFields are fields that may not be set directly because they are not copy-assignable. You may still perform mutable operations on them, however.
	Property,			// Properties may be set directly and have mutable operations performed on them, but may not be gotten directly.
	ReadOnlyProperty	// ReadOnlyProperties may only have immutable operations performed on them.
};

/** A class representing the information for a Property.
* This unfortunately does not model all the const/reference overload
* possibilities for getters and setters, */
struct CORE_API PropertyInfo final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT;

	friend Property;
	friend ImmutableProperty;

	template <typename T, class TypeInfoT>
	friend struct TypeInfoBuilder;

	////////////////////////
	///   Constructors   ///
private:

	PropertyInfo(CString name, CString description, PropertyFlags flags);
	
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

	/** Returns the flags on this property. */
	FORCEINLINE PropertyFlags GetFlags() const
	{
		return _flags;
	}

	/** Returns the acess level for this property. */
	FORCEINLINE PropertyAccess GetAccess() const
	{
		return _access;
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

	/** Gets this Property on the given owner.
	* WARNING: 'owner' must be castable to the type that owns this property. */
	template <typename T>
	Property Get(T& owner);

	/** Gets this Property on the given owner.
	* WARNING: 'owner' must be castable to the type that owns this property. */
	template <typename T>
	ImmutableProperty Get(const T& owner);

	/** It's not safe to get properties on rvalue references. */
	template <typename T>
	auto Get(T&& owner) = delete;

	////////////////
	///   Data   ///
private:

	CString _name;
	CString _description;
	const TypeInfo* _propertyType;
	const CompoundInfo* _ownerType;
	std::function<const void* (const void*)> _fieldGetter;
	std::function<void (void*, const void*)> _setter;
	std::function<String (const void*)> _toString;
	std::function<String (void*, const String&)> _fromString;
	std::function<void (const void*, ArchNode&)> _toArchive;
	PropertyFlags _flags;
	PropertyAccess _access;
};

/** Type encapsulating access to a mutable (though possible read-only) Property. */
struct CORE_API Property final : Contract::Proxy<Property>
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

	/** Formats the state of this Property as a String. */
	String ToString() const;

	/** Parses this Property from a String, a returns the remainder of the string. */
	String FromString(const String& string) const;

	/** Serializes this property to the given archive node. */
	void ToArchive(ArchNode& node) const;

	/** Sets the value of this property.
	* WARNING: If the access level of this property is 'ReadOnlyProperty', this function will fail. */
	void SetValue(ImmutableVariant value) const;

	/** Accesses this property as a field.
	* WARNING: If the access level of this property is not 'Field', this function will fail. */
	Variant GetField() const;

	////////////////
	///   Data   ///
private:

	const PropertyInfo* _info;
	void* _owner;
};

/** Type encapsulating access to an immutable property. */
struct CORE_API ImmutableProperty final : Contract::Proxy<ImmutableProperty>
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

	/** Formats the state of this property as a String. */
	String ToString() const;

	/** Serializes this property to the given archive node. */
	void ToArchive(ArchNode& node) const;

	/** Accesses this property as a field.
	* WARNING: If the access level of this property is not 'Field', this function will fail. */
	ImmutableVariant GetField() const;

	////////////////
	///   Data   ///
private:

	const PropertyInfo* _info;
	const void* _owner;
};

///////////////////
///   Methods   ///

template <typename T>
Property PropertyInfo::Get(T& owner)
{
	return Property(self, &owner);
}

template <typename T>
ImmutableProperty PropertyInfo::Get(const T& owner)
{
	return ImmutableProperty(self, &owner);
}

/////////////////////
///   Functions   ///

/** You can't call 'FromString' on an ImmutableProperty. */
String FromString(ImmutableProperty) = delete;

//////////////////////
///   Reflection   ///

REFLECTABLE_ENUM(PropertyFlags)
REFLECTABLE_ENUM(PropertyAccess)
