// TypeInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../String.h"
#include "../Object.h"
#include "../Operations/TypeOps.h"
#include "../Operations/ToString.h"
#include "../Operations/FromString.h"
#include "Reflection.h"

/////////////////
///   Types   ///

/** Declaration of 'TypeInfoBuilder', specialized here and in other reflection class headers. */
template <typename T, class TypeInfoT = TypeInfoType<T>>
struct TypeInfoBuilder;

// TODO: Documentation
template <typename T, class TypeInfoT>
using TypeInfoBuilderBase = TypeInfoBuilder<T, BaseOf<TypeInfoT>>;

/** Base of every reflection meta-class in the engine */
class CORE_API TypeInfo : public Object
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(Object)

	friend Variant;
	template <typename T, class TypeInfoT>
	friend struct TypeInfoBuilder;

	///////////////////////
	///   Inner Types   ///
public:

	/** The function signature for a reflected default constructor */
	typedef void(*DefaultConstructor)(byte*);

	/** The function signature for a reflected copy constructor */
	typedef void(*CopyConstructor)(byte*, const void*);

	/** The function signature for a reflected move constructor */
	typedef void(*MoveConstructor)(byte*, void*);

	/** The function signature for a reflected copy-assignment operator */
	typedef void(*CopyAssignmentOperator)(void*, const void*);

	/** The function signature for a reflected move-assignment operator */
	typedef void(*MoveAssignmentOperator)(void*, void*);

	/** The function signature for a reflected destructor */
	typedef void(*Destructor)(void*);

	////////////////////////
	///   Constructors   ///
public:

	// TODO: Documentation
	template <typename T>
	TypeInfo(const TypeInfoBuilder<T, TypeInfo>& builder)
		: _data(std::move(builder._data))
	{
		RegisterWithApplication();
	}

	/** TypeInfo objects are not copyable. */
	TypeInfo(const TypeInfo& copy) = delete;

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
		return GetName();
	}

	/** Returns the static size of this type */
	FORCEINLINE uint32 GetSize() const
	{
		return _data.size;
	}

	/** Returns the name of this type */
	virtual String GetName() const;

	/** Returns whether this type is a compound type.
	* i.e - It is composed of smaller types (like a class, struct, or interface). */
	FORCEINLINE bool IsCompound() const
	{
		return _data.isCompound;
	}

	/** Returns whether this type is abstract
	* i.e - It has at least one pure virtual function */
	FORCEINLINE bool IsAbstract() const
	{
		return _data.isAbstract;
	}

	/** Returns whether this type is polymorphic
	* i.e - It has at least one virtual function */
	FORCEINLINE bool IsPolymorphic() const
	{
		return _data.isPolymorphic;
	}

	/** Returns whether this type is default-constructible. */
	FORCEINLINE bool IsDefaultConstructible() const
	{
		return _data.isDefaultConstructible;
	}

	/** Returns whether this type is copy-constructible. */
	FORCEINLINE bool IsCopyConstructible() const
	{
		return _data.isCopyConstructible;
	}

	/** Returns whether this type is move-constructible. */
	FORCEINLINE bool IsMoveConstructible() const
	{
		return _data.isMoveConstructible;
	}

	/** Returns whether this type is copy-assignable. */
	FORCEINLINE bool IsCopyAssignable() const
	{
		return _data.isCopyAssignable;
	}

	/** Returns whether this type is move-assignable. */
	FORCEINLINE bool IsMoveAssignable() const
	{
		return _data.isMoveAssignable;
	}

	/** Returns whether this type is destructible. */
	FORCEINLINE bool IsDestructible() const
	{
		return _data.isDestructible;
	}

	/** Returns the default constructor for this type.
	* Returns an empty implementation if this type is not copy-constructible. */
	FORCEINLINE DefaultConstructor GetDefaultConstructor() const
	{
		return _data.defaultConstructor;
	}

	/** Returns the copy-constructor for this type. 
	* Returns an empty implementation if this type is not copy-constructible. */
	FORCEINLINE CopyConstructor GetCopyConstructor() const
	{
		return _data.copyConstructor;
	}

	/** Returns the move-constructor for this type. 
	* Returns an empty implementation if this type is not move-constructible. */
	FORCEINLINE MoveConstructor GetMoveConstructor() const
	{
		return _data.moveConstructor;
	}

	/** Returns the copy-assignment operator for this type.
	* Returns an empty implementation if this type is not copy-assignable. */
	FORCEINLINE CopyAssignmentOperator GetCopyAssignmentOperator() const
	{
		return _data.copyAssignmentOperator;
	}

	/** Returns the move-assignment operator for this type.
	* Returns an empty implementation if this type is not move-assignable. */
	FORCEINLINE MoveAssignmentOperator GetMoveAssignmentOperator() const
	{
		return _data.moveAssignmentOperator;
	}

	/** Returns the destructor for this type.
	* Returns an empty implementation if this type is not destructible. */
	FORCEINLINE Destructor GetDestructor() const
	{
		return _data.destructor;
	}

	/** Returns whether this type is bitwise castable to the given type */
	virtual bool IsCastableTo(const TypeInfo& type) const = 0;

private:

	/** Registers this TypeInfo instance with the Application singleton. */
	void RegisterWithApplication();

	/////////////////////
	///   Operators   ///
