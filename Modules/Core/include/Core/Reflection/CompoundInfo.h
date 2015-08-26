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

	/** Adds a field property. */
	template <typename FieldT, WHERE(!std::is_function<FieldT>::value)>
	auto& AddProperty(
		CString name, 
		CString description, 
		FieldT CompoundT::*field,
		PropertyFlags flags = PF_None)
	{
		CommonAsserts<FieldT>();
		FieldAsserts<FieldT>();

		PropertyInfo property(name, description, flags);
		property._propertyType = &TypeOf<FieldT>();
		property._ownerType = &TypeOf<CompoundT>();

		property._fieldGetter = [field](const void* owner) -> const void*
		{
			auto pOwner = static_cast<const CompoundT*>(owner);
			return &(pOwner->*field);
		};
		if (std::is_copy_assignable<FieldT>::value)
		{
			property._access = PropertyAccess::Field;
			property._setter = [field](void* owner, const void* value) -> void
			{
				auto pOwner = static_cast<CompoundT*>(owner);
				auto pValue = static_cast<const FieldT*>(value);
				Implementation::Assign<FieldT, const FieldT&>::Function(pOwner->*field, *pValue);
			};
		}
		else
		{
			property._access = PropertyAccess::NoSetField;
			property._setter = nullptr;
		}

		ImplementToString(property, field);
		property._fromString = [field](void* owner, const String& string) -> String
		{
			auto pOwner = static_cast<CompoundT*>(owner);
			return FromString(pOwner->*field, string);
		};
		ImplementToArchive(property, field);

		_data.PropertyTable[name] = _data.Properties.Add(std::move(property));
		return static_cast<TypeInfoBuilder<CompoundT>&>(self);
	}

	/** Adds a readonly property with a field getter. */
	template <typename FieldT, WHERE(!std::is_function<FieldT>::value)>
	auto& AddProperty(
		CString name,
		CString description,
		FieldT CompoundT::*field,
		std::nullptr_t /*setter*/,
		PropertyFlags flags = PF_None)
	{
		CommonAsserts<FieldT>();
		FieldAsserts<FieldT>();
		
		PropertyInfo property(name, description, flags);
		property._propertyType = &TypeOf<FieldT>();
		property._ownerType = &TypeOf<CompoundT>();
		property._access = PropertyAccess::ReadOnlyProperty;

		property._fieldGetter = nullptr;
		property._setter = nullptr;
		ImplementToString(property, field);
		property._fromString = nullptr;
		ImplementToArchive(property, field);

		_data.PropertyTable[name] = _data.Properties.Add(std::move(property));
		return static_cast<TypeInfoBuilder<CompoundT>&>(self);
	}

	/** Adds a property with a custom setter. */
	template <typename FieldT, typename SetT, typename SetRetT, WHERE(!std::is_function<FieldT>::value)>
	auto& AddProperty(
		CString name,
		CString description,
		FieldT CompoundT::*field,
		SetRetT (CompoundT::*setter)(SetT),
		PropertyFlags flags = PF_None)
	{
		using PropertyT = FieldT;
		CommonAsserts<PropertyT>();
		FieldAsserts<FieldT>();
		GetterSetterAsserts<FieldT, SetT>();

		PropertyInfo property(name, description, flags);
		property._propertyType = &TypeOf<PropertyT>();
		property._ownerType = &TypeOf<CompoundT>();
		property._access = PropertyAccess::Property;

		property._fieldGetter = nullptr;
		ImplementSetter(property, setter);
		ImplementToString(property, field);
		ImplementFromString(property, field, setter);
		ImplementToArchive(property, field);

		_data.PropertyTable[name] = _data.Properties.Add(std::move(property));
		return static_cast<TypeInfoBuilder<CompoundT>&>(self);
	}

	/** Adds a readonly property with a custom getter. */
	template <typename PropertyT>
	auto& AddProperty(
		CString name,
		CString description,
		PropertyT (CompoundT::*getter)() const,
		std::nullptr_t /*setter*/,
		PropertyFlags flags = PF_None)
	{
		CommonAsserts<PropertyT>();

		PropertyInfo property(name, description, flags);
		property._propertyType = &TypeOf<PropertyT>();
		property._ownerType = &TypeOf<CompoundT>();
		property._access = PropertyAccess::ReadOnlyProperty;

		property._fieldGetter = nullptr;
		property._setter = nullptr;
		ImplementToString(property, getter);
		property._fromString = nullptr;
		ImplementToArchive(property, getter);

		_data.PropertyTable[name] = _data.Properties.Add(std::move(property));
		return static_cast<TypeInfoBuilder<CompoundT>&>(self);
	}

	/** Adds a property with a custom getter and setter. */
	template <typename GetT, typename SetRetT, typename SetT>
	auto& AddProperty(
		CString name,
		CString description,
		GetT (CompoundT::*getter)() const,
		SetRetT (CompoundT::*setter)(SetT),
		PropertyFlags flags = PF_None)
	{
		using PropertyT = std::decay_t<GetT>;
		CommonAsserts<PropertyT>();
		GetterSetterAsserts<GetT, SetT>();

		PropertyInfo property(name, description, flags);
		property._propertyType = &TypeOf<PropertyT>();
		property._ownerType = &TypeOf<CompoundT>();
		property._access = PropertyAccess::Property;

		property._fieldGetter = nullptr;
		ImplementSetter(property, setter);
		ImplementToString(property, getter);
		ImplementFromString(property, getter, setter);
		ImplementToString(property, getter);

		_data.PropertyTable[name] = _data.Properties.Add(std::move(property));
		return static_cast<TypeInfoBuilder<CompoundT>&>(self);
	}

