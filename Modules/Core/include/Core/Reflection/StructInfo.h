// StructInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "TypeInfo.h"
#include "FieldInfo.h"

/////////////////
///   Types   ///

/** Type information for structs */
class CORE_API StructInfo final : public TypeInfo
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
		static_assert(std::is_default_constructible<AnyStructType>::value, "Structs must be default-constructible");
		static_assert(!std::is_polymorphic<AnyStructType>::value, "Structs may not be polymorphic");
		return StructInfo(sizeof(AnyStructType), name, &StackFactory<AnyStructType>, &HeapFactory<AnyStructType>);
	}

	template <template <typename ... DependentTypes> class AnyStructTemplateType, typename ... DependentTypes>
	static StructInfo CreateTemplate(const String& name)
	{
		
	}

	StructInfo(const StructInfo& copy) = delete;
	StructInfo(StructInfo&& move);
	~StructInfo() override;

private:

	StructInfo(uint32 size, const String& name, Value(*stackFactory)(), Variant(*heapFactory)());

	///////////////////
	///   Methods   ///
public:

	/** Returns whether this type is abstract
	* i.e - it has at least one pure virtual function
	* NOTE: Always returns false - structs are never abstract */
	bool IsAbstract() const override;

	/** Returns whether this type is polymorphic 
	* NOTE: Always returns false - structs are never polymorphic */
	bool IsPolymorphic() const override;

	/** Returns whether this type is instantiable via 'Instantiate()'
	* NOTE: Always returns true - structs are always instantiable */
	bool IsInstantiable() const override;

	/** Returns whether this type is castable (via 'reinterpret_cast') to the given type */
	bool IsCastableTo(const TypeInfo& type) const override;

	/** Returns an instance of this struct, allocated on the stack */
	Value StackInstance() const override;

	/** Returns a reference to an instance of this struct allocated on the heap
	* NOTE: Callee has ownership over the lifetime of returned value (it must be deleted manually) */
	Variant HeapInstance() const override;

	/** Returns a list of all the fields of this type */
	Array<const IFieldInfo*> GetFields() const;

	/** Searches for the field in this type */
	const IFieldInfo* FindField(const String& name) const;

	/** Register fields with this struct */
	template <class OwnerType, typename FieldType>
	StructInfo&& AddField(const String& name, FieldType OwnerType::*field)
	{	
		_fields[name] = new FieldInfo<OwnerType, FieldType>(name, field);
		return std::move(This);
	}

	/////////////////////
	///   Operators   ///
public:

	StructInfo& operator=(const StructInfo& copy) = delete;
	StructInfo& operator=(StructInfo&& move) = delete;

	////////////////
	///   Data   ///
