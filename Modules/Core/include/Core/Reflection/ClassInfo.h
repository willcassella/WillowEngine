// ClassInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Containers/Table.h"
#include "TypeInfo.h"
#include "FieldInfo.h"

/** Type information for classes */
class CORE_API ClassInfo : public TypeInfo
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(TypeInfo);

	////////////////////////
	///   Constructors   ///
public:

	/** Creates reflection information for the given class
	* NOTE: Do not use this outside of the registration function for a class
	* 'name' - The fully-qualified name of the class */
	template <class AnyClass>
	static ClassInfo Create(const String& name)
	{
		AnyClass* dummy = nullptr;
		return ClassInfo(dummy, name);
	}

protected:

	// @TODO: Documentation
	template <class AnyClass>
	ClassInfo(AnyClass* dummy, const String& name)
		: Super(dummy, name), _base(&AnyClass::Super::StaticTypeInfo)
	{
		static_assert(std::is_base_of<Object, AnyClass>::value, "Classes must be extend 'Object'");
	}

private:

	/** Special constructor used to construct TypeInfo for "Object" class */
	explicit ClassInfo(Object* dummy, const String& name)
		: Super(dummy, name), _base(nullptr)
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns whether this type castable (via reinterpret_cast) to the given type */
	bool IsCastableTo(const TypeInfo& type) const override;

	/** Returns a list of all the fields of this type */
	FORCEINLINE const Array<FieldInfo>& GetFields() const
	{
		return _fields;
	}

	/** Returns whether this class extends the given class */
	bool Extends(const ClassInfo& type) const;

	/** Returns whether this class implements the given interface */
	bool Implements(const InterfaceInfo& interf) const;

	/** Searches for the field in this type */
	FORCEINLINE const FieldInfo* FindField(const String& name) const
	{
		auto index = _fieldTable.Find(name);
		if (index)
		{
			return &_fields[*index];
		}
		else
		{
			return nullptr;
		}
	}

	/** Adds a field to this type's fields
	* NOTE: Only register fields that were added by this class, DO NOT include base class fields */
	template <class OwnerType, typename FieldType>
	FORCEINLINE ClassInfo&& AddField(const String& name, FieldType OwnerType::*field)
	{
		_fieldTable.Insert(name, _fields.Add(FieldInfo(field, name)));
		return std::move(This);
	}

	/** Returns whether this class extends the given class */
	template <class AnyClass>
	FORCEINLINE bool Extends() const
	{
		return Extends(AnyClass::StaticTypeInfo);
	}
	
	/** Returns whether this class implements the given interface */
	template <class AnyInterface>
	FORCEINLINE bool Implements() const
	{
		return Implements(AnyInterface::StaticTypeInfo);
	}

	////////////////
	///   Data   ///
protected:

	Table<String, uint32> _fieldTable;
	Array<FieldInfo> _fields;
	Array<const InterfaceInfo*> _interfaces;
	const ClassInfo* _base;
};

//////////////////
///   Macros   ///

/** Put this macro into the source file of a class you'd like to reflect
* NOTE: The class muse use the 'REFLECTABLE_CLASS' flag in it's header */
#define CLASS_REFLECTION(T) const ::ClassInfo T::StaticTypeInfo = ::ClassInfo::Create<T>(#T)