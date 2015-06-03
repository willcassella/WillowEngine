// FieldInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <functional>
#include "Variant.h"

class CORE_API FieldInfo final : public Object
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(Object);
	friend ClassInfo;
	friend StructInfo;

	////////////////////////
	///   Constructors   ///
private:

	/** Creates a named field */
	template <class OwnerType, typename FieldType>
	FieldInfo(FieldType OwnerType::*field, const String& name)
		: FieldInfo(field, name, "")
	{
		// All done
	}

	/** Creates a named field with a description */
	template <class OwnerType, typename FieldType>
	FieldInfo(FieldType OwnerType::*field, const String& name, const String& description)
		: _name(name),
		_description(description),
		_fieldType(TypeOf<FieldType>()),
		_ownerType(TypeOf<OwnerType>())
	{
		_getter = [field](void* owner)->void*
		{  
			return &(static_cast<OwnerType*>(owner)->*field);
		};
		_setter = [field](void* owner, const void* value)->void
		{
			static_cast<OwnerType*>(owner)->*field = *static_cast<const FieldType*>(value);
		};
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns the name of this field */
	FORCEINLINE const String& GetName() const
	{
		return _name;
	}

	/** Returns a description of this field */
	FORCEINLINE const String& GetDescription() const
	{
		return _description;
	}

	/** Returns the type information for this field */
	FORCEINLINE const TypeInfo& GetFieldType() const
	{
		return _fieldType;
	}

	/** Returns the type information for the owner of this field */
	FORCEINLINE const TypeInfo& GetOwnerType() const
	{
		return _ownerType;
	}

	/** Returns a Variant to the value of this field on the given Variant
	* NOTE: The value referenced by 'owner' must be of the same or extension of the type referenced by 'GetOwnerType()' */
	Variant GetValue(const Variant& owner) const;

	/** Returns an ImmutableVariant to the value of this field on the given ImmutableVariant
	* NOTE: The value referenced by 'owner' must be of the same or extension of the type referenced by 'GetOwnerType()' */
	ImmutableVariant GetValue(const ImmutableVariant& owner) const;

	/** Sets the value of this field on the given Variant to the given value
	* NOTE: The value referenced by 'owner' must be of the same or extension of the type referenced by 'GetOwnerType()' 
	* NOTE: The value referenced by 'value' must be of the same or extension of the type referenced by 'GetFieldType()' */
	void SetValue(const Variant& owner, const ImmutableVariant& value) const;

	/** Returns a Variant to the value of this field on the given value
	* NOTE: 'owner' must be of the same or extension of the type referenced by 'GetOwnerType()' */
	template <class OwnerType>
	FORCEINLINE Variant GetValue(OwnerType& owner) const
	{
		return GetValue(Variant(owner));
	}

	/** Returns an ImmutableVariant to the value of this field on the given value
	* NOTE: 'owner' must be of the same or extension of the type referenced by 'GetOwnerType()' */
	template <class OwnerType>
	FORCEINLINE ImmutableVariant GetValue(const OwnerType& owner) const
	{
		return GetValue(ImmutableVariant(owner));
	}

	////////////////
	///   Data   ///
private:

	String _name;
	String _description;
	TypeIndex _fieldType;
	TypeIndex _ownerType;
	std::function<void* (void*)> _getter;
	std::function<void (void*, const void*)> _setter;
};