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

/** Base of every reflection meta-class in the engine */
class CORE_API TypeInfo : public Object
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(Object);
	template <typename T> friend String ToString(const T&);
	template <typename T> friend String FromString(T&, const String&);

	///////////////////////
	///   Inner Types   ///
public:

	/** The function signature for a reflected default constructor */
	//using DefaultConstructor = void(byte*);
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

	TypeInfo(const TypeInfo& copy) = delete;
	TypeInfo(TypeInfo&& move);
	~TypeInfo() override;

protected:

	/** @TODO: Documentation */
	template <typename T>
	TypeInfo(T* /*dummy*/, CString name)
		: _name(name)
	{
		_defaultConstructor = [](byte* location)
		{
			Implementation::Construct<T>::Function(location);
		};
		_copyConstructor = [](byte* location, const void* copy)
		{
			Implementation::Construct<T, const T&>::Function(location, *static_cast<const T*>(copy));
		};
		_moveConstructor = [](byte* location, void* move)
		{
			Implementation::Construct<T, T&&>::Function(location, std::move(*static_cast<T*>(move)));
		};
		_copyAssignmentOperator = [](void* value, const void* copy) 
		{
			Implementation::Assign<T, const T&>::Function(*static_cast<T*>(value), *static_cast<const T*>(copy));
		};
		_moveAssignmentOperator = [](void* value, void* move)
		{
			Implementation::Assign<T, T&&>::Function(*static_cast<T*>(value), std::move(*static_cast<T*>(move)));
		};
		_destructor = [](void* value)
		{
			Implementation::Destroy<T>::Function(*static_cast<T*>(value));
		};

		_toStringImplementation = [](const void* value) -> String
		{
			return Implementation::ToString<T>::Function(*static_cast<const T*>(value));
		};
		_fromStringImplementation = [](void* value, const String& string) -> String
		{
			return Implementation::FromString<T>::Function(*static_cast<T*>(value), string);
		};

		_size = sizeof(T);
		_isCompound = std::is_class<T>::value;
		_isAbstract = std::is_abstract<T>::value;
		_isPolymorphic = std::is_polymorphic<T>::value;
		_isDefaultConstructible = std::is_default_constructible<T>::value;
		_isCopyConstructible = std::is_copy_constructible<T>::value;
		_isMoveConstructible = std::is_move_constructible<T>::value;
		_isCopyAssignable = std::is_copy_assignable<T>::value;
		_isMoveAssignable = std::is_move_assignable<T>::value;
		_isDestructible = std::is_destructible<T>::value;

		RegisterWithApplication();
	}
	
	/** Overload for when creating type info for "void" */
	TypeInfo(void* dummy, CString name);

	///////////////////
	///   Methods   ///
