// CompoundInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Containers/Table.h"
#include "TypeInfo.h"
#include "PropertyInfo.h"

class CORE_API CompoundInfo : public TypeInfo
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(TypeInfo)

	////////////////////////
	///   Constructors   ///
protected:

	/** Constructs a new 'CompoundInfo'.
	* 'dummy' - A pointer to an instance of the type.
	* 'name' - The name of the type. */
	template <class CompoundT>
	CompoundInfo(CompoundT* dummy, CString name)
		: Super(dummy, name)
	{
		static_assert(std::is_class<CompoundT>::value, "A 'Compound' type is either a class, struct, or interface.");
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns an Array of all the properties of this type. */
	virtual Array<PropertyInfo> GetProperties() const;

	/** Searches for the given property in this type by name. */
	virtual const PropertyInfo* FindProperty(const String& name) const;

	/** Adds a field that is gettable, mutably gettable, and settable. */
	template <class OwnerT, typename FieldT, WHERE(!std::is_function<FieldT>::value)>
	auto&& AddProperty(const String& name, const String& description, FieldT OwnerT::*field)
	{
		PropertyInfo property(name, description);
		property._propertyType = &TypeOf<FieldT>();
		property._ownerType = &TypeOf<OwnerT>();
		property._isField = true;
		property._isPolymorphic = false;
		property._requiresCopy = false;
		property.SetMutableGetter(field);
		property.SetGetter(field);
		property.SetSetter(field);

		_propertyTable[name] = _properties.Add(std::move(property));

		return static_cast<TypeInfoType<OwnerT>&&>(self);
	}

	/** Adds a field that is gettable, but not mutably gettable or settable. */
	template <class OwnerT, typename FieldT, WHERE(!std::is_function<FieldT>::value)>
	auto&& AddProperty(const String& name, const String& description, FieldT OwnerT::*field, std::nullptr_t)
	{
		PropertyInfo property(name, description);
		property._propertyType = &TypeOf<FieldT>();
		property._ownerType = &TypeOf<OwnerT>();
		property._isField = true;
		property._isPolymorphic = false;
		property._requiresCopy = false;
		property.SetGetter(field);

		_propertyTable[name] = _properties.Add(std::move(property));

		return static_cast<TypeInfoType<OwnerT>&&>(self);
	}

	/** Adds a property that is gettable, but not mutably gettable or settable. */
	template <class OwnerT, typename PropertyT>
	auto&& AddProperty(const String& name, const String& description, PropertyT(OwnerT::*getter)() const, std::nullptr_t)
	{
		PropertyInfo property(name, description);
		property._propertyType = &TypeOf<PropertyT>();
		property._ownerType = &TypeOf<OwnerT>();
		property._isField = false;
		property._isPolymorphic = std::is_reference<PropertyT>::value && std::is_polymorphic<std::remove_reference_t<PropertyT>>::value;
		property._requiresCopy = std::is_object<PropertyT>::value;
		property.SetGetter(getter);

		_propertyTable[name] = _properties.Add(std::move(property));

		return static_cast<TypeInfoType<OwnerT>&&>(self);
	}

	/** Adds a field that is gettable and settable, but not mutably gettable */
	template <class OwnerT, typename FieldT, typename SetT,
		WHERE(!std::is_function<FieldT>::value),
		//WHERE(!std::is_const<FieldT>::value),
		WHERE(std::is_same<FieldT, std::decay_t<SetT>>::value),		
		WHERE(!std::is_reference<SetT>::value || std::is_const<std::remove_reference_t<SetT>>::value)>
	auto&& AddProperty(const String& name, const String& description, FieldT OwnerT::*field, void (OwnerT::*setter)(SetT))
	{
		PropertyInfo property(name, description);
		property._propertyType = &TypeOf<FieldT>();
		property._ownerType = &TypeOf<OwnerT>();
		property._isField = true;
		property._isPolymorphic = false;
		property._requiresCopy = false;
		property.SetGetter(field);
		property.SetSetter(setter);

		_propertyTable[name] = _properties.Add(std::move(property));

		return static_cast<TypeInfoType<OwnerT>&&>(self);
	}

	/** Adds a property that is gettable and settable, but not mutably gettable */
	template <class OwnerT, typename GetT, typename SetT, 
		WHERE(std::is_same<std::decay_t<GetT>, std::decay_t<SetT>>::value),
		WHERE(!std::is_reference<SetT>::value || std::is_const<std::remove_reference_t<SetT>>::value)>
	auto&& AddProperty(const String& name, const String& description, GetT(OwnerT::*getter)() const, void (OwnerT::*setter)(SetT))
	{
		PropertyInfo property(name, description);
		property._propertyType = &TypeOf<GetT>();
		property._ownerType = &TypeOf<OwnerT>();
		property._isField = false;
		property._isPolymorphic = std::is_reference<GetT>::value && std::is_polymorphic<std::remove_reference_t<GetT>>::value;
		property._requiresCopy = std::is_object<GetT>::value;
		property.SetGetter(getter);
		property.SetSetter(setter);

		_propertyTable[name] = _properties.Add(std::move(property));

		return static_cast<TypeInfoType<OwnerT>&&>(self);
	}

	////////////////
	///   Data   ///
private:

	Table<String, uint32> _propertyTable;
	Array<PropertyInfo> _properties;
};
