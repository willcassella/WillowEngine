// CompoundInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Containers/Table.h"
#include "PropertyInfo.h"

class CORE_API CompoundInfo : public TypeInfo
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(TypeInfo);

	//////////////////////
	///   InnerTypes   ///
private:

	// @TODO: Description
	template <class OwnerType>
	using TypeInfoType = std::add_rvalue_reference_t<std::decay_t<decltype(TypeOf<OwnerType>())>>;

	////////////////////////
	///   Constructors   ///
protected:

	// @TODO: Documentation
	template <class AnyCompoundType>
	CompoundInfo(AnyCompoundType* dummy, const String& name)
		: Super(dummy, name)
	{
		static_assert(std::is_class<AnyCompoundType>::value, "A 'Compound' type is either a class, struct, or interface.");
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns an Array of all the properties of this type. */
	virtual Array<PropertyInfo> GetProperties() const;

	/** Searches for the given property in this type by name. */
	virtual const PropertyInfo* FindProperty(const String& name) const;

	/** Adds a field that is gettable, mutably gettable, and settable. */
	template <class OwnerType, typename FieldType>
	auto AddProperty(const String& name, const String& description, FieldType OwnerType::*field)
	{
		return static_cast<TypeInfoType<OwnerType>>(self);
	}

	/** Adds a field that is gettable, but not mutably gettable or settable. */
	template <class OwnerType, typename FieldType>
	auto AddProperty(const String& name, const String& description, FieldType OwnerType::*field, std::nullptr_t)
	{
		PropertyInfo property(name, description);
		property._ownerType = &TypeOf<OwnerType>(); // Not safe to use 'this', because 'this' will be moved
		//property._propertyType = TypeOf<FieldType>();

		//_propertyTable.Insert(name, _properties.Add(PropertyInfo(name, description, field)));
		return static_cast<TypeInfoType<OwnerType>>(self);
	}

	/** Adds a property that is gettable, but not mutably gettable or settable. */
	template <class OwnerType, typename PropertyType>
	auto AddProperty(const String& name, const String& description, PropertyType(OwnerType::*getter)() const, std::nullptr_t)
	{
		return static_cast<TypeInfoType<OwnerType>>(self);
	}

	/** Adds a field that is gettable and settable, but not mutably gettable */
	template <class OwnerType, typename FieldType, typename SetType,
		WHERE(std::is_same<FieldType, std::decay_t<SetType>>::value), // Ensure 'FieldType' and 'SetType' are the same type
		WHERE(!std::is_reference<SetType>::value || std::is_const<std::remove_reference_t<SetType>>::value)>
	auto AddProperty(const String& name, const String& description, FieldType OwnerType::*field, void (OwnerType::*setter)(SetType))
	{

	}

	template <class OwnerType, typename PGetType, typename PSetType, 
		WHERE(std::is_same<std::decay_t<PGetType>, std::decay_t<PSetType>>::value)>
	auto AddProperty(const String& name, const String& description, PGetType(OwnerType::*getter)() const, void (OwnerType::*setter)(PSetType))
	{
		return static_cast<TypeInfoType<OwnerType>>(self);
	}

	////////////////
	///   Data   ///
private:

	Table<String, uint32> _propertyTable;
	Array<PropertyInfo> _properties;
};
