// CompoundInfo.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Memory/Buffers/StaticBuffer.h"
#include "../Containers/Table.h"
#include "../Functional/EnumeratorView.h"
#include "../IO/Console.h"
#include "PrimitiveInfo.h"
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

	/** Enumerates all properties of this type. */
	virtual void EnumerateProperties(const EnumeratorView<const PropertyInfo&>& enumerator) const;

	/** Searches for the given property in this type by name. */
	virtual const PropertyInfo* FindProperty(const String& name) const;

	/** Returns an Array of all data members of this type. */
	virtual Array<DataInfo> GetData() const;

	/** Enumerates all data members of this type. */
	virtual void EnumerateData(const EnumeratorView<const DataInfo&>& enumerator) const;

	/** Searches for the given data member in this type by name. */
	virtual const DataInfo* FindData(const String& name) const;

	////////////////
	///   Data   ///
private:

	struct Data
	{
		Table<String, std::size_t> PropertyTable;
		Array<PropertyInfo> Properties;
		Table<String, std::size_t> DataTable;
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

	/** Default description for properties. */
	static constexpr CString DefaultDescription = "";

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
		return this->AsMostSpecificTypeInfoBuilder();
	}

	/** Registers a field member in the default category with a default description. */
	template <typename FieldT>
	auto& Field(
		CString name,
		FieldT CompoundT::*field,
		FieldFlags flags = FF_None)
	{
		return Field(name, field, DefaultDescription, DefaultCategory, flags);
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
		return this->AsMostSpecificTypeInfoBuilder();
	}

	/** Adds a readonly property with a field getter, in the default category with a default description. */
	template <typename FieldT, WHERE(!std::is_function<FieldT>::value)>
	auto& Property(
		CString name,
		FieldT CompoundT::*field,
		std::nullptr_t /*setter*/,
		PropertyFlags flags = PF_None)
	{
		return Property(name, field, nullptr, DefaultDescription, DefaultCategory, flags);
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
		return this->AsMostSpecificTypeInfoBuilder();
	}

	/** Adds a field property with a custom setter, in the default category with a default description. */
	template <typename FieldT, typename SetT, typename SetRetT, WHERE(!std::is_function<FieldT>::value)>
	auto& Property(
		CString name,
		FieldT CompoundT::*field,
		SetRetT (CompoundT::*setter)(SetT),
		PropertyFlags flags = PF_None)
	{
		return Property(name, field, setter, DefaultDescription, DefaultCategory, flags);
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

	/** Adds a field property with a custom setter. */
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
		return this->AsMostSpecificTypeInfoBuilder();
	}

	/** Adds a read-only property with a custom getter, in the default category with a default description. */
	template <typename GetT>
	auto& Property(
		CString name,
		GetT (CompoundT::*getter)() const,
		std::nullptr_t /*setter*/,
		PropertyFlags flags = PF_None)
	{
		return Property(name, getter, nullptr, DefaultDescription, DefaultCategory, flags);
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
		return this->AsMostSpecificTypeInfoBuilder();
	}

	/** Adds a property with a custom getter and setter, in the default category with a default desciption. */
	template <typename GetT, typename SetRetT, typename SetT>
	auto& Property(
		CString name,
		GetT (CompoundT::*getter)() const,
		SetRetT (CompoundT::*setter)(SetT),
		PropertyFlags flags = PF_None)
	{
		return Property(name, getter, setter, DefaultDescription, DefaultCategory, flags);
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
		return this->AsMostSpecificTypeInfoBuilder();
	}

