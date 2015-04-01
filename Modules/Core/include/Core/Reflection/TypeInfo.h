// TypeInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../String.h"
#include "../Object.h"

/////////////////
///   Types   ///

/** Base of every reflection meta-class in the engine */
class CORE_API TypeInfo : public Object
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(Object);
	friend Variant;
	friend VoidInfo;
	template <typename AnyType> friend AnyType* CopyConstruct(const AnyType&);
	template <typename AnyType> friend bool CopyAssign(AnyType&, const AnyType&);
	template <typename AnyType> friend bool Destroy(AnyType&);
	template <typename AnyType> friend String ToString(const AnyType&);
	template <typename AnyType> friend String FromString(AnyType&, const String&);

	////////////////////////
	///   Constructors   ///
public:

	TypeInfo(const TypeInfo& copy) = delete;
	TypeInfo(TypeInfo&& move);
	~TypeInfo() override;

protected:

	/** @TODO: Documentation */
	template <typename AnyType>
	TypeInfo(AnyType* dummy, const String& name)
		: _name(name)
	{
		_constructor = []()->void* 
		{ 
			return Implementation::Construct<AnyType>::Function();
		};
		_copyConstructor = [](const void* copy)->void* 
		{ 
			return Implementation::CopyConstruct<AnyType>::Function(*static_cast<const AnyType*>(copy)); 
		};
		_copyAssignmentOperator = [](void* value, const void* copy)->bool 
		{
			return Implementation::CopyAssign<AnyType>::Function(*static_cast<AnyType*>(value), *static_cast<const AnyType*>(copy));
		};
		_destructor = [](void* value)->bool
		{
			return Implementation::Destroy<AnyType>::Function(*static_cast<AnyType*>(value));
		};

		_size = sizeof(AnyType);
		_isAbstract = std::is_abstract<AnyType>::value;
		_isPolymorphic = std::is_polymorphic<AnyType>::value;
		_isDefaultConstructible = Implementation::Construct<AnyType>::IsConstructible;
		_isCopyConstructible = Implementation::CopyConstruct<AnyType>::IsCopyConstructible;
		_isCopyAssignable = Implementation::CopyAssign<AnyType>::IsCopyAssignable;
		_isDestructible = Implementation::Destroy<AnyType>::IsDestructible;

		RegisterWithApplication();
	}

private:

	// @TODO: Find better way of doing this?
	/** Special constructor for creating TypeInfo for 'void' */
	TypeInfo(const String& name);

	///////////////////
	///   Methods   ///
public:

	/** Returns the static size of this type */
	FORCEINLINE uint32 GetSize() const
	{
		return _size;
	}

	/** Returns the name of this type */
	virtual String GetName() const;

	/** Returns whether this type is abstract
	* i.e - It has at least one pure virtual function */
	FORCEINLINE bool IsAbstract() const
	{
		return _isAbstract;
	}

	/** Returns whether this type is polymorphic
	* i.e - It has at least one virtual function */
	FORCEINLINE bool IsPolymorphic() const
	{
		return _isPolymorphic;
	}

	/** Returns whether this type is default-constructible */
	FORCEINLINE bool IsDefaultConstructible() const
	{
		return _isDefaultConstructible;
	}

	/** Returns whether this type is copy-constructible */
	FORCEINLINE bool IsCopyConstructible() const
	{
		return _isCopyConstructible;
	}

	/** Returns whether this type is copy-assignable */
	FORCEINLINE bool IsCopyAssignable() const
	{
		return _isCopyAssignable;
	}

	/** Returns whether this type is destructible */
	FORCEINLINE bool IsDestructible() const
	{
		return _isDestructible;
	}

	/** Returns whether this type is bitwise castable to the given type */
	virtual bool IsCastableTo(const TypeInfo& type) const = 0;

	/** Returns a Variant to an instance of this type
	* NOTE: Callee has ownership over the lifetime of returned value (it must be deleted manually)
	* NOTE: Returns a "void" Variant if this type is not default-constructible, check 'IsConstructible()' before calling */
	Variant Construct() const;
	
	/** Returns whether this type is bitwise castable to the given type */
	template <typename AnyType>
	FORCEINLINE bool IsCastableTo() const
	{
		return IsCastableTo(TypeOf<AnyType>());
	}

private:

	/** Registers this TypeInfo object with the global 'Application' object */
	void RegisterWithApplication();

	/////////////////////
	///   Operators   ///
public:

	TypeInfo& operator=(const TypeInfo& copy) = delete;
	TypeInfo& operator=(TypeInfo&& move) = delete;
	friend FORCEINLINE CORE_API bool operator==(const TypeInfo& lhs, const TypeInfo& rhs)
	{
		return lhs.GetName() == rhs.GetName();
	}
	friend FORCEINLINE CORE_API bool operator!=(const TypeInfo& lhs, const TypeInfo& rhs)
	{
		return lhs.GetName() != rhs.GetName();
	}

	////////////////
	///   Data   ///
private:

	String _name;
	void*(*_constructor)();
	void*(*_copyConstructor)(const void*);
	bool(*_copyAssignmentOperator)(void*, const void*);
	bool(*_destructor)(void*);
	String(*_toStringImplementation)(const void*);
	String(*_fromStringImplementation)(void*, const String&);
	uint32 _size;
	bool _isAbstract;
	bool _isPolymorphic;
	bool _isDefaultConstructible;
	bool _isCopyConstructible;
	bool _isCopyAssignable;
	bool _isDestructible;
};

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Default implementation of "Cast" */
	template <typename TargetType, typename AnyType>
	struct Cast
	{
		/** Attempt to cast reference */
		FORCEINLINE static TargetType* Function(AnyType& value)
		{
			if (::TypeOf(value).template IsCastableTo<TargetType>())
			{
				return reinterpret_cast<TargetType*>(&value);
			}
			else
			{
				return nullptr;
			}
		}

		/** Attempt to cast const reference */
		FORCEINLINE static const TargetType* Function(const AnyType& value)
		{
			if (::TypeOf(value).template IsCastableTo<TargetType>())
			{
				return reinterpret_cast<const TargetType*>(&value);
			}
			else
			{
				return nullptr;
			}
		}
	};
}