public:

	friend FORCEINLINE bool operator==(const TypeInfo& lhs, const TypeInfo& rhs)
	{
		return &lhs == &rhs || lhs.GetName() == rhs.GetName();
	}
	friend FORCEINLINE bool operator!=(const TypeInfo& lhs, const TypeInfo& rhs)
	{
		return !(lhs == rhs);
	}

	////////////////
	///   Data   ///
private:

	struct Data
	{
		CString name;
		DefaultConstructor defaultConstructor;
		CopyConstructor copyConstructor;
		MoveConstructor moveConstructor;
		CopyAssignmentOperator copyAssignmentOperator;
		MoveAssignmentOperator moveAssignmentOperator;
		Destructor destructor;
		String(*toStringImplementation)(const void*);
		String(*fromStringImplementation)(void*, const String&);
		uint32 size;
		bool isCompound;
		bool isAbstract;
		bool isPolymorphic;
		bool isDefaultConstructible;
		bool isCopyConstructible;
		bool isMoveConstructible;
		bool isCopyAssignable;
		bool isMoveAssignable;
		bool isDestructible;
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
		_data.name = name;

		_data.defaultConstructor= Implementation::Construct<T>::Function;
		_data.copyConstructor = [](byte* location, const void* copy)
		{
			Implementation::Construct<T, const T&>::Function(location, *static_cast<const T*>(copy));
		};
		_data.moveConstructor = [](byte* location, void* move)
		{
			Implementation::Construct<T, T&&>::Function(location, std::move(*static_cast<T*>(move)));
		};
		_data.copyAssignmentOperator = [](void* value, const void* copy)
		{
			Implementation::Assign<T, const T&>::Function(*static_cast<T*>(value), *static_cast<const T*>(copy));
		};
		_data.moveAssignmentOperator = [](void* value, void* move)
		{
			Implementation::Assign<T, T&&>::Function(*static_cast<T*>(value), std::move(*static_cast<T*>(move)));
		};
		_data.destructor = [](void* value)
		{
			Implementation::Destroy<T>::Function(*static_cast<T*>(value));
		};

		_data.toStringImplementation = [](const void* value) -> String
		{
			return Implementation::ToString<T>::Function(*static_cast<const T*>(value));
		};
		_data.fromStringImplementation = [](void* value, const String& string) -> String
		{
			return Implementation::FromString<T>::Function(*static_cast<T*>(value), string);
		};

		_data.size = sizeof(T);
		_data.isCompound = std::is_class<T>::value;
		_data.isAbstract = std::is_abstract<T>::value;
		_data.isPolymorphic = std::is_polymorphic<T>::value;
		_data.isDefaultConstructible = std::is_default_constructible<T>::value;
		_data.isCopyConstructible = std::is_copy_constructible<T>::value;
		_data.isMoveConstructible = std::is_move_constructible<T>::value;
		_data.isCopyAssignable = std::is_copy_assignable<T>::value;
		_data.isMoveAssignable = std::is_move_assignable<T>::value;
		_data.isDestructible = std::is_destructible<T>::value;
	}

	////////////////
	///   Data   ///
private:

	mutable TypeInfo::Data _data;
};

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	namespace Default
	{
		/** Default implementation of 'ToString', returns value's type name. */
		template <typename T>
		FORCEINLINE String ToString(const T& value)
		{
			return ::TypeOf(value).GetName();
		}

		/** Default implementation of 'FromString', does nothing. */
		template <typename T>
		FORCEINLINE String FromString(T& /*value*/, const String& string)
		{
			return string;
		}
	}
}

/////////////////////
///   Functions   ///

/** Safely casts from a reference of one type to the target class/interface/type
* WARNING: Returns a null pointer if the cast is invalid (value does not legally translate to the given type) */
template <typename TargetT, typename T>
FORCEINLINE TargetT* Cast(T& value)
{
	static_assert(!std::is_reference<TargetT>::value, "Using 'Cast' to cast to a reference type is not allowed");

	if (TypeOf(value).IsCastableTo(TypeOf<TargetT>()))
	{
		return reinterpret_cast<TargetT*>(&value);
	}
	else
	{
		return nullptr;
	}
}

/** Safely casts from an immutable reference of one type to the target class/interface/type
* WARNING: Returns a null pointer if the cast is invalid (value does not legally translate to the given type) */
template <typename TargetT, typename T>
FORCEINLINE const TargetT* Cast(const T& value)
{
	static_assert(!std::is_reference<TargetT>::value, "Using 'Cast' to cast to a reference is not allowed");
	
	// TODO: Change this to ".template IsCastableTo<TargetT>()" if that works on clang (doesn't work on MSVC for some reason
	if (TypeOf(value).IsCastableTo(TypeOf<TargetT>()))
	{
		return reinterpret_cast<const TargetT*>(&value);
	}
	else
	{
		return nullptr;
	}
}

//////////////////
///   Macros   ///

/** Put this macro into the source file of a type you'd like to reflect.
* NOTE: The type muse use the corresponding 'REFLECTABLE_X' flag in its header.
* NOTE: If you get the error "Incomplete type is not allowed", then the TypeInfoBuilder for this reflection type has not been defined. */
#define BUILD_REFLECTION(T) const ::TypeInfoType<T> T::StaticTypeInfo = ::TypeInfoBuilder<T>(#T)