public:

	/** Returns this TypeInfo object as a String */
	FORCEINLINE String ToString() const
	{
		return _name;
	}

	/** Returns the static size of this type */
	FORCEINLINE uint32 GetSize() const
	{
		return _size;
	}

	/** Returns the name of this type */
	virtual String GetName() const;

	/** Returns whether this type is a compound type.
	* i.e - It is composed of smaller types (like a class, struct, or interface). */
	FORCEINLINE bool IsCompound() const
	{
		return _isCompound;
	}

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

	/** Returns whether this type is default-constructible. */
	FORCEINLINE bool IsDefaultConstructible() const
	{
		return _isDefaultConstructible;
	}

	/** Returns whether this type is copy-constructible. */
	FORCEINLINE bool IsCopyConstructible() const
	{
		return _isCopyConstructible;
	}

	/** Returns whether this type is move-constructible. */
	FORCEINLINE bool IsMoveConstructible() const
	{
		return _isMoveConstructible;
	}

	/** Returns whether this type is copy-assignable. */
	FORCEINLINE bool IsCopyAssignable() const
	{
		return _isCopyAssignable;
	}

	/** Returns whether this type is move-assignable. */
	FORCEINLINE bool IsMoveAssignable() const
	{
		return _isMoveAssignable;
	}

	/** Returns whether this type is destructible. */
	FORCEINLINE bool IsDestructible() const
	{
		return _isDestructible;
	}

	/** Returns the default constructor for this type.
	* Returns an empty implementation if this type is not copy-constructible. */
	FORCEINLINE DefaultConstructor GetDefaultConstructor() const
	{
		return _defaultConstructor;
	}

	/** Returns the copy-constructor for this type. 
	* Returns an empty implementation if this type is not copy-constructible. */
	FORCEINLINE CopyConstructor GetCopyConstructor() const
	{
		return _copyConstructor;
	}

	/** Returns the move-constructor for this type. 
	* Returns an empty implementation if this type is not move-constructible. */
	FORCEINLINE MoveConstructor GetMoveConstructor() const
	{
		return _moveConstructor;
	}

	/** Returns the copy-assignment operator for this type.
	* Returns an empty implementation if this type is not copy-assignable. */
	FORCEINLINE CopyAssignmentOperator GetCopyAssignmentOperator() const
	{
		return _copyAssignmentOperator;
	}

	/** Returns the move-assignment operator for this type.
	* Returns an empty implementation if this type is not move-assignable. */
	FORCEINLINE MoveAssignmentOperator GetMoveAssignmentOperator() const
	{
		return _moveAssignmentOperator;
	}

	/** Returns the destructor for this type.
	* Returns an empty implementation if this type is not destructible. */
	FORCEINLINE Destructor GetDestructor() const
	{
		return _destructor;
	}

	/** Returns whether this type is bitwise castable to the given type */
	virtual bool IsCastableTo(const TypeInfo& type) const = 0;
	
	/** Returns whether this type is bitwise castable to the given type */
	template <typename T>
	FORCEINLINE bool IsCastableTo() const
	{
		return IsCastableTo(TypeOf<T>());
	}

private:

	/** Registers this TypeInfo instance with the Application singleton. */
	void RegisterWithApplication();

	/////////////////////
	///   Operators   ///
public:

	TypeInfo& operator=(const TypeInfo& copy) = delete;
	TypeInfo& operator=(TypeInfo&& move) = delete;
	friend FORCEINLINE CORE_API bool operator==(const TypeInfo& lhs, const TypeInfo& rhs)
	{
		return &lhs == &rhs || lhs.GetName() == rhs.GetName();
	}
	friend FORCEINLINE CORE_API bool operator!=(const TypeInfo& lhs, const TypeInfo& rhs)
	{
		return !(lhs == rhs);
	}

	////////////////
	///   Data   ///
private:

	CString _name;
	DefaultConstructor _defaultConstructor;
	CopyConstructor _copyConstructor;
	MoveConstructor _moveConstructor;
	CopyAssignmentOperator _copyAssignmentOperator;
	MoveAssignmentOperator _moveAssignmentOperator;
	Destructor _destructor;
	String(*_toStringImplementation)(const void*);
	String(*_fromStringImplementation)(void*, const String&);
	uint32 _size;
	bool _isCompound;
	bool _isAbstract;
	bool _isPolymorphic;
	bool _isDefaultConstructible;
	bool _isCopyConstructible;
	bool _isMoveConstructible;
	bool _isCopyAssignable;
	bool _isMoveAssignable;
	bool _isDestructible;
};

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Default implementation of 'ToString' */
	template <typename T>
	struct ToString final
	{
	private:

		/** Implementation for if the type defines its own "ToString" method (preferred). */
		template <typename F>
		FORCEINLINE static auto Impl(Preferred, const F& value) -> decltype(value.ToString())
		{
			return value.ToString();
		}

		/** Implementation for if the type does not define its own "ToString" method (fallback). */
		template <typename F>
		FORCEINLINE static String Impl(Fallback, const F& value)
		{
			return ::TypeOf<F>().GetName();
		}

	public:

		/** Entry point for the implementation. */
		FORCEINLINE static String Function(const T& value)
		{
			using ReturnType = decltype(Impl(0, value));
			static_assert(std::is_same<String, ReturnType>::value || std::is_same<const String&, ReturnType>::value,
				"The return type of the 'ToString' method must be either a 'String' or a const reference to one.");

			return Impl(0, value);
		}
	};

	/** Default implementation of 'FromString' */
	template <typename T>
	struct FromString final
	{
	private:

		/** Implementation for if the type defines its own 'FromString' method (preferred). */
		template <typename F>
		FORCEINLINE static auto Impl(Preferred, F& value, const String& string) -> decltype(value.FromString(string))
		{
			return value.FromString(string);
		}

		/** Implementation for if the type does not define its own 'FromString' method (fallback). */
		template <typename F>
		FORCEINLINE static const String& Impl(Fallback, F& /*value*/, const String& string)
		{
			return string;
		}

	public:

		/** Entry point for the implementation. */
		FORCEINLINE static String Function(T& value, const String& string)
		{
			using ReturnType = decltype(Impl(0, value, string));
			static_assert(std::is_same<String, ReturnType>::value || std::is_same<const String&, ReturnType>::value,
				"The return type of the 'FromString' method must either be a 'String' or a const reference to one.");

			return Impl(0, value, string);
		}
	};
}

