// CompoundInfo.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Containers/StaticBuffer.h"
#include "../Containers/Table.h"
#include "../Console.h"
#include "TypeInfo.h"
#include "DataInfo.h"
#include "PropertyInfo.h"

/////////////////
///   Types   ///

enum FieldFlags : byte
{
	FF_None = 0,				/** No special considerations need to be made for this field. */
	FF_Transient = (1 << 0),	/** This field should not be serialized. */
	FF_EditorOnly = (1 << 1)	/** This field should only be exposed to the editor. */
};

/** A 'Compound' is a type that is composed over several other types, such as a 'struct', 'class', or 'interface'. */
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

	/** Returns an Array of all data members of this type. */
	virtual Array<DataInfo> GetData() const;

	/** Searches for the given data member in this type by name. */
	virtual const DataInfo* FindData(const String& name) const;

	////////////////
	///   Data   ///
private:

	struct Data
	{
		Table<String, uint32> PropertyTable;
		Array<PropertyInfo> Properties;
		Table<String, uint32> DataTable;
		Array<DataInfo> DataMembers;
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

	/////////////////////
	///   Constants   ///
private:

	/** The default category that properties are sorted into. */
	static constexpr CString DefaultCategory = "General";

	////////////////////////
	///   Constructors   ///
public:

	TypeInfoBuilder(CString name)
		: TypeInfoBuilderBase<CompoundT, CompoundInfo>(name)
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	/** Registers the given field as a data member. */
	template <typename FieldT>
	auto& Data(
		CString name,
		FieldT CompoundT::*field,
		DataFlags flags = DF_None)
	{
		CommonAsserts<FieldT>();
		FieldAsserts<FieldT>();

		DataInfo dataInfo(name, flags);
		dataInfo._ownerType = &TypeOf<CompoundT>();
		dataInfo._dataType = &TypeOf<FieldT>();
		dataInfo._offset = GetFieldOffset(field);

		_data.DataTable[name] = _data.DataMembers.Add(std::move(dataInfo));
		return this->SelfAsMostSpecificTypeInfoBuilder();
	}

	/** Registers a field member in the default category. */
	template <typename FieldT>
	auto& Field(
		CString name,
		FieldT CompoundT::*field,
		CString description,
		FieldFlags flags = FF_None)
	{
		return Field(name, field, description, DefaultCategory, flags);
	}

	/** Registers a field member in the specified category. */
	template <typename FieldT>
	auto& Field(
		CString name,
		FieldT CompoundT::*field,
		CString description,
		CString category,
		FieldFlags flags = FF_None)
	{
		CommonAsserts<FieldT>();
		FieldAsserts<FieldT>();

		// Add the data portion of this field
		this->Data(name, field, FieldFlagsToDataFlags(flags));

		// Add the property portion of this field
		PropertyInfo propInfo(name, description, category, FieldFlagsToPropertyFlags(flags));
		propInfo._propertyType = &TypeOf<FieldT>();
		propInfo._ownerType = &TypeOf<CompoundT>();
		propInfo._isReadOnly = false;

		ImplementPropertyToString(propInfo, field);
		ImplementPropertyFromString(propInfo, field);
		ImplementPropertyToArchive(propInfo, field);
		ImplementPropertyFromArchive(propInfo, field);

		_data.PropertyTable[name] = _data.Properties.Add(std::move(propInfo));
		return this->SelfAsMostSpecificTypeInfoBuilder();
	}

	/** Adds a readonly property with a field getter, in the default category. */
	template <typename FieldT, WHERE(!std::is_function<FieldT>::value)>
	auto& Property(
		CString name,
		FieldT CompoundT::*field,
		std::nullptr_t /*setter*/,
		CString description,
		PropertyFlags flags = PF_None)
	{
		return Property(name, field, nullptr, description, DefaultCategory, flags);
	}

	/** Adds a readonly property with a field getter, in the specified category. */
	template <typename FieldT, WHERE(!std::is_function<FieldT>::value)>
	auto& Property(
		CString name,
		FieldT CompoundT::*field,
		std::nullptr_t /*setter*/,
		CString description,
		CString category,
		PropertyFlags flags = PF_None)
	{
		CommonAsserts<FieldT>();
		FieldAsserts<FieldT>();

		PropertyInfo propInfo(name, description, category, flags);
		propInfo._propertyType = &TypeOf<FieldT>();
		propInfo._ownerType = &TypeOf<CompoundT>();
		propInfo._isReadOnly = true;

		ImplementPropertyToString(propInfo, field);
		propInfo._fromString = nullptr;
		ImplementPropertyToArchive(propInfo, field);
		propInfo._fromArchive = nullptr;

		_data.PropertyTable[name] = _data.Properties.Add(std::move(propInfo));
		return this->SelfAsMostSpecificTypeInfoBuilder();
	}

	/** Adds a field property with a custom setter, in the default category. */
	template <typename FieldT, typename SetT, typename SetRetT, WHERE(!std::is_function<FieldT>::value)>
	auto& Property(
		CString name,
		FieldT CompoundT::*field,
		SetRetT (CompoundT::*setter)(SetT),
		CString description,
		PropertyFlags flags = PF_None)
	{
		return Property(name, field, setter, description, DefaultCategory, flags);
	}

	/** Adds a property with a custom setter. */
	template <typename FieldT, typename SetT, typename SetRetT, WHERE(!std::is_function<FieldT>::value)>
	auto& Property(
		CString name,
		FieldT CompoundT::*field,
		SetRetT(CompoundT::*setter)(SetT),
		CString description,
		CString category,
		PropertyFlags flags = PF_None)
	{
		using PropertyT = FieldT;
		CommonAsserts<PropertyT>();
		FieldAsserts<FieldT>();
		GetterSetterAsserts<FieldT, SetT>();

		PropertyInfo propInfo(name, description, category, flags);
		propInfo._propertyType = &TypeOf<FieldT>();
		propInfo._ownerType = &TypeOf<CompoundT>();
		propInfo._isReadOnly = false;

		ImplementPropertyToString(propInfo, field);
		ImplementPropertyFromString(propInfo, field, setter);
		ImplementPropertyToArchive(propInfo, field);
		ImplementPropertyFromArchive(propInfo, field, setter);

		_data.PropertyTable[name] = _data.Properties.Add(std::move(propInfo));
		return this->SelfAsMostSpecificTypeInfoBuilder();
	}

	/** Adds a read-only property with a custom getter, in the default category. */
	template <typename GetT>
	auto& Property(
		CString name,
		GetT (CompoundT::*getter)() const,
		std::nullptr_t /*setter*/,
		CString description,
		PropertyFlags flags = PF_None)
	{
		return Property(name, getter, nullptr, description, DefaultCategory, flags);
	}

	/** Adds a read-only property with a custom getter, in the specified category. */
	template <typename GetT>
	auto& Property(
		CString name,
		GetT (CompoundT::*getter)() const,
		std::nullptr_t /*setter*/,
		CString description,
		CString category,
		PropertyFlags flags = PF_None)
	{
		using PropertyT = std::decay_t<GetT>;
		CommonAsserts<PropertyT>();

		PropertyInfo propInfo(name, description, category, flags);
		propInfo._propertyType = &TypeOf<PropertyT>();
		propInfo._ownerType = &TypeOf<CompoundT>();
		propInfo._isReadOnly = true;

		ImplementPropertyToString(propInfo, getter);
		propInfo._fromString = nullptr;
		ImplementPropertyToArchive(propInfo, getter);
		propInfo._fromArchive = nullptr;

		_data.PropertyTable[name] = _data.Properties.Add(std::move(propInfo));
		return this->SelfAsMostSpecificTypeInfoBuilder();
	}

	/** Adds a property with a custom getter and setter, in the default category. */
	template <typename GetT, typename SetRetT, typename SetT>
	auto& Property(
		CString name,
		GetT (CompoundT::*getter)() const,
		SetRetT (CompoundT::*setter)(SetT),
		CString description,
		PropertyFlags flags = PF_None)
	{
		return Property(name, getter, setter, description, DefaultCategory, flags);
	}

	/** Adds a property with a custom getter and setter. */
	template <typename GetT, typename SetRetT, typename SetT>
	auto& Property(
		CString name,
		GetT(CompoundT::*getter)() const,
		SetRetT(CompoundT::*setter)(SetT),
		CString description,
		CString category,
		PropertyFlags flags = PF_None)
	{
		using PropertyT = std::decay_t<GetT>;
		CommonAsserts<PropertyT>();
		GetterSetterAsserts<GetT, SetT>();

		PropertyInfo propInfo(name, description, category, flags);
		propInfo._propertyType = &TypeOf<PropertyT>();
		propInfo._ownerType = &TypeOf<CompoundT>();
		propInfo._isReadOnly = false;

		ImplementPropertyToString(propInfo, getter);
		ImplementPropertyFromString(propInfo, getter, setter);
		ImplementPropertyToArchive(propInfo, getter);
		ImplementPropertyFromArchive(propInfo, getter, setter);

		_data.PropertyTable[name] = _data.Properties.Add(std::move(propInfo));
		return this->SelfAsMostSpecificTypeInfoBuilder();
	}

private:

	/** Impelements the 'ToString' function on a field getter. */
	template <typename FieldT, WHERE(!std::is_function<FieldT>::value)>
	void ImplementPropertyToString(PropertyInfo& propInfo, FieldT CompoundT::*field)
	{
		propInfo._toString = [field](const void* owner) -> String
		{
			auto pOwner = static_cast<const CompoundT*>(owner);
			return ToString(pOwner->*field);
		};
	}

	/** Implements the 'ToString' function on a method getter. */
	template <typename GetT>
	void ImplementPropertyToString(PropertyInfo& propInfo, GetT (CompoundT::*getter)() const)
	{
		propInfo._toString = [getter](const void* owner) -> String
		{
			auto pOwner = static_cast<const CompoundT*>(owner);
			return ToString((pOwner->*getter)());
		};
	}

	/** Implements the 'FromString' function with a field. */
	template <typename FieldT, WHERE(!std::is_function<FieldT>::value)>
	void ImplementPropertyFromString(PropertyInfo& propInfo, FieldT CompoundT::*field)
	{
		propInfo._fromString = [field](void* owner, const String& string) -> String
		{
			auto pOwner = static_cast<CompoundT*>(owner);
			return FromString(pOwner->*field, string);
		};
	}

	/** Implements the 'FromString' function with a field getter, and method setter. */
	template <typename FieldT, typename RetT, typename SetT, WHERE(!std::is_function<FieldT>::value)>
	void ImplementPropertyFromString(PropertyInfo& propInfo, FieldT CompoundT::*field, RetT (CompoundT::*setter)(SetT))
	{
		propInfo._fromString = [field, setter](void* owner, const String& string) -> String
		{
			auto pOwner = static_cast<CompoundT*>(owner);
			auto val = pOwner->*field;
			String remainder = FromString(val, string);
			(pOwner->*setter)(std::move(val));
			return remainder;
		};
	}

	/** Implements the 'FromString' function with a method getter, and method setter. */
	template <typename GetT, typename RetT, typename SetT>
	void ImplementPropertyFromString(PropertyInfo& propInfo, GetT (CompoundT::*getter)() const, RetT (CompoundT::*setter)(SetT))
	{
		propInfo._fromString = [getter, setter](void* owner, const String& string) -> String
		{
			auto pOwner = static_cast<CompoundT*>(owner);
			auto val = (pOwner->*getter)();
			String remainder = FromString(val, string);
			(pOwner->*setter)(std::move(val));
			return remainder;
		};
	}

	/** Implements the 'ToArchive' function with a field getter. */
	template <typename FieldT, WHERE(!std::is_function<FieldT>::value)>
	void ImplementPropertyToArchive(PropertyInfo& propInfo, FieldT CompoundT::*field)
	{
		propInfo._toArchive = [field](const void* owner, ArchiveNode& node) -> void
		{
			auto pOwner = static_cast<const CompoundT*>(owner);
			ToArchive(pOwner->*field, node);
		};
	}

	/** Implements the 'ToArchive' function with a method getter. */
	template <typename GetT>
	void ImplementPropertyToArchive(PropertyInfo& propInfo, GetT (CompoundT::*getter)() const)
	{
		propInfo._toArchive = [getter](const void* owner, ArchiveNode& node) -> void
		{
			auto pOwner = static_cast<const CompoundT*>(owner);
			ToArchive((pOwner->*getter)(), node);
		};
	}

	/** Implements the 'FromArchive' function with a field. */
	template <typename FieldT, WHERE(!std::is_function<FieldT>::value)>
	void ImplementPropertyFromArchive(PropertyInfo& propInfo, FieldT CompoundT::*field)
	{
		propInfo._fromArchive = [field](void* owner, const ArchiveNode& node) -> void
		{
			auto pOwner = static_cast<CompoundT*>(owner);
			FromArchive(pOwner->*field, node);
		};
	}

	/** Implements the 'FromArchive' function with a field getter and method setter. */
	template <typename FieldT, typename RetT, typename SetT, WHERE(!std::is_function<FieldT>::value)>
	void ImplementPropertyFromArchive(PropertyInfo& propInfo, FieldT CompoundT::*field, RetT (CompoundT::*setter)(SetT))
	{
		propInfo._fromArchive = [field, setter](void* owner, const ArchiveNode& node) -> void
		{
			auto pOwner = static_cast<CompoundT*>(owner);
			auto value = pOwner->*field;
			FromArchive(value, node);
			(pOwner->*setter)(value);
		};
	}

	/** Implements the 'FromArchive' function with a method getter and method setter. */
	template <typename GetT, typename RetT, typename SetT>
	void ImplementPropertyFromArchive(PropertyInfo& propInfo, GetT (CompoundT::*getter)() const, RetT (CompoundT::*setter)(SetT))
	{
		propInfo._fromArchive = [getter, setter](void* owner, const ArchiveNode& node) -> void
		{
			auto pOwner = static_cast<CompoundT*>(owner);
			auto value = (pOwner->*getter)();
			FromArchive(value, node);
			(pOwner->*setter)(value);
		};
	}

	/** Returns the offset of the given field within the compound. */
	template <typename FieldT>
	std::size_t GetFieldOffset(FieldT CompoundT::*field) const
	{
		static_assert(!std::is_function<FieldT>::value, "You cannot get the offset of a non-field.");

		// Bit of a hack, but necessary. If this becomes problematic, I can replace the field offset with a getter/setter std::function pair or something.
		// Though that would be much less performant.
		StaticBuffer<sizeof(CompoundT)> fake; // Create a fake object to dereference this field from
		FieldT* member = &(fake.template GetPointer<CompoundT>()->*field);
		
		return reinterpret_cast<byte*>(member) - fake.GetPointer(); // Calculate the offset of the field from the base
	}

	/** Translates the given FieldFlags into the relevant DataFlags. */
	static DataFlags FieldFlagsToDataFlags(FieldFlags flags)
	{
		auto dFlags = DF_None;

		if (flags & FF_Transient)
		{
			dFlags = DataFlags(dFlags | DF_Transient);
		}

		return dFlags;
	}

	/** Translates the given FieldFlags to the relevant PropertyFlags. */
	static PropertyFlags FieldFlagsToPropertyFlags(FieldFlags flags)
	{
		auto pFlags = PF_None;

		if (flags & FF_EditorOnly)
		{
			pFlags = PropertyFlags(pFlags | PF_EditorOnly);
		}

		return pFlags;
	}

	/** Assertions common to all types of members. */
	template <typename PropertyT>
	static void CommonAsserts()
	{
		static_assert(!std::is_polymorphic<std::decay_t<PropertyT>>::value, "Compounds may not contain polymorphic types.");
	}

	/** Assertions common to field members. */
	template <typename DataT>
	static void FieldAsserts()
	{
		static_assert(!std::is_reference<DataT>::value, "You may not have references as data.");
		static_assert(!std::is_function<DataT>::value, "You can't register a member function as data.");
	}

	/** Assertions common to all getter/setter functions */
	template <typename GetT, typename SetT>
	static void GetterSetterAsserts()
	{
		static_assert(std::is_same<std::decay_t<GetT>, std::decay_t<SetT>>::value, "The setter must accept the same type as the getter.");
		static_assert(std::is_object<SetT>::value || stde::is_const_reference<SetT>::value, "The setter must either accept by value or const-reference.");
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
		/** Default implementation of 'ToArchive', prints out data members or 'ToString'. */
		template <typename T>
		void ToArchive(const T& value, ArchiveNode& node)
		{
			if(std::is_class<T>::value)
			{
				// Type is compound, serialize its data
				const auto& type = reinterpret_cast<const CompoundInfo&>(::TypeOf(value));
				
				// Iterate through all data members
				for (const auto& dataInfo : type.GetData())
				{
					// If this data is not marked as transient
					if (!(dataInfo.GetFlags() & DF_Transient))
					{
						// Add a node for the data, naming it after the data
						auto dataNode = node.AddChild(dataInfo.GetName());

						// Serialize the property to the node TODO: Figure out why I need to explicitly initialize "ImmutableVariant" here
						dataInfo.Get(ImmutableVariant{ value }).ToArchive(*dataNode);
					}
				}
			}
			else
			{
				// Type is primitive, just serialize it to a string
				node.SetValue(::ToString(value).Cstr());
			}
		}

		/** Default implementation of 'FromArchive'. */
		template <typename T>
		void FromArchive(T& value, const ArchiveNode& node)
		{
			if (std::is_class<T>::value)
			{
				const auto& type = reinterpret_cast<const CompoundInfo&>(::TypeOf(value));

				// Iterate through all child nodes
				for (auto pChild : node.GetChildren())
				{
					// Try to find the data that this node references
					if (auto data = type.FindData(pChild->GetName()))
					{
						// Deserialize the data
						data->Get(Variant{ value }).FromArchive(*pChild);
					}
					else
					{
						// This property does not exist, give a warning
						Console::Warning("The data member '@' does not exist on the type '@'.", pChild->GetName(), type);
					}
				}
			}
			else
			{
				// This node must hold a value, get the value from this node
				::FromString(value, node.GetValue());
			}
		}
	}
}
