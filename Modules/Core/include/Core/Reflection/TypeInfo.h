// TypeInfo.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <typeinfo>
#include "../Object.h"
#include "../Containers/String.h"
#include "../Operations/FailableOperation.h"
#include "../Operations/TypeOps.h"
#include "../Operations/ToString.h"
#include "../Operations/FromString.h"
#include "../Operations/ToArchive.h"
#include "../Operations/FromArchive.h"
#include "Reflection.h"

/////////////////
///   Types   ///

/** Declaration of 'TypeInfoBuilder', specialized here and in other reflection class headers. */
template <typename T, class TypeInfoT = TypeInfoTypeOf<T>>
struct TypeInfoBuilder;

/** Aliases what the base type for a TypeInfoBuilder with the given types should be.  */
template <typename T, class TypeInfoT>
using TypeInfoBuilderBase = TypeInfoBuilder<T, BaseTypeOf<TypeInfoT>>;

/** Base of every reflection meta-class in the engine */
class CORE_API TypeInfo : public Object
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(Object)

	template <typename T, class TypeInfoT>
	friend struct TypeInfoBuilder;

	///////////////////////
	///   Inner Types   ///
public:

	/** The function signature for a reflected constructor. */
	using Constructor = void(*)(byte*);

	/** The function signature for a reflected copy-constructor. */
	using CopyConstructor =  void(*)(byte*, const void*);

	/** The function signature for a reflected move-constructor. */
	using MoveConstructor = void(*)(byte*, void*);

	/** The function signature for a reflected destructor. */
	using Destructor = void(*)(void*);

	/** The function signature for a reflected copy-assignment operator. */
	using CopyAssignmentOperator = void(*)(void*, const void*);

	/** The function signature for a reflected move-assignment operator. */
	using MoveAssignmentOperator = void(*)(void*, void*);

	/** The function signature for a reflected ToString implementation. */
	using ToStringImplementation = String(*)(const void*);

	/** The function signature for a reflected FromString implementation. */
	using FromStringImplementation = String(*)(void*, const String&);

	/** The function signature for a reflected ToArchive implementation. */
	using ToArchiveImplementation = void(*)(const void*, ArchiveWriter&);

	/** The function signature for a reflected FromArchive implementation. */
	using FromArchiveImplementation = void(*)(void*, const ArchiveReader&);

	////////////////////////
	///   Constructors   ///
public:

	/** Constructs this TypeInfo object from the given builder, and registers with the Application. */
	template <typename T>
	TypeInfo(const TypeInfoBuilder<T, TypeInfo>& builder)
		: Base(NoReferenceCount), _data(std::move(builder._data))
	{
		this->register_with_application();
	}

	/** Stupid move-constructor that will never get called. See notes in source. */
	TypeInfo(TypeInfo&& move);

	/** Unregisters this TypeInfo object with the Application. */
	~TypeInfo() override;

	///////////////////
	///   Methods   ///