/////////////////////
///   Functions   ///

/** Safely casts from a reference of one type to the target class/interface/type
* WARNING: Returns a null pointer if the cast is invalid (value does not legally translate to the given type)
* DO NOT OVERLOAD: Specialize struct 'Implementation::Cast' */
template <typename TargetType, typename AnyType>
FORCEINLINE TargetType* Cast(AnyType& value)
{
	static_assert(!std::is_reference<TargetType>::value, "Using 'Cast' to cast to a reference type is not allowed");
	return Implementation::Cast<TargetType, AnyType>::Function(value);
}

/** Safely casts from an immutable reference of one type to the target class/interface/type
* WARNING: Returns a null pointer if the cast is invalid (value does not legally translate to the given type)
* DO NOT OVERLOAD: Specialize struct 'Implementation::Cast' */
template <typename TargetType, typename AnyType>
FORCEINLINE const TargetType* Cast(const AnyType& value)
{
	static_assert(!std::is_reference<TargetType>::value, "Using 'Cast' to cast to a reference is not allowed");
	return Implementation::Cast<TargetType, AnyType>::Function(value);
}

//////////////////////
///   Operations   ///

/** Returns a pointer to a new instance of the given type (if it is default-constructible)
* NOTE: If the type is not default-constructible, returns a null pointer
* You can override this behavior by implementing a public default constructor,
* or by specializing the 'Implementation::Construct' struct */
template <typename AnyType>
FORCEINLINE AnyType* Construct()
{
	// Call the implementation directly
	return Implementation::Construct<AnyType>::Function();
}

/** Returns a pointer to a new instance of the given type, copied from the given value (if it is copy-constructible)
* NOTE: If the type is not copy-constructible, returns a null pointer
* You can override this behavior by implementing a public copy constructor,
* or by specializing the 'Implementation::CopyConstruct' struct */
template <typename AnyType>
FORCEINLINE AnyType* CopyConstruct(const AnyType& copy)
{
	if (!std::is_polymorphic<AnyType>::value)
	{
		// Call the implementation directly
		return Implementation::CopyConstruct<AnyType>::Function(copy);
	}
	else
	{
		// Get the copy's type and call its implementation through that
		return TypeOf<copy>()._copyConstructor(&copy);
	}
}

/** Assigns the given instance to the value of another given instance of the same type (if it is copy-assignable)
* NOTE: If the type is not copy-assignable, returns 'false'
* NOTE: If the given values are not of the same type, returns 'false'
* You can override this behavior by implementing a public copy-assignment operator,
* or by specializing the 'Implementation::CopyAssign' struct */
template <typename AnyType>
FORCEINLINE bool CopyAssign(AnyType& value, const AnyType& copy)
{
	if (!std::is_polymorphic<AnyType>::value)
	{
		// Call the implementation directly
		return Implementation::CopyAssign<AnyType>::Function(value, copy);
	}
	else
	{
		const TypeInfo* valueType = &TypeOf(value);

		// Make sure the types are compatible
		if (TypeOf(copy).IsCastableTo(*valueType))
		{
			// Call the implementation through reflection
			return valueType->_copyAssignmentOperator(&value, &copy);
		}
		else
		{
			return false;
		}
	}
}

/** Destroys the given instance using 'delete' (if the type is destructible)
* NOTE: If the type is not destructible, returns 'false'
* You can override this behavior by implementing a public destructor,
* or by specializing the 'Implementation::Destruct' struct */
template <typename AnyType>
FORCEINLINE bool Destroy(AnyType& value)
{
	if (!std::is_polymorphic<AnyType>::value)
	{
		// Call the implementation directly
		return Implementation::Destroy<AnyType>::Function(value);
	}
	else
	{
		// Get the value's type and call its implementation through that
		return TypeOf(value)._destructor(&value);
	}
}

/** Formats the state of the given value as a String
* NOTE: The default behavior is to return the value's type name
* You can override this behavior by implementing the 'String ToString() const' public member function,
* or by specializing the 'Implementation::ToString' struct */
template <typename AnyType>
FORCEINLINE String ToString(const AnyType& value)
{
	if (!std::is_polymorphic<AnyType>::value)
	{
		// Call the implementation directly
		return Implementation::ToString<AnyType>::Function(value);
	}
	else
	{
		// Get the value's type and call its implementation through that
		return TypeOf(value)._toStringImplementation(&value);
	}
}

/** Sets the state of the given value by parsing a String, returning the remainder of the String
* NOTE: The default behavior is to not modify the value and return the String as is
* You can override this behavior by implementing the 'String FromString(const String& string)' public member function,
* or by specializing the 'Implementation::FromString' struct */
template <typename AnyType>
FORCEINLINE String FromString(AnyType& value, const String& string)
{
	if (!std::is_polymorphic<AnyType>::value)
	{
		// Call the implementation directly
		return Implementation::FromString<AnyType>::Function(value, string);
	}
	else
	{
		// Get the value's type and call its implementation through that
		return TypeOf(value)._fromStringImplementation(&value, string);
	}
}