private:

	/** Impelements the 'ToString' function on a field getter. */
	template <typename FieldT, WHERE(!std::is_function<FieldT>::value)>
	void ImplementPropertyToString(PropertyInfo& propInfo, FieldT CompoundT::*field)
	{
		using ToStringT = Operations::ToString<FieldT>;

		if (ToStringT::Supported)
		{
			propInfo._toString = [field](const void* owner) -> String
			{
				auto pOwner = static_cast<const CompoundT*>(owner);
				String out;
				FailableOperation<ToStringT>(out, pOwner->*field);
				return out;
			};
		}
	}

	/** Implements the 'ToString' function on a method getter. */
	template <typename GetT>
	void ImplementPropertyToString(PropertyInfo& propInfo, GetT (CompoundT::*getter)() const)
	{
		using ToStringT = Operations::ToString<std::decay_t<GetT>>;

		if (ToStringT::Supported)
		{
			propInfo._toString = [getter](const void* owner) -> String
			{
				auto pOwner = static_cast<const CompoundT*>(owner);
				String out;
				FailableOperation<ToStringT>(out, (pOwner->*getter)());
				return out;
			};
		}
	}

	/** Implements the 'FromString' function with a field. */
	template <typename FieldT, WHERE(!std::is_function<FieldT>::value)>
	void ImplementPropertyFromString(PropertyInfo& propInfo, FieldT CompoundT::*field)
	{
		using FromStringT = Operations::FromString<FieldT>;

		if (FromStringT::Supported)
		{
			propInfo._fromString = [field](void* owner, const String& string) -> String
			{
				auto pOwner = static_cast<CompoundT*>(owner);
				String out;
				FailableOperation<FromStringT>(out, pOwner->*field, string);
				return out;
			};
		}
	}

	/** Implements the 'FromString' function with a field getter, and method setter. */
	template <typename FieldT, typename RetT, typename SetT, WHERE(!std::is_function<FieldT>::value)>
	void ImplementPropertyFromString(PropertyInfo& propInfo, FieldT CompoundT::*field, RetT (CompoundT::*setter)(SetT))
	{
		using FromStringT = Operations::FromString<FieldT>;

		if (FromStringT::Supported)
		{
			propInfo._fromString = [field, setter](void* owner, const String& string) -> String
			{
				auto pOwner = static_cast<CompoundT*>(owner);
				auto val = pOwner->*field;
				String out;
				FailableOperation<FromStringT>(out, val, string);
				(pOwner->*setter)(std::move(val));
				return out;
			};
		}
	}

	/** Implements the 'FromString' function with a method getter, and method setter. */
	template <typename GetT, typename RetT, typename SetT>
	void ImplementPropertyFromString(PropertyInfo& propInfo, GetT (CompoundT::*getter)() const, RetT (CompoundT::*setter)(SetT))
	{
		using FromStringT = Operations::FromString<std::decay_t<GetT>>;

		if (FromStringT::Supported)
		{
			propInfo._fromString = [getter, setter](void* owner, const String& string) -> String
			{
				auto pOwner = static_cast<CompoundT*>(owner);
				auto val = (pOwner->*getter)();
				String out;
				FailableOperation<FromStringT>(out, val, string);
				(pOwner->*setter)(std::move(val));
				return out;
			};
		}
	}

	/** Implements the 'ToArchive' function with a field getter. */
	template <typename FieldT, WHERE(!std::is_function<FieldT>::value)>
	void ImplementPropertyToArchive(PropertyInfo& propInfo, FieldT CompoundT::*field)
	{
		using ToArchiveT = Operations::ToArchive<FieldT>;

		if (ToArchiveT::Supported)
		{
			propInfo._toArchive = [field](const void* owner, ArchiveWriter& writer) -> void
			{
				auto pOwner = static_cast<const CompoundT*>(owner);
				FailableOperation<ToArchiveT>(pOwner->*field, writer);
			};
		}
	}

	/** Implements the 'ToArchive' function with a method getter. */
	template <typename GetT>
	void ImplementPropertyToArchive(PropertyInfo& propInfo, GetT (CompoundT::*getter)() const)
	{
		using ToArchiveT = Operations::ToArchive<std::decay_t<GetT>>;

		if (ToArchiveT::Supported)
		{
			propInfo._toArchive = [getter](const void* owner, ArchiveWriter& writer) -> void
			{
				auto pOwner = static_cast<const CompoundT*>(owner);
				FailableOperation<ToArchiveT>((pOwner->*getter)(), writer);
			};
		}
	}

	/** Implements the 'FromArchive' function with a field. */
	template <typename FieldT, WHERE(!std::is_function<FieldT>::value)>
	void ImplementPropertyFromArchive(PropertyInfo& propInfo, FieldT CompoundT::*field)
	{
		using FromArchiveT = Operations::FromArchive<FieldT>;

		if (FromArchiveT::Supported)
		{
			propInfo._fromArchive = [field](void* owner, const ArchiveReader& reader) -> void
			{
				auto pOwner = static_cast<CompoundT*>(owner);
				FailableOperation<FromArchiveT>(pOwner->*field, reader);
			};
		}
	}

	/** Implements the 'FromArchive' function with a field getter and method setter. */
	template <typename FieldT, typename RetT, typename SetT, WHERE(!std::is_function<FieldT>::value)>
	void ImplementPropertyFromArchive(PropertyInfo& propInfo, FieldT CompoundT::*field, RetT (CompoundT::*setter)(SetT))
	{
		using FromArchiveT = Operations::FromArchive<FieldT>;

		if (FromArchiveT::Supported)
		{
			propInfo._fromArchive = [field, setter](void* owner, const ArchiveReader& reader) -> void
			{
				auto pOwner = static_cast<CompoundT*>(owner);
				auto value = pOwner->*field;
				FailableOperation<FromArchiveT>(value, reader);
				(pOwner->*setter)(value);
			};
		}
	}

	/** Implements the 'FromArchive' function with a method getter and method setter. */
	template <typename GetT, typename RetT, typename SetT>
	void ImplementPropertyFromArchive(PropertyInfo& propInfo, GetT (CompoundT::*getter)() const, RetT (CompoundT::*setter)(SetT))
	{
		using FromArchiveT = Operations::FromArchive<std::decay_t<GetT>>;

		if (FromArchiveT::Supported)
		{
			propInfo._fromArchive = [getter, setter](void* owner, const ArchiveReader& reader) -> void
			{
				auto pOwner = static_cast<CompoundT*>(owner);
				auto value = (pOwner->*getter)();
				FailableOperation<FromArchiveT>(value, reader);
				(pOwner->*setter)(value);
			};
		}
	}

	/** Returns the offset of the given field within the compound. */
	template <typename FieldT>
	std::size_t GetFieldOffset(FieldT CompoundT::*field) const
	{
		static_assert(!std::is_function<FieldT>::value, "You cannot get the offset of a non-field.");

		// Bit of a hack, but necessary. If this becomes problematic, I can replace the field offset with a getter/setter std::function pair or something.
		// Though that would be much less performant.
		StaticBufferFor<CompoundT> fake; // Create a fake object to dereference this field from
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
		static_assert(std::is_object<SetT>::value || stde::is_reference_to_const<SetT>::value, "The setter must either accept by value or const-reference.");
	}

	////////////////
	///   Data   ///