public:

	/** Returns this TypeInfo object as a String */
	FORCEINLINE String ToString() const final override
	{
		return get_name();
	}

	/** Gets the name for this type. */
	FORCEINLINE const String& get_name() const
	{
		if (this->_name.IsEmpty())
		{
			this->_name = this->generate_name();
		}

		return this->_name;
	}

	/** Returns the size of this type. */
	FORCEINLINE std::size_t get_size() const
	{
		return this->_data.size;
	}

	/** Returns the alignment of this type. */
	FORCEINLINE std::size_t get_alignment() const
	{
		return this->_data.alignment;
	}

	/** Returns whether this type is a compound type.
	* i.e - It is composed of smaller types (like a class, struct, or interface). */
	FORCEINLINE bool is_compound() const
	{
		return this->_data.is_compound;
	}

	/** Returns whether this type is abstract
	* i.e - It has at least one pure virtual function */
	FORCEINLINE bool is_abstract() const
	{
		return this->_data.is_abstract;
	}

	/** Returns whether this type is polymorphic
	* i.e - It has at least one virtual function */
	FORCEINLINE bool is_polymorphic() const
	{
		return this->_data.is_polymorphic;
	}

	/** Returns whether this type is trivial (it can be safely memcopy'd). */
	FORCEINLINE bool is_trivial() const
	{
		return this->_data.is_trivial;
	}

	/** Returns whether this type is default-constructible */
	FORCEINLINE bool is_default_constructible() const
	{
		return this->get_default_constructor() != nullptr;
	}

	/** Returns whether this type has a dynamic constructor. */
	FORCEINLINE bool is_dynamically_constructible() const
	{
		return this->get_dynamic_constructor() != nullptr;
	}

	/** Returns whether this type is copy-constructible. */
	FORCEINLINE bool is_copy_constructible() const
	{
		return this->get_copy_constructor() != nullptr;
	}

	/** Returns whether this type is move-constructible. */
	FORCEINLINE bool is_move_constructible() const
	{
		return this->get_move_constructor() != nullptr;
	}

	/** Returns whether this type is destructible. */
	FORCEINLINE bool is_destructible() const
	{
		return this->get_destructor() != nullptr;
	}

	/** Returns whether this type is copy-assignable. */
	FORCEINLINE bool is_copy_assignable() const
	{
		return this->get_copy_assignment_operator() != nullptr;
	}

	/** Returns whether this type is move-assignable. */
	FORCEINLINE bool is_move_assignable() const
	{
		return this->get_move_assignment_operator() != nullptr;
	}

	/** Returns whether this type supports the 'ToString' operation. */
	FORCEINLINE bool implements_to_string() const
	{
		return this->get_to_string_implementation() != nullptr;
	}

	/** Returns whether this type supports the 'FromString' operation. */
	FORCEINLINE bool implements_from_string() const
	{
		return this->get_from_string_implementation() != nullptr;
	}

	/** Returns whether this type supports the 'ToArchive' operation. */
	FORCEINLINE bool implements_to_archive() const
	{
		return this->get_to_archive_implementation() != nullptr;
	}

	/** Returns whether this type supports the 'FromArchive' operation. */
	FORCEINLINE bool implements_from_archive() const
	{
		return this->get_from_archive_implementation() != nullptr;
	}

	/** Returns the constructor for this type.
	* NOTE: Returns 'null' if this type is not constructible. */
	FORCEINLINE Constructor get_default_constructor() const
	{
		return this->_data.default_constructor;
	}

	/** Returns the dynamic constructor for this type.
	* The dynamic constructor is similar to the default constructor, except it is explicitly intended for serialization.
	* If the type does not have a dynamic constructor, just use the default-constructor. If this type does not have either, then it is not serializable.
	* NOTE: Returns 'null' if this type does not have a dynamic constructor. */
	FORCEINLINE Constructor get_dynamic_constructor() const
	{
		return this->_data.dynamic_constructor;
	}

	/** Returns the copy-constructor for this type. 
	* NOTE: Returns 'null' if this type is not copy-constructible. */
	FORCEINLINE CopyConstructor get_copy_constructor() const
	{
		return this->_data.copy_constructor;
	}

	/** Returns the move-constructor for this type.
	* NOTE: Returns 'null' if this type is not move-constructible. */
	FORCEINLINE MoveConstructor get_move_constructor() const
	{
		return this->_data.move_constructor;
	}

	/** Returns the destructor for this type.
	* NOTE: Returns 'null' if this type is not destructible. */
	FORCEINLINE Destructor get_destructor() const
	{
		return this->_data.destructor;
	}

	/** Returns the copy-assignment operator for this type.
	* NOTE: Returns 'null' if this type is not copy-assignable. */
	FORCEINLINE CopyAssignmentOperator get_copy_assignment_operator() const
	{
		return this->_data.copy_assignment_operator;
	}

	/** Returns the move-assignment operator for this type.
	* NOTE: Returns 'null' if this type is not move-assignable. */
	FORCEINLINE MoveAssignmentOperator get_move_assignment_operator() const
	{
		return this->_data.move_assignment_operator;
	}

	/** Returns the implementation of 'ToString' for this type. 
	* NOTE: Returns 'null' if this type does not support the 'ToString' operation. */
	FORCEINLINE ToStringImplementation get_to_string_implementation() const
	{
		return this->_data.to_string_implementation;
	}

	/** Returns the implementation of 'FromString' for this type. 
	* NOTE: Returns 'null' if this type does not support the 'FromString' operation. */
	FORCEINLINE FromStringImplementation get_from_string_implementation() const
	{
		return this->_data.from_string_implementation;
	}

	/** Returns the implementation of 'ToArchive' for this type. 
	* NOTE: Returns 'null' if this type does not support the 'ToArchive' operation. */
	FORCEINLINE ToArchiveImplementation get_to_archive_implementation() const
	{
		return this->_data.to_archive_implementation;
	}

	/** Returns the implementation of 'FromArchive' for this type. 
	* NOTE: Returns 'null' if this type does not support the 'FromArchive' operation. */
	FORCEINLINE FromArchiveImplementation get_from_archive_implementation() const
	{
		return this->_data.from_archive_implementation;
	}

	/** Returns whether this type is bitwise castable to the given type */
	virtual bool is_castable_to(const TypeInfo& type) const = 0;

	/** Returns whether this type is stable (its memory layout is unlikely to ever change). */
	virtual bool is_stable() const = 0;

