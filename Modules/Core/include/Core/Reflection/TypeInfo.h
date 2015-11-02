// TypeInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../String.h"
#include "../Object.h"
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

	friend Variant;
	friend ImmutableVariant;
	template <typename T, class TypeInfoT>
	friend struct TypeInfoBuilder;

	///////////////////////
	///   Inner Types   ///
public:

	/** The function signature for a reflected constructor. */
	typedef void(*Constructor)(byte*);

	/** The function signature for a reflected copy-constructor. */
	typedef void(*CopyConstructor)(byte*, const void*);

	/** The function signature for a reflected move-constructor. */
	typedef void(*MoveConstructor)(byte*, void*);

	/** The function signature for a reflected destructor. */
	typedef void(*Destructor)(void*);

	/** The function signature for a reflected copy-assignment operator. */
	typedef void(*CopyAssignmentOperator)(void*, const void*);

	/** The function signature for a reflected move-assignment operator. */
	typedef void(*MoveAssignmentOperator)(void*, void*);

	////////////////////////
	///   Constructors   ///
public:

	/** Constructs this TypeInfo object from the given builder, and registers with the Application. */
	template <typename T>
	TypeInfo(const TypeInfoBuilder<T, TypeInfo>& builder)
		: _data(std::move(builder._data))
	{
		RegisterWithApplication();
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
		return GetName();
	}

	/** Gets the name for this type. */
	FORCEINLINE const String& GetName() const
	{
		if (_name.IsEmpty())
		{
			_name = GenerateName();
		}

		return _name;
	}

	/** Returns the static size of this type */
	FORCEINLINE uint32 GetSize() const
	{
		return _data.size;
	}

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

	/** Returns whether this type is trivial (it can be safely memcopy'd). */
	FORCEINLINE bool IsTrivial() const
	{
		return _data.isTrivial;
	}

	/** Returns whether this type is default-constructible */
	FORCEINLINE bool IsDefaultConstructible() const
	{
		return this->GetDefaultConstructor() != nullptr;
	}

	/** Returns whether this type has a dynamic constructor. */
	FORCEINLINE bool HasDynamicConstructor() const
	{
		return this->GetDynamicConstructor() != nullptr;
	}

	/** Returns whether this type is copy-constructible. */
	FORCEINLINE bool IsCopyConstructible() const
	{
		return this->GetCopyConstructor() != nullptr;
	}

	/** Returns whether this type is move-constructible. */
	FORCEINLINE bool IsMoveConstructible() const
	{
		return this->GetMoveConstructor() != nullptr;
	}

	/** Returns whether this type is destructible. */
	FORCEINLINE bool IsDestructible() const
	{
		return this->GetDestructor() != nullptr;
	}

	/** Returns whether this type is copy-assignable. */
	FORCEINLINE bool IsCopyAssignable() const
	{
		return this->GetCopyAssignmentOperator() != nullptr;
	}

	/** Returns whether this type is move-assignable. */
	FORCEINLINE bool IsMoveAssignable() const
	{
		return this->GetMoveAssignmentOperator() != nullptr;
	}

	/** Returns the constructor for this type.
	* NOTE: Returns 'null' if this type is not constructible. */
	FORCEINLINE Constructor GetDefaultConstructor() const
	{
		return _data.defaultConstructor;
	}

	/** Returns the dynamic constructor for this type.
	* The dynamic constructor is similar to the default constructor, except it is explicitly intended for serialization.
	* If the type does not have a dynamic constructor, just use the default-constructor. If this type does not have either, then it is not serializable.
	* NOTE: Returns 'null' if this type does not have a dynamic constructor. */
	FORCEINLINE Constructor GetDynamicConstructor() const
	{
		return _data.dynamicConstructor;
	}

	/** Returns the copy-constructor for this type. 
	* NOTE: Returns 'null' if this type is not copy-constructible. */
	FORCEINLINE CopyConstructor GetCopyConstructor() const
	{
		return _data.copyConstructor;
	}

	/** Returns the move-constructor for this type.
	* NOTE: Returns 'null' if this type is not move-constructible. */
	FORCEINLINE MoveConstructor GetMoveConstructor() const
	{
		return _data.moveConstructor;
	}

	/** Returns the destructor for this type.
	* NOTE: Returns 'null' if this type is not destructible. */
	FORCEINLINE Destructor GetDestructor() const
	{
		return _data.destructor;
	}

	/** Returns the copy-assignment operator for this type.
	* NOTE: Returns 'null' if this type is not copy-assignable. */
	FORCEINLINE CopyAssignmentOperator GetCopyAssignmentOperator() const
	{
		return _data.copyAssignmentOperator;
	}

	/** Returns the move-assignment operator for this type.
	* NOTE: Returns 'null' if this type is not move-assignable. */
	FORCEINLINE MoveAssignmentOperator GetMoveAssignmentOperator() const
	{
		return _data.moveAssignmentOperator;
	}

	/** Returns whether this type is bitwise castable to the given type */
	virtual bool IsCastableTo(const TypeInfo& type) const = 0;

	/** Returns whether this type is stable (its memory layout is unlikely to ever change). */
	virtual bool IsStable() const = 0;

