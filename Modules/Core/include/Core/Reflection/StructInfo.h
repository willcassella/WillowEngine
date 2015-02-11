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
		return StructInfo(sizeof(AnyStructType), name, &StackFactory<AnyStructType>, &HeapFactory<AnyStructType>);
	}

	StructInfo(const StructInfo& copy) = delete;
	StructInfo(StructInfo&& move);
	~StructInfo() override;

private:

	StructInfo(uint32 size, const String& name, Value(*stackFactory)(), Reference(*heapFactory)());

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
	Reference HeapInstance() const override;

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

	Value(*_stackFactory)();
	Reference(*_heapFactory)();
	Table<String, IFieldInfo*> _fields;
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

		inline static const TypeInfo& Function()
		{
			return StaticTypeInfo;
		}

		inline static const TypeInfo& Function(const String& value)
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

		inline static const TypeInfo& Function()
		{
			return StaticTypeInfo;
		}

		inline static const TypeInfo& Function(const Array<T>& value)
		{
			return StaticTypeInfo;
		}
	};

	/** Register TypeInfo for Array */
	template <typename T>
	const StructInfo TypeOf<Array<T>>::StaticTypeInfo = StructInfo::Create<Array<T>>(String::Format("Array<@>", ::TypeOf<T>().GetName()));

	/** TypeOf for List */
	template <typename T>
	struct TypeOf < List<T> >
	{
		/** Defined below */
		static const StructInfo StaticTypeInfo;

		inline static const TypeInfo& Function()
		{
			return StaticTypeInfo;
		}

		inline static const TypeInfo& Function(const List<T>& value)
		{
			return StaticTypeInfo;
		}
	};

	/** Register TypeInfo for List */
	template <typename T>
	const StructInfo TypeOf<List<T>>::StaticTypeInfo = StructInfo::Create<List<T>>(String::Format("List<@>", ::TypeOf<T>().GetName()));

	///** TypeOf for ArrayList */
	//template <typename T>
	//struct TypeOf < ArrayList<T> >
	//{
	//	static const TypeInfo& Function()
	//	{
	//		static StructInfo type = StructInfo::Create<ArrayList<T>>(String::Format("ArrayList<@>", ::TypeOf<T>().GetName()));
	//		return type;
	//	}

	//	inline static const TypeInfo& Function(const ArrayList<T>& value)
	//	{
	//		return Function();
	//	}
	//};

	/** TypeOf for Queue */
	template <typename T, template <typename F> class StorageType>
	struct TypeOf < Queue<T, StorageType> >
	{
		/** Defined below */
		static const StructInfo StaticTypeInfo;

		inline static const TypeInfo& Function()
		{
			return StaticTypeInfo;
		}

		inline static const TypeInfo& Function(const Queue<T, StorageType>& value)
		{
			return StaticTypeInfo;
		}
	};

	/** Register TypeInfo for Queue */
	template <typename T, template <typename F> class StorageType>
	const StructInfo TypeOf<Queue<T, StorageType>>::StaticTypeInfo = 
		StructInfo::Create<Queue<T, StorageType>>(String::Format("Queue<@, @>", ::TypeOf<T>().GetName(), ::TypeOf<StorageType<T>>().GetName()));

	/** TypeOf for Stack */
	template <typename T, template <typename F> class StorageType>
	struct TypeOf < Stack<T, StorageType> >
	{
		/** Defined below */
		static const StructInfo StaticTypeInfo;

		inline static const TypeInfo& Function()
		{
			return StaticTypeInfo;
		}

		inline static const TypeInfo& Function(const Stack<T, StorageType>& value)
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

		inline static const TypeInfo& Function()
		{
			return StaticTypeInfo;
		}

		inline static const TypeInfo& Function(const Table<KeyType, ValueType>& value)
		{
			return StaticTypeInfo;
		}
	};

	/** Register TypeInfo for Table */
	template <typename KeyType, typename ValueType>
	const StructInfo TypeOf<Table<KeyType, ValueType>>::StaticTypeInfo = 
		StructInfo::Create<Table<KeyType, ValueType>>(String::Format("Table<@, @>", ::TypeOf<KeyType>().GetName(), ::TypeOf<ValueType>().GetName()));

	/** TypeOf for Pair */
	template <typename A, typename B>
	struct TypeOf < Pair<A, B> >
	{
		/** Defined below */
		static const StructInfo StaticTypeInfo;

		inline static const TypeInfo& Function()
		{
			return StaticTypeInfo;
		}

		inline static const TypeInfo& Function(const Pair<A, B>& value)
		{
			return StaticTypeInfo;
		}
	};

	/** Register TypeInfo for Pair */
	template <typename A, typename B>
	const StructInfo TypeOf<Pair<A, B>>::StaticTypeInfo = StructInfo::Create<Pair<A, B>>(String::Format("Pair<@, @>", ::TypeOf<A>().GetName(), ::TypeOf<B>().GetName()));
}