protected:

	/** Generates the name of the type. Since some types need special name-formatting behavior that is unsafe
	* to do while the application is starting up, this needs to be done when the application is initialized.
	* Called when the Application is initialized. */
	virtual String generate_name() const;

private:

	/** Registers this TypeInfo instance with the Application singleton. */
	void register_with_application();

	/////////////////////
	///   Operators   ///
public:

	friend FORCEINLINE bool operator==(const TypeInfo& lhs, const TypeInfo& rhs)
	{
		return lhs._data.type_info->hash_code() == rhs._data.type_info->hash_code();
	}
	friend FORCEINLINE bool operator!=(const TypeInfo& lhs, const TypeInfo& rhs)
	{
		return !(lhs == rhs);
	}

	////////////////
	///   Data   ///
private:

	/** Some types need special behavior when generating their name.
	* While '_data.raw_name' holds the ungenerated part of the name, '_name' holds the final name.
	* After the application is initialized, '_rawName' should be ignored. */
	mutable String _name;
	
	struct Data final
	{
		const std::type_info* type_info = nullptr;
		CString raw_name = nullptr;
		Constructor default_constructor = nullptr;
		Constructor dynamic_constructor = nullptr;
		CopyConstructor copy_constructor = nullptr;
		MoveConstructor move_constructor = nullptr;
		Destructor destructor = nullptr;
		CopyAssignmentOperator copy_assignment_operator = nullptr;
		MoveAssignmentOperator move_assignment_operator = nullptr;
		ToStringImplementation to_string_implementation = nullptr;
		FromStringImplementation from_string_implementation = nullptr;
		ToArchiveImplementation to_archive_implementation = nullptr;
		FromArchiveImplementation from_archive_implementation = nullptr;
		std::size_t size = 0;
		std::size_t alignment = 0;
		bool is_compound = false;
		bool is_abstract = false;
		bool is_polymorphic = false;
		bool is_trivial = false;
	} _data;
};

/** Generic TypeInfoBuilder for TypeInfo */
template <typename T>
struct TypeInfoBuilder < T, TypeInfo >
{
	///////////////////////
	///   Information   ///
public:

	friend TypeInfo;

	////////////////////////
	///   Constructors   ///
public:

