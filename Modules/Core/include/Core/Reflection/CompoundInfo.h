// CompoundInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Containers/Table.h"
#include "TypeInfo.h"
#include "PropertyInfo.h"

/////////////////
///   Types   ///

// TODO: Documentation
class CORE_API CompoundInfo : public TypeInfo
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(TypeInfo)

	template <typename T, class TypeInfoT>
	friend struct TypeInfoBuilder;

	////////////////////////
	///   Constructors   ///
public:

	// TODO: Documentation
	template <class CompoundT>
	CompoundInfo(const TypeInfoBuilder<CompoundT, CompoundInfo>& builder)
		: Base(builder), _data(std::move(builder._data))
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

	////////////////
	///   Data   ///
private:

	struct Data
	{
		Table<String, uint32> PropertyTable;
		Array<PropertyInfo> Properties;
	} _data;
};

/** Generic TypeInfoBuilder for CompoundInfo */
template <class CompoundT>
struct TypeInfoBuilder < CompoundT, CompoundInfo > : TypeInfoBuilderBase<CompoundT, CompoundInfo>
{
	///////////////////////
	///   Information   ///
public:

	friend CompoundInfo;

	////////////////////////
	///   Constructors   ///
public:

	// TODO: Documentation
	TypeInfoBuilder(CString name)
		: TypeInfoBuilderBase<CompoundT, CompoundInfo>(name)
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	/** Adds a field that is gettable, mutably gettable, and settable. */
	template <typename FieldT, WHERE(!std::is_function<FieldT>::value)>
	auto& AddProperty(
		CString name, 
		CString description, 
		FieldT CompoundT::*field, 
		PropertyFlags flags = PF_None)
	{
		PropertyInfo property(name, description, flags);
		property._propertyType = &TypeOf<FieldT>();
		property._ownerType = &TypeOf<CompoundT>();
		property._isField = true;
		property._isPolymorphic = false;
		property._requiresCopy = false;
		property.SetMutableGetter(field);
		property.SetGetter(field);
		property.SetSetter(field);

		_data.PropertyTable[name] = _data.Properties.Add(std::move(property));

		return static_cast<TypeInfoBuilder<CompoundT>&>(self);
	}

	/** Adds a field that is gettable, but not mutably gettable or settable. */
	template <typename FieldT, WHERE(!std::is_function<FieldT>::value)>
	auto& AddProperty(
		CString name, 
		CString description, 
		FieldT CompoundT::*field, 
		std::nullptr_t, 
		PropertyFlags flags = PF_None)
	{
		PropertyInfo property(name, description, flags);
		property._propertyType = &TypeOf<FieldT>();
		property._ownerType = &TypeOf<CompoundT>();
		property._isField = true;
		property._isPolymorphic = false;
		property._requiresCopy = false;
		property.SetGetter(field);

		_data.PropertyTable[name] = _data.Properties.Add(std::move(property));

		return static_cast<TypeInfoBuilder<CompoundT>&>(self);
	}

	/** Adds a property that is gettable, but not mutably gettable or settable. */
	template <typename PropertyT>
	auto& AddProperty(
		CString name, 
		CString description, 
		PropertyT(CompoundT::*getter)() const, 
		std::nullptr_t, 
		PropertyFlags flags = PF_None)
	{
		PropertyInfo property(name, description, flags);
		property._propertyType = &TypeOf<PropertyT>();
		property._ownerType = &TypeOf<CompoundT>();
		property._isField = false;
		property._isPolymorphic = std::is_reference<PropertyT>::value && std::is_polymorphic<std::remove_reference_t<PropertyT>>::value;
		property._requiresCopy = std::is_object<PropertyT>::value;
		property.SetGetter(getter);

		_data.PropertyTable[name] = _data.Properties.Add(std::move(property));

		return static_cast<TypeInfoBuilder<CompoundT>&>(self);
	}

	/** Adds a field that is gettable and settable, but not mutably gettable. */
	template <typename FieldT, typename SetT, WHERE(!std::is_function<FieldT>::value)>
	auto& AddProperty(
		CString name, 
		CString description, 
		FieldT CompoundT::*field, 
		void (CompoundT::*setter)(SetT), 
		PropertyFlags flags = PF_None)
	{
		static_assert(std::is_same<FieldT, std::decay_t<SetT>>::value, "The setter must accept the same type as the field.");
		static_assert(!std::is_reference<SetT>::value || std::is_const<std::remove_reference_t<SetT>>::value, "The setter must either accept by value or const-reference.");

		PropertyInfo property(name, description, flags);
		property._propertyType = &TypeOf<FieldT>();
		property._ownerType = &TypeOf<CompoundT>();
		property._isField = true;
		property._isPolymorphic = false;
		property._requiresCopy = false;
		property.SetGetter(field);
		property.SetSetter(setter);

		_data.PropertyTable[name] = _data.Properties.Add(std::move(property));

		return static_cast<TypeInfoBuilder<CompoundT>&>(self);
	}

	/** Adds a property that is gettable and settable, but not mutably gettable. */
	template <typename GetT, typename SetT>
	auto& AddProperty(
		CString name,
		CString description,
		GetT(CompoundT::*getter)() const,
		void (CompoundT::*setter)(SetT),
		PropertyFlags flags = PF_None)
	{
		static_assert(std::is_same<std::decay_t<GetT>, std::decay_t<SetT>>::value, "The getter and setter must return the same type.");
		static_assert(!std::is_reference<SetT>::value || std::is_const<std::remove_reference_t<SetT>>::value, "The setter must either accept by value or const-reference.");

		PropertyInfo property(name, description, flags);
		property._propertyType = &TypeOf<GetT>();
		property._ownerType = &TypeOf<CompoundT>();
		property._isField = false;
		property._isPolymorphic = std::is_reference<GetT>::value && std::is_polymorphic<std::remove_reference_t<GetT>>::value;
		property._requiresCopy = std::is_object<GetT>::value;
		property.SetGetter(getter);
		property.SetSetter(setter);

		_data.PropertyTable[name] = _data.Properties.Add(std::move(property));

		return static_cast<TypeInfoBuilder<CompoundT>&>(self);
	}

	////////////////
	///   Data   ///
private:

	mutable CompoundInfo::Data _data;
};