private:

	mutable CompoundInfo::Data _data;
};

namespace Operations
{
	namespace Default
	{
		/** Default implementation of 'ToArchive', prints out data members or 'ToString'. */
		template <typename T>
		void ToArchive(const T& value, ArchiveWriter& writer)
		{
			static_assert(std::is_class<T>::value, "You can only default 'ToArchive' for reflected classes.");
			
			const CompoundInfo& type = ::TypeOf(value);
				
			// Iterate through all data members
			type.EnumerateData([&](const auto& dataInfo)
			{
				// If this data is not marked as transient
				if (dataInfo.GetDataType().implements_to_archive() && !(dataInfo.GetFlags() & DF_Transient))
				{
					// Add a node for the data member, naming it after the data member
					writer.PushValue(dataInfo.GetName(), dataInfo.GetFromOwner(value));
				}
			});
		}

		/** Default implementation of 'FromArchive'. */
		template <typename T>
		void FromArchive(T& value, const ArchiveReader& reader)
		{
			static_assert(std::is_class<T>::value, "You can only default 'FromArchive' for reflected classes.");
			static_assert(!std::is_const<T>::value, "You can't deserialize const objects.");

			const CompoundInfo& type = ::TypeOf(value);

			// Iterate through all child archives
			reader.EnumerateChildren([&](const ArchiveReader& child)
			{
				// Try to find the data that this child archive references
				if (auto data = type.FindData(child.GetName()))
				{
					if (data->GetDataType().implements_from_archive())
					{
						// Deserialize the data
						data->GetFromOwner(value).FromArchive(child);
					}
				}
			});
		}
	}
}
