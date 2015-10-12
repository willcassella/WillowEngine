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

	/** The function signature for a reflected destructor. */
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

	/** Returns whether this type is constructible,
	* Either with a default-constructor, or a DynamicInitializer. */
	FORCEINLINE bool IsConstructible() const
	{
		return _data.isConstructible;
	}

	/** Returns whether this type is destructible. */
	FORCEINLINE bool IsDestructible() const
	{
		return _data.isDestructible;
	}

	/** Returns whether this type is trivial (it can be safely memcopy'd). */
	FORCEINLINE bool IsTrivial() const
	{
		return _data.isTrivial;
	}

	/** Returns the constructor for this type.
	* NOTE: Returns an empty implementation if this type is not constructible. */
	FORCEINLINE Constructor GetConstructor() const
	{
		return _data.constructor;
	}

	/** Returns the destructor for this type.
	* NOTE: Returns an empty implementation if this type is not destructible. */
	FORCEINLINE Destructor GetDestructor() const
	{
		return _data.destructor;
	}

	/** Returns whether this type is bitwise castable to the given type */
	virtual bool IsCastableTo(const TypeInfo& type) const = 0;

	/** Returns whether this type is stable (its memory layout is unlikely to ever change). */
	virtual bool IsStable() const = 0;

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
		Constructor constructor;
		Destructor destructor;
		String(*toStringImplementation)(const void*);
		String(*fromStringImplementation)(void*, const String&);
		void(*toArchiveImplementation)(const void*, ArchiveNode&);
		void(*fromArchiveImplementation)(void*, const ArchiveNode&);
		uint32 size;
		bool isCompound;
		bool isAbstract;
		bool isPolymorphic;
		bool isConstructible;
		bool isDestructible;
		bool isTrivial;
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
		_data.name = name;

		if (std::is_constructible<T, DynamicInitializer>::value)
		{
			_data.constructor = [](byte* location) -> void
			{
				Implementation::Construct<T, DynamicInitializer>::Function(location, DynamicInitializer{});
			};
		}
		else
		{
			_data.constructor = Implementation::Construct<T>::Function;
		}

		_data.destructor = [](void* value) -> void
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
		_data.isConstructible = std::is_constructible<T, DynamicInitializer>::value || std::is_default_constructible<T>::value;
		_data.isDestructible = std::is_destructible<T>::value;
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