private:

	Table<String, IFieldInfo*> _fields;
	Array<const TypeInfo*> _dependentTypes;
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

		FORCEINLINE static const TypeInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const TypeInfo& Function(const String& value)
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

		FORCEINLINE static const TypeInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const TypeInfo& Function(const Array<T>& value)
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

		FORCEINLINE static const TypeInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const TypeInfo& Function(const List<T>& value)
		{
			return StaticTypeInfo;
		}
	};

	/** Register TypeInfo for List */
	template <typename T>
	const StructInfo TypeOf<List<T>>::StaticTypeInfo = 
		StructInfo::CreateTemplate<List, T>("List");

	/** TypeOf for Queue */
	template <typename T, template <typename F> class StorageType>
	struct TypeOf < Queue<T, StorageType> >
	{
		/** Defined below */
		static const StructInfo StaticTypeInfo;

		FORCEINLINE static const TypeInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const TypeInfo& Function(const Queue<T, StorageType>& value)
		{
			return StaticTypeInfo;
		}
	};

	/** Register TypeInfo for Queue */
	//template <typename T, template <typename F> class StorageType>
	//const StructInfo TypeOf<Queue<T, StorageType>>::StaticTypeInfo = StructInfo::CreateTemplate<Queue<

	/** TypeOf for Stack */
	template <typename T, template <typename F> class StorageType>
	struct TypeOf < Stack<T, StorageType> >
	{
		/** Defined below */
		static const StructInfo StaticTypeInfo;

		FORCEINLINE static const TypeInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const TypeInfo& Function(const Stack<T, StorageType>& value)
		{
			return StaticTypeInfo;
		}
	};

	/** Register TypeInfo for Stack */
	template <typename T, template <typename F> class StorageType>
	const StructInfo TypeOf<Stack<T, StorageType>>::StaticTypeInfo = 
		StructInfo::Create<Stack<T, StorageType>>(String::Format("Stack<@, @>", ::TypeOf<T>().GetName(), ::TypeOf<StorageType<T>>().GetName()));

	/** TypeOf for Table */
	template <typename KeyType, typename ValueType>
	struct TypeOf < Table<KeyType, ValueType> >
	{
		/** Defined below */
		static const StructInfo StaticTypeInfo;

		FORCEINLINE static const TypeInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const TypeInfo& Function(const Table<KeyType, ValueType>& value)
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

		FORCEINLINE static const TypeInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const TypeInfo& Function(const Pair<FirstType, SecondType>& value)
		{
			return StaticTypeInfo;
		}
	};

	/** Register TypeInfo for Pair */
	template <typename FirstType, typename SecondType>
	const StructInfo TypeOf<Pair<FirstType, SecondType>>::StaticTypeInfo = 
		StructInfo::CreateTemplate<Pair, FirstType, SecondType>("Pair");

	/** TypeOf for 3 Tuple */
	template <typename FirstType, typename SecondType, typename ThirdType>
	struct TypeOf < Tuple<FirstType, SecondType, ThirdType> >
	{
		/** Defined below */
		static const StructInfo StaticTypeInfo;

		FORCEINLINE static const TypeInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const TypeInfo& Function(const Tuple<FirstType, SecondType, ThirdType>& value)
		{
			return StaticTypeInfo;
		}
	};

	/** Register TypeInfo for 3 Tuple */
	template <typename FirstType, typename SecondType, typename ThirdType>
	const StructInfo TypeOf<Tuple<FirstType, SecondType, ThirdType>>::StaticTypeInfo = 
		StructInfo::CreateTemplate<Tuple, FirstType, SecondType, ThirdType>("Tuple");

	/** TypeInfo for 4 Tuple */
	template <typename FirstType, typename SecondType, typename ThirdType, typename FourthType>
	struct TypeOf < Tuple<FirstType, SecondType, ThirdType, FourthType> >
	{
		/** Defined below */
		static const StructInfo StaticTypeInfo;

		FORCEINLINE static const TypeInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const TypeInfo& Function(const Tuple<FirstType, SecondType, ThirdType, FourthType>& value)
		{
			return StaticTypeInfo;
		}
	};

	/** Register TypeInfo for 4 Tuple */
	template <typename FirstType, typename SecondType, typename ThirdType, typename FourthType>
	const StructInfo TypeOf<Tuple<FirstType, SecondType, ThirdType, FourthType>>::StaticTypeInfo = 
		StructInfo::CreateTemplate<Tuple, FirstType, SecondType, ThirdType, FourthType>("Tuple");

	/** TypeInfo for 5 Tuple */
	template <typename FirstType, typename SecondType, typename ThirdType, typename FourthType, typename FifthType>
	struct TypeOf < Tuple<FirstType, SecondType, ThirdType, FourthType, FifthType> >
	{
		/** Defined below */
		static const StructInfo StaticTypeInfo;

		FORCEINLINE static const TypeInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const TypeInfo& Function(const Tuple<FirstType, SecondType, ThirdType, FourthType, FifthType>& value)
		{
			return StaticTypeInfo;
		}
	};

	/** Register TypeInfo for 5 Tuple */
	template <typename FirstType, typename SecondType, typename ThirdType, typename FourthType, typename FifthType>
	const StructInfo TypeOf<Tuple<FirstType, SecondType, ThirdType, FourthType, FifthType>>::StaticTypeInfo =
		StructInfo::CreateTemplate<Tuple, FirstType, SecondType, ThirdType, FourthType, FifthType>("Tuple");
}

//////////////////
///   Macros   ///

/** Put this macro in the source file of a struct you'd like to reflect
* NOTE: The struct must use the 'REFLECTABLE_STRUCT' flag in its "Information" section */
#define STRUCT_REFLECTION(T) const ::StructInfo T::StaticTypeInfo = ::StructInfo::Create<T>(#T)

/** Put this macro in the header file a struct template you'd like to reflect
* NOTE: The struct must use the 'REFLECTABLE_STRUCT' flag in its "Information" section */
#define TEMPLATE_STRUCT_REFLECTION(T, ...) const ::StructInfo T<_VA_ARGS_>::StaticTypeInfo = ::StructInfo::CreateTemplate<T, _VA_ARGS_>(#T)