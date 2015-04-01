// FieldInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "TypeInfo.h"

/** Abstract interface for handling field information */
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

	template <class OwnerType, typename FieldType>
	FieldInfo(const String& name, FieldType OwnerType::*field)
		: _name(name)
	{
		_fieldType = &TypeOf<FieldType>();
		_ownerType = &TypeOf<OwnerType>();
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
		return *_fieldType;
	}

	/** Returns the type information for the owner of this field */
	FORCEINLINE const TypeInfo& GetOwnerType() const
	{
		return *_ownerType;
	}

	/** Returns a Variant (with the same mutability as "owner") to the value of this field on the given Variant
	* WARNING: "owner" may not be a null Reference
	* @TODO: Exception info */
	Variant GetValue(Variant owner) const;

	/** Sets the value of this field on the given Reference to the given Value
	* NOTE: "owner" may not be an immutable Reference
	* WARNING: "owner" may not be a null Reference
	* @TODO: Exception info */
	void SetValue(Variant owner, Variant value) const;

	////////////////
	///   Data   ///
private:

	String _name;
	String _description;
	const TypeInfo* _fieldType;
	const TypeInfo* _ownerType;
};