private:

	/** Implements the setter wrapper for a setter method. */
	template <typename RetT, typename SetT>
	void ImplementSetter(PropertyInfo& property, RetT (CompoundT::*setter)(SetT))
	{
		property._setter = [setter](void* owner, const void* value) -> void
		{
			auto pOwner = static_cast<CompoundT*>(owner);
			auto pValue = static_cast<const SetT*>(value);
			(pOwner->*setter)(*pValue);
		};
	}

	/** Impelements the 'ToString' function on a field getter. */
	template <typename FieldT, WHERE(!std::is_function<FieldT>::value)>
	void ImplementToString(PropertyInfo& property, FieldT CompoundT::*field)
	{
		property._toString = [field](const void* owner) -> String
		{
			auto pOwner = static_cast<const CompoundT*>(owner);
			return ToString(pOwner->*field);
		};
	}

	/** Implements the 'ToString' function on a method getter. */
	template <typename GetT>
	void ImplementToString(PropertyInfo& property, GetT (CompoundT::*getter)() const)
	{
		property._toString = [getter](const void* owner) -> String
		{
			auto pOwner = static_cast<const CompoundT*>(owner);
			return ToString((pOwner->*getter)());
		};
	}

	/** Implements the 'FromString' function with a field getter, and method setter. */
	template <typename FieldT, typename RetT, typename SetT, WHERE(!std::is_function<FieldT>::value)>
	void ImplementFromString(PropertyInfo& property, FieldT CompoundT::*field, RetT (CompoundT::*setter)(SetT))
	{
		property._fromString = [field, setter](void* owner, const String& string) -> String
		{
			auto pOwner = static_cast<CompoundT*>(owner);
			auto val = pOwner->*field;
			String remainder = FromString(val, string);
			(pOwner->*setter)(std::move(val));
			return std::move(remainder);
		};
	}

	/** Implements the 'FromString' function with a method getter, and method setter. */
	template <typename GetT, typename RetT, typename SetT>
	void ImplementFromString(PropertyInfo& property, GetT (CompoundT::*getter)() const, RetT (CompoundT::*setter)(SetT))
	{
		property._fromString = [getter, setter](void* owner, const String& string) -> String
		{
			auto pOwner = static_cast<CompoundT*>(owner);
			auto val = (pOwner->*getter)();
			String remainder = FromString(val, string);
			(pOwner->*setter)(std::move(val));
			return std::move(remainder);
		};
	}

	/** Implements the 'ToArchive' function with a field getter. */
	template <typename FieldT, WHERE(!std::is_function<FieldT>::value)>
	void ImplementToArchive(PropertyInfo& property, FieldT CompoundT::*field)
	{
		property._toArchive = [field](const void* owner, ArchNode& node) -> void
		{
			auto pOwner = static_cast<const CompoundT*>(owner);
			ToArchive(pOwner->*field, node);
		};
	}

	/** Implements the 'ToArchive' function with a method getter. */
	template <typename GetT>
	void ImplementToArchive(PropertyInfo& property, GetT (CompoundT::*getter)() const)
	{
		property._toArchive = [getter](const void* owner, ArchNode& node) -> void
		{
			auto pOwner = static_cast<const CompoundT*>(owner);
			ToArchive((pOwner->*getter)(), node);
		};
	}

	/** Assertions common to all types of properties. */
	template <typename PropertyT>
	void CommonAsserts() const
	{
		static_assert(!std::is_polymorphic<std::decay_t<PropertyT>>::value, "Compounds may not contain polymorphic types.");
	}

	/** Assertsion common to field properties */
	template <typename PropertyT>
	void FieldAsserts() const
	{
		static_assert(!std::is_reference<PropertyT>::value, "You may not have references as fields.");
	}

	/** Assertions common to all getter/setter functions */
	template <typename GetT, typename SetT>
	void GetterSetterAsserts() const
	{
		static_assert(std::is_same<std::decay_t<GetT>, std::decay_t<SetT>>::value, "The setter must accept the same type as the getter.");
		static_assert(std::is_object<SetT>::value || stdEXT::is_const_reference<SetT>::value, "The setter must either accept by value or const-reference.");
	}

	////////////////
	///   Data   ///
private:

	mutable CompoundInfo::Data _data;
};

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	namespace Default
	{
		/** Default implementation of 'ToArchive', prints out properties or 'ToString'. */
		template <typename T>
		void ToArchive(const T& value, ArchNode& node)
		{
			if(std::is_class<T>::value)
			{
				// Type is compound, serialize its properties
				const auto& pType = reinterpret_cast<const CompoundInfo&>(::TypeOf(value));
				{
					for (const auto& propInfo : pType.GetProperties())
					{
						// If we can serialize this property
						if (propInfo.GetAccess() != PropertyAccess::ReadOnlyProperty && !(propInfo.GetFlags() & PF_NoSerialize))
						{
							// Add a node for the property, naming it after the property
							auto& propNode = node.AddNode(propInfo.GetName());

							// Serialize the property to the node TODO: Figure out why I need to explicitly initialize "ImmutableVariant" here
							propInfo.Get(ImmutableVariant{ value }).ToArchive(propNode);
						}
					}
				}
			}
			else
			{
				// Type is primitive, just serialize it to a string
				node.SetValue(::ToString(value));
			}
		}
	}
}