/////////////////////
///   Functions   ///

/** Safely casts from a reference of one type to the target class/interface/type
* WARNING: Returns a null pointer if the cast is invalid (value does not legally translate to the given type) */
template <typename TargetT, typename T>
FORCEINLINE TargetT* Cast(T& value)
{
	static_assert(!std::is_reference<TargetT>::value, "Using 'Cast' to cast to a reference type is not allowed");

	if (::TypeOf(value).template IsCastableTo<TargetT>())
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

/** Returns a pointer to a new instance of the given type, moved from the given value (if it is move-constructible)
* NOTE: If the type is not move-constructible, returns a null pointer
* You can override this behavior by implementing a public move constructor,
* or by specializing the 'Implementation::Copy' struct */
template <typename T>
FORCEINLINE T* Copy(T&& copy)
{
	if (!std::is_polymorphic<T>::value)
	{
		// Call the implementation directly
		return Implementation::Copy<T>::Function(std::move(move));
	}
	else
	{
		/** Get move's type and call its implementation through that */
		return static_cast<T*>(TypeOf(move)._moveConstructor(&move));
	}
}

// TODO: Update this
/** Assigns the given instance to the value of another given instance of the same type (if it is copy-assignable)
* NOTE: If the type is not copy-assignable, returns 'false'
* NOTE: If the given values are not of the same type, returns 'false'
* You can override this behavior by implementing a public copy-assignment operator,
* or by specializing the 'Implementation::Assign' struct */
template <typename T>
FORCEINLINE bool Assign(T& value, const T& copy)
{
	if (!std::is_polymorphic<T>::value)
	{
		// Call the implementation directly
		return Implementation::Assign<T>::Function(value, copy);
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

/** Formats the state of the given value as a String
* NOTE: The default behavior is to return the value's type name
* You can override this behavior by implementing the 'String ToString() const' public member function,
* or by specializing the 'Implementation::ToString' struct */
template <typename T>
FORCEINLINE String ToString(const T& value)
{
	if (!std::is_polymorphic<T>::value)
	{
		// Call the implementation directly
		return Implementation::ToString<T>::Function(value);
	}
	else
	{
		// Get value's type and call its implementation through that
		return TypeOf(value)._toStringImplementation(&value);
	}
}

/** Sets the state of the given value by parsing a String, returning the remainder of the String
* NOTE: The default behavior is to not modify the value and return the String as is
* You can override this behavior by implementing the 'String FromString(const String& string)' public member function,
* or by specializing the 'Implementation::FromString' struct */
template <typename T>
FORCEINLINE String FromString(T& value, const String& string)
{
	if (!std::is_polymorphic<T>::value)
	{
		// Call the implementation directly
		return Implementation::FromString<T>::Function(value, string);
	}
	else
	{
		// Get the value's type and call its implementation through that
		return TypeOf(value)._fromStringImplementation(&value, string);
	}
}