protected:

	/** Generates the name of the type. Since some types need special name-formatting behavior that is unsafe
	* to do while the application is starting up, this needs to be done when the application is initialized.
	* Called when the Application is initialized. */
	virtual String GenerateName() const;

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

	/** Some types need special behavior when generating their name.
	* While '_data.rawName' holds the ungenerated part of the name, '_name' holds the final name.
	* After the application is initialized, '_rawName' should be ignored. */
	mutable String _name;
	
	struct Data final
	{
		CString rawName = nullptr;
		Constructor defaultConstructor = nullptr;
		Constructor dynamicConstructor = nullptr;
		CopyConstructor copyConstructor = nullptr;
		MoveConstructor moveConstructor = nullptr;
		Destructor destructor = nullptr;
		CopyAssignmentOperator copyAssignmentOperator = nullptr;
		MoveAssignmentOperator moveAssignmentOperator = nullptr;
		String(*toStringImplementation)(const void*) = nullptr;
		String(*fromStringImplementation)(void*, const String&) = nullptr;
		void(*toArchiveImplementation)(const void*, ArchiveNode&) = nullptr;
		void(*fromArchiveImplementation)(void*, const ArchiveNode&) = nullptr;
		uint32 size = 0;
		bool isCompound = false;
		bool isAbstract = false;
		bool isPolymorphic = false;
		bool isTrivial = false;
	} _data;
};

/** This type soley exists for types that aren't default-constructible, but still wish to be constructible via reflection.
* Just implement a constructor that accepts an object of this type, and it may be serialized.
* Think of it like this:
* - A constructor configures and initializes the object all at once.
* - A constructor accepting 'DynamicInitializer' indicates that the object will be configured and initialized post-construction.
* Note that this means that you shouldn't invoke the 'DynamicInitializer' constructor directly, unless you know what you're doing. */
struct DynamicInitializer final
{
	// Nothing here
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
		_data.rawName = name;

		// If the type is default-constructible
		if (Operations::Construct<T>::Supported)
		{
			_data.defaultConstructor = Operations::Construct<T>::Function;
		}

		// If the type is constructible via a dynamic initializer
		if (Operations::Construct<T, DynamicInitializer>::Supported)
		{
			_data.dynamicConstructor = [](byte* location) -> void
			{
				Operations::Construct<T, DynamicInitializer>::Function(location, DynamicInitializer{});
			};
		}

		// If the type is copy-constructible
		if (Operations::Construct<T, const T&>::Supported)
		{
			_data.copyConstructor = [](byte* location, const void* copy) -> void
			{
				Operations::Construct<T, const T&>::Function(location, *static_cast<const T*>(copy));
			};
		}

		// If the type is move-constructible
		if (Operations::Construct<T, T&&>::Supported)
		{
			_data.moveConstructor = [](byte* location, void* move) -> void
			{
				Operations::Construct<T, T&&>::Function(location, std::move(*static_cast<T*>(move)));
			};
		}

		// If the type is destructible
		if (Operations::Destroy<T>::Supported)
		{
			_data.destructor = [](void* value) -> void
			{
				Operations::Destroy<T>::Function(*static_cast<T*>(value));
			};
		}

		// If the type is copy-assignable
		if (Operations::Assign<T, const T&>::Supported)
		{
			_data.copyAssignmentOperator = [](void* lhs, const void* rhs) -> void
			{
				Operations::Assign<T, const T&>::Function(*static_cast<T*>(lhs), *static_cast<const T*>(rhs));
			};
		}

		// If the type is move-assignable
		if (Operations::Assign<T, T&&>::Supported)
		{
			_data.moveAssignmentOperator = [](void* lhs, void* rhs) -> void
			{
				Operations::Assign<T, T&&>::Function(*static_cast<T*>(lhs), std::move(*static_cast<T*>(rhs)));
			};
		}

		_data.toStringImplementation = [](const void* value) -> String
		{
			return Implementation::ToString<T>::Function(*static_cast<const T*>(value));
		};
		_data.fromStringImplementation = [](void* value, const String& string) -> String
		{
			return Implementation::FromString<T>::Function(*static_cast<T*>(value), string);
		};
		_data.toArchiveImplementation = [](const void* value, ArchiveNode& node) -> void
		{
			Implementation::ToArchive<T>::Function(*static_cast<const T*>(value), node);
		};
		_data.fromArchiveImplementation = [](void* value, const ArchiveNode& node) -> void
		{
			Implementation::FromArchive<T>::Function(*static_cast<T*>(value), node);
		};

		_data.size = sizeof(T);
		_data.isCompound = std::is_class<T>::value;
		_data.isAbstract = std::is_abstract<T>::value;
		_data.isPolymorphic = std::is_polymorphic<T>::value;
		_data.isTrivial = std::is_trivial<T>::value;
	}

	///////////////////
	///   Methods   ///
protected:

	/** Since TypeInfoBuilders use the builder pattern, you can use this to return yourself after each build method, 
	* without losing compmile-time info. */
	auto& SelfAsMostSpecificTypeInfoBuilder()
	{
		return static_cast<TypeInfoBuilder<T>&>(self);
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

/** Safely casts from a reference of one type to the target class/interface/type.
* NOTE: Returns a null pointer if the cast is invalid (value does not legally translate to the given type). */
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

/** Safely casts from an immutable reference of one type to the target class/interface/type.
* NOTE: Returns a null pointer if the cast is invalid (value does not legally translate to the given type). */
template <typename TargetT, typename T>
FORCEINLINE const TargetT* Cast(const T& value)
{
	static_assert(!std::is_reference<TargetT>::value, "Using 'Cast' to cast to a reference is not allowed");
	
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
#define BUILD_REFLECTION(T) const T::TypeInfoType T::StaticTypeInfo = ::TypeInfoBuilder<T>(#T)

// TODO: Documentation
#define BUILD_TEMPLATE_REFLECTION(T, ...) const typename T<__VA_ARGS__>::TypeInfoType T<__VA_ARGS__>::StaticTypeInfo = ::TypeInfoBuilder<T<__VA_ARGS__>>(#T) 
