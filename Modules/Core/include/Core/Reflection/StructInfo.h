// StructInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Containers/List.h"
#include "../Containers/Queue.h"
#include "../Containers/Stack.h"
#include "../Containers/Tuple.h"
#include "../Containers/Table.h"
#include "TypeInfo.h"
#include "FieldInfo.h"

/////////////////
///   Types   ///

/** Type information for structs */
class CORE_API StructInfo : public TypeInfo
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(TypeInfo);

	////////////////////////
	///   Constructors   ///
public:

	/** Creates reflection information for the given struct
	* NOTE: Do not use this outside of the registration function for a struct 
	* 'name' - The fully-qualified name of the struct */
	template <class AnyStructType>
	static StructInfo Create(const String& name)
	{		
		AnyStructType* dummy = nullptr;
		return StructInfo(dummy, name);
	}

	template <template <typename ... DependentTypes> class AnyStructTemplateType, typename ... DependentTypes>
	static StructInfo CreateTemplate(const String& name)
	{
		// @TODO: Implement this
	}

protected:

	// @TODO: Documentation
	template <class AnyStructType>
	StructInfo(AnyStructType* dummy, const String& name)
		: Super(dummy, name)
	{
		static_assert(std::is_default_constructible<AnyStructType>::value, "Structs must be default-constructible");
		static_assert(!std::is_polymorphic<AnyStructType>::value, "Structs may not be polymorphic");
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns whether this type is castable (via 'reinterpret_cast') to the given type */
	bool IsCastableTo(const TypeInfo& type) const override;

	/** Returns a list of all the fields of this type */
	FORCEINLINE const Array<FieldInfo>& GetFields() const
	{
		return _fields;
	}

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

	/** Register fields with this struct */
	template <class OwnerType, typename FieldType>
	StructInfo&& AddField(const String& name, FieldType OwnerType::*field)
	{	
		_fieldTable.Insert(name, _fields.Add(FieldInfo(field, name)));
		return std::move(This);
	}

	////////////////
	///   Data   ///
private:

	Table<String, uint32> _fieldTable;
	Array<FieldInfo> _fields;
	Array<TypeIndex> _dependentTypes;
};

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** TypeOf for String */
	template <>
	struct CORE_API TypeOf < String >
	{
		/** Defined in 'StructInfo.cpp' */
		static const StructInfo StaticTypeInfo;

		FORCEINLINE static const StructInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const StructInfo& Function(const String& /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	/** TypeOf for Array */
	template <typename T>
	struct TypeOf < Array<T> >
	{
		/** Defined below */
		static const StructInfo StaticTypeInfo;

		FORCEINLINE static const StructInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const StructInfo& Function(const Array<T>& /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	/** Register TypeInfo for Array */
	template <typename T>
	const StructInfo TypeOf<Array<T>>::StaticTypeInfo = 
		StructInfo::CreateTemplate<Array, T>("Array");

	/** TypeOf for List */
	template <typename T>
	struct TypeOf < List<T> >
	{
		/** Defined below */
		static const StructInfo StaticTypeInfo;

		FORCEINLINE static const StructInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const StructInfo& Function(const List<T>& value)
		{
			return StaticTypeInfo;
		}
	};

	/** Register TypeInfo for List */
	template <typename T>
	const StructInfo TypeOf<List<T>>::StaticTypeInfo = 
		StructInfo::CreateTemplate<List, T>("List");

	/** TypeOf for Queue */
	template <typename T>
	struct TypeOf < Queue<T> >
	{
		/** Defined below */
		static const StructInfo StaticTypeInfo;

		FORCEINLINE static const StructInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const StructInfo& Function(const Queue<T>& value)
		{
			return StaticTypeInfo;
		}
	};

	/** Register TypeInfo for Queue */
	template <typename T>
	const StructInfo TypeOf<Queue<T>>::StaticTypeInfo =
		StructInfo::CreateTemplate<Queue, T>("Queue");

	/** TypeOf for Stack */
	template <typename T>
	struct TypeOf < Stack<T> >
	{
		/** Defined below */
		static const StructInfo StaticTypeInfo;

		FORCEINLINE static const StructInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const StructInfo& Function(const Stack<T>& value)
		{
			return StaticTypeInfo;
		}
	};

	/** Register TypeInfo for Stack */
	template <typename T>
	const StructInfo TypeOf<Stack<T>>::StaticTypeInfo = 
		StructInfo::CreateTemplate<Stack, T>("Stack");

	/** TypeOf for Table */
	template <typename KeyType, typename ValueType>
	struct TypeOf < Table<KeyType, ValueType> >
	{
		/** Defined below */
		static const StructInfo StaticTypeInfo;

		FORCEINLINE static const StructInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const StructInfo& Function(const Table<KeyType, ValueType>& value)
		{
			return StaticTypeInfo;
		}
	};

	/** Register TypeInfo for Table */
	template <typename KeyType, typename ValueType>
	const StructInfo TypeOf<Table<KeyType, ValueType>>::StaticTypeInfo = 
		StructInfo::CreateTemplate<Table, KeyType, ValueType>("Table");

	/** TypeOf for Pair */
	template <typename FirstType, typename SecondType>
	struct TypeOf < Pair<FirstType, SecondType> >
	{
		/** Defined below */
		static const StructInfo StaticTypeInfo;

		FORCEINLINE static const StructInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const StructInfo& Function(const Pair<FirstType, SecondType>& value)
		{
			return StaticTypeInfo;
		}
	};

	/** Register TypeInfo for Pair */
	template <typename FirstType, typename SecondType>
	const StructInfo TypeOf<Pair<FirstType, SecondType>>::StaticTypeInfo = 
		StructInfo::CreateTemplate<Pair, FirstType, SecondType>("Pair");

	/** TypeOf for Tuple */
	template <typename ... AnyTypes>
	struct TypeOf < Tuple<AnyTypes...> >
	{
		/** Defined below */
		static const StructInfo StaticTypeInfo;

		FORCEINLINE static const StructInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const StructInfo& Function(const Tuple<AnyTypes...>& value)
		{
			return StaticTypeInfo;
		}
	};

	/** Register TypeInfo for Tuple */
	template <typename ... AnyTypes>
	const StructInfo TypeOf<Tuple<AnyTypes...>>::StaticTypeInfo =
		StructInfo::CreateTemplate<Tuple, AnyTypes...>("Tuple");
}

//////////////////
///   Macros   ///

/** Put this macro in the source file of a struct you'd like to reflect
* NOTE: The struct must use the 'REFLECTABLE_STRUCT' flag in its "Information" section */
#define STRUCT_REFLECTION(T) const ::StructInfo T::StaticTypeInfo = ::StructInfo::Create<T>(#T)

/** Put this macro in the header file a struct template you'd like to reflect
* NOTE: The struct must use the 'REFLECTABLE_STRUCT' flag in its "Information" section */
#define TEMPLATE_STRUCT_REFLECTION(T, ...) const ::StructInfo T<_VA_ARGS_>::StaticTypeInfo = ::StructInfo::CreateTemplate<T, _VA_ARGS_>(#T)