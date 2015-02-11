// FieldInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Interface.h"
#include "Unpack.h"

/** Abstract interface for handling field information */
class IFieldInfo : public Interface
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_INTERFACE;

	///////////////////
	///   Methods   ///
public:

	/** Returns the name of this field */
	virtual String GetName() const = 0;

	/** Returns a description of this field */
	virtual String GetDescription() const = 0;

	/** Returns the type information for this field */
	virtual const TypeInfo& GetFieldType() const = 0;

	/** Returns the type information for the owner of this field 
	* NOTE: The returned type may be a class or a struct */
	virtual const TypeInfo& GetOwnerType() const = 0;

	/** Returns a Reference (with the same mutability as "owner") to the value of this field on the given Reference
	* WARNING: "owner" may not be a null Reference
	* @TODO: Exception info */
	virtual Reference GetValue(const Reference& owner) const = 0;

	/** Sets the value of this field on the given Reference to the given Value
	* WARNING: "owner" may not be an immutable Reference
	* WARNING: "owner" may not be a null Reference
	* @TODO: Exception info */
	virtual void SetValue(const Reference& owner, const Value& value) const = 0;
};

/** Template class for field information */
template <class OwnerType, typename FieldType>
class FieldInfo final : public IFieldInfo
{
	///////////////////////
	///   Information   ///
public:

	friend ClassInfo;
	friend StructInfo;

	////////////////////////
	///   Constructors   ///
private:

	FieldInfo(const String& name, FieldType OwnerType::*field)
		: _name(name), _field(field)
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	String GetName() const override
	{
		return _name;
	}

	String GetDescription() const override
	{
		return _description;
	}

	const TypeInfo& GetFieldType() const override
	{
		return TypeOf<FieldType>();
	}

	const TypeInfo& GetOwnerType() const override
	{
		return TypeOf<OwnerType>();
	}

	Reference GetValue(const Reference& owner) const override
	{
		if (owner.IsImmutable())
		{
			return Unpack<const OwnerType&>(owner).*_field;
		}
		else
		{
			return Unpack<OwnerType&>(owner).*_field;
		}
	}

	void SetValue(const Reference& owner, const Value& value) const override
	{
		Unpack<OwnerType&>(owner).*_field = Unpack<const FieldType&>(value);
	}

	////////////////
	///   Data   ///
private:

	String _name;
	String _description;
	FieldType OwnerType::*_field;
};