	TypeInfoBuilder(CString name)
	{
		_data.type_info = &typeid(T);
		_data.raw_name = name;

		// If the type is default-constructible
		using DefaultConstructT = Operations::DefaultConstruct<T>;
		if (DefaultConstructT::Supported)
		{
			_data.default_constructor = [](byte* location)
			{
				FailableOperation<DefaultConstructT>(location);
			};
		}

		// If the type is constructible via a dynamic initializer
		using DynamicInitializeT = Operations::DynamicInitialize<T>;
		if (DynamicInitializeT::Supported)
		{
			_data.dynamic_constructor = [](byte* location) -> void
			{
				FailableOperation<DynamicInitializeT>(location, DynamicInitializer());
			};
		}

		// If the type is copy-constructible
		using CopyConstructT = Operations::CopyConstruct<T>;
		if (CopyConstructT::Supported)
		{
			_data.copy_constructor = [](byte* location, const void* copy) -> void
			{
				FailableOperation<CopyConstructT>(location, *static_cast<const T*>(copy));
			};
		}

		// If the type is move-constructible
		using MoveConstructT = Operations::MoveConstruct<T>;
		if (MoveConstructT::Supported)
		{
			_data.move_constructor = [](byte* location, void* move) -> void
			{
				FailableOperation<MoveConstructT>(location, std::move(*static_cast<T*>(move)));
			};
		}

		// If the type is destructible
		using DestroyT = Operations::Destroy<T>;
		if (DestroyT::Supported)
		{
			_data.destructor = [](void* value) -> void
			{
				FailableOperation<DestroyT>(*static_cast<T*>(value));
			};
		}

		// If the type is copy-assignable
		using CopyAssignT = Operations::CopyAssign<T>;
		if (CopyAssignT::Supported)
		{
			_data.copy_assignment_operator = [](void* lhs, const void* rhs) -> void
			{
				FailableOperation<CopyAssignT>(*static_cast<T*>(lhs), *static_cast<const T*>(rhs));
			};
		}

		// If the type is move-assignable
		using MoveAssignT = Operations::MoveAssign<T>;
		if (MoveAssignT::Supported)
		{
			_data.move_assignment_operator = [](void* lhs, void* rhs) -> void
			{
				FailableOperation<MoveAssignT>(*static_cast<T*>(lhs), std::move(*static_cast<T*>(rhs)));
			};
		}

		// If the type supports 'ToString'
		using ToStringT = Operations::ToString<T>;
		if (ToStringT::Supported)
		{
			_data.to_string_implementation = [](const void* value) -> String
			{
				String out;
				FailableOperation<ToStringT>(out, *static_cast<const T*>(value));
				return out;
			};
		}

		// If the type supports 'FromString'
		using FromStringT = Operations::FromString<T>;
		if (FromStringT::Supported)
		{
			_data.from_string_implementation = [](void* value, const String& string) -> String
			{
				String out;
				FailableOperation<FromStringT>(out, *static_cast<T*>(value), string);
				return out;
			};
		}

		// If the type supports 'ToArchive'
		using ToArchiveT = Operations::ToArchive<T>;
		if (ToArchiveT::Supported)
		{
			_data.to_archive_implementation = [](const void* value, ArchiveWriter& writer) -> void
			{
				FailableOperation<ToArchiveT>(*static_cast<const T*>(value), writer);
			};
		}

		// If the type supports 'FromArchive'
		using FromArchiveT = Operations::FromArchive<T>;
		if (FromArchiveT::Supported)
		{
			_data.from_archive_implementation = [](void* value, const ArchiveReader& reader) -> void
			{
				FailableOperation<FromArchiveT>(*static_cast<T*>(value), reader);
			};
		}

		_data.size = sizeof(T);
		_data.alignment = alignof(T&); // Have to use reference here, since MSVC errors out when using plain 'T'
		_data.is_compound = std::is_class<T>::value;
		_data.is_abstract = std::is_abstract<T>::value;
		_data.is_polymorphic = std::is_polymorphic<T>::value;
		_data.is_trivial = std::is_trivial<T>::value;
	}

	///////////////////
	///   Methods   ///
protected:

	/** Since TypeInfoBuilders use the builder pattern, you can use this to return yourself after each build method, 
	* without losing compmile-time info. */
	auto& AsMostSpecificTypeInfoBuilder()
	{
		return static_cast<TypeInfoBuilder<T>&>(*this);
	}

	////////////////
	///   Data   ///
private:

	mutable TypeInfo::Data _data;
};

namespace Operations
{
	namespace Default
	{
		/** Default implementation of 'ToString', returns value's type name. */
		template <typename T>
		FORCEINLINE String ToString(const T& value)
		{
			return Format("{instance of @}", ::TypeOf(value));
		}
	}
}

/////////////////////
///   Functions   ///

/** Returns whether the given object is castable to the given type.
* NOTE: This is the predicate used by the 'Cast' function. */
template <typename TargetT, typename T>
bool IsCastableTo(T& value)
{
	return std::is_base_of<TargetT, T>::value || TypeOf(value).is_castable_to(TypeOf<TargetT>());
}

/** Safely casts from a reference of one type to the target type.
* NOTE: Returns a null pointer if the cast is invalid (value does not legally translate to the given type). */
template <typename TargetT, typename T>
FORCEINLINE auto* Cast(T& value)
{
	using ResultT = stde::minimum_cv_t<T, TargetT>*;

	// Perform a compile-time and run-time check of the validity of this cast
	if (IsCastableTo<TargetT>(value))
	{
		return reinterpret_cast<ResultT>(&value);
	}
	else
	{
		return ResultT{ nullptr };
	}
}

//////////////////
///   Macros   ///

/** Put this macro into the source file of a type you'd like to reflect.
* NOTE: The type muse use the corresponding 'REFLECTABLE_X' flag in its header.
* NOTE: If you get the error "Incomplete type is not allowed", then the TypeInfoBuilder for this reflection type has not been defined. */
#define BUILD_REFLECTION(T) const T::TypeInfoType T::StaticTypeInfo = ::TypeInfoBuilder<T>(#T)

// TODO: Documentation
#define BUILD_TEMPLATE_REFLECTION(T, ...) const typename T<__VA_ARGS__>::TypeInfoType T<__VA_ARGS__>::StaticTypeInfo = ::TypeInfoBuilder<T<__VA_ARGS__>>(#T)
