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
	template <typename AnyType> friend AnyType* Copy(const AnyType&);
	template <typename AnyType> friend AnyType* Copy(AnyType&&);
	template <typename AnyType> friend bool Assign(AnyType&, const AnyType&);
	template <typename AnyType> friend bool Assign(AnyType&, AnyType&&);
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

	/** Defined below */
	template <typename AnyType>
	TypeInfo(AnyType* dummy, const String& name);
	
	/** Overload for when creating type info for "void" */
	TypeInfo(void* dummy, const String& name);

	///////////////////
	///   Methods   ///
public:

	/** Returns this TypeInfo object as a String */
	FORCEINLINE String ToString() const
	{
		return GetName();
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

	/** Returns whether this type is move-constructible */
	FORCEINLINE bool IsMoveConstructible() const
	{
		return _isMoveConstructible;
	}

	/** Returns whether this type is copy-assignable */
	FORCEINLINE bool IsCopyAssignable() const
	{
		return _isCopyAssignable;
	}

	/** Returns whether this type is move-assignable */
	FORCEINLINE bool IsMoveAssignable() const
	{
		return _isMoveAssignable;
	}

	/** Returns whether this type is destructible */
	FORCEINLINE bool IsDestructible() const
	{
		return _isDestructible;
	}

	/** Returns whether this type is bitwise castable to the given type */
	virtual bool IsCastableTo(const TypeInfo& type) const = 0;

	/** Returns a Variant to an instance of this type
	* NOTE: Returns a "void" Variant if this type is not default-constructible, check 'IsDefaultConstructible()' before calling */
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
		return &lhs == &rhs || lhs.GetName() == rhs.GetName();
	}
	friend FORCEINLINE CORE_API bool operator!=(const TypeInfo& lhs, const TypeInfo& rhs)
	{
		return lhs.GetName() != rhs.GetName();
	}

	////////////////
	///   Data   ///
private:

	String _name;
	void*(*_defaultConstructor)();
	void*(*_copyConstructor)(const void*);
	void*(*_moveConstructor)(void*);
	bool(*_copyAssignmentOperator)(void*, const void*);
	bool(*_moveAssigmentOperator)(void*, void*);
	bool(*_destructor)(void*);
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
	/** Default implementation of 'Construct' */
	template <typename AnyType>
	struct Construct final
	{
	private:

		template <typename SameAnyType, bool hasDefaultConstructor>
		struct GetConstructor;

		/** Case for if the type IS default constructible */
		template <typename SameAnyType>
		struct GetConstructor < SameAnyType, true >
		{
			FORCEINLINE static SameAnyType* Function()
			{
				return new SameAnyType();
			}
		};

		/** Case for if the type IS NOT default constructible */
		template <typename SameAnyType>
		struct GetConstructor < SameAnyType, false >
		{
			FORCEINLINE static SameAnyType* Function()
			{
				return nullptr;
			}
		};

	public:

		FORCEINLINE static AnyType* Function()
		{
			return GetConstructor<AnyType, IsConstructible>::Function();
		}

		static const bool IsConstructible = std::is_default_constructible<AnyType>::value;
	};

	/** Default implementation of 'Copy' */
	template <typename AnyType>
	struct Copy final
	{
		/////////////////////////////
		///   Copy-construction   ///
	private:

		template <typename SameAnyType, bool hasCopyConstructor>
		struct GetCopyConstructor;

		/** Case for if the type DOES have a copy constructor */
		template <typename SameAnyType>
		struct GetCopyConstructor < SameAnyType, true >
		{
			FORCEINLINE static SameAnyType* Function(const SameAnyType& copy)
			{
				return new SameAnyType(copy);
			}
		};

		/** Case for if the type DOES NOT have a copy constructor */
		template <typename SameAnyType>
		struct GetCopyConstructor < SameAnyType, false >
		{
			FORCEINLINE static SameAnyType* Function(const SameAnyType& /*copy*/)
			{
				return nullptr;
			}
		};

	public:

		FORCEINLINE static AnyType* Function(const AnyType& copy)
		{
			return GetCopyConstructor<AnyType, IsCopyConstructible>::Function(copy);
		}

		static const bool IsCopyConstructible = std::is_copy_constructible<AnyType>::value;

		/////////////////////////////
		///   Move-construction   ///
	private:

		template <typename SameAnyType, bool hasMoveConstructor>
		struct GetMoveConstructor;

		/** Case for if the type DOES have a move constructor */
		template <typename SameAnyType >
		struct GetMoveConstructor < SameAnyType, true >
		{
			FORCEINLINE static SameAnyType* Function(SameAnyType&& move)
			{
				return new SameAnyType(std::move(move));
			}
		};

		/** Case for if the type DOES NOT have a move constructor */
		template <typename SameAnyType >
		struct GetMoveConstructor < SameAnyType, false >
		{
			FORCEINLINE static SameAnyType* Function(SameAnyType&& /*move*/)
			{
				return nullptr;
			}
		};

	public:

		FORCEINLINE static AnyType* Function(AnyType&& move)
		{
			return GetMoveConstructor<AnyType, IsMoveConstructable>::Function(std::move(move));
		}

		static const bool IsMoveConstructable = std::is_move_constructible<AnyType>::value;
	};

	/** Default implementation of 'Assign' */
	template <typename AnyType>
	struct Assign final
	{
		///////////////////////////
		///   Copy-assignment   ///
	private:

		template <typename SameAnyType, bool isCopyAssignable>
		struct GetCopyAssignmentOperator;

		/** Case for if the type IS copy assignable */
		template <typename SameAnyType>
		struct GetCopyAssignmentOperator < SameAnyType, true >
		{
			FORCEINLINE static bool Function(SameAnyType& value, const SameAnyType& copy)
			{
				value = copy;
				return true;
			}
		};

		/** Case for if the type IS NOT copy assignable */
		template <typename SameAnyType>
		struct GetCopyAssignmentOperator < SameAnyType, false >
		{
			FORCEINLINE static bool Function(SameAnyType& /*value*/, const SameAnyType& /*copy*/)
			{
				return false;
			}
		};

	public:

		FORCEINLINE static bool Function(AnyType& value, const AnyType& copy)
		{
			return GetCopyAssignmentOperator<AnyType, IsCopyAssignable>::Function(value, copy);
		}

		static const bool IsCopyAssignable = std::is_copy_assignable<AnyType>::value;

		///////////////////////////
		///   Move-assignment   ///
	private:

		template <typename SameAnyType, bool isMoveAssignable>
		struct GetMoveAssignmentOperator;

		/** Case for if the type IS move assignable */
		template <typename SameAnyType>
		struct GetMoveAssignmentOperator < SameAnyType, true >
		{
			FORCEINLINE static bool Function(SameAnyType& value, SameAnyType&& move)
			{
				value = std::move(move);
				return true;
			}
		};

		/** Case for if the type IS NOT move assignable */
		template <typename SameAnyType>
		struct GetMoveAssignmentOperator < SameAnyType, false >
		{
			FORCEINLINE static bool Function(SameAnyType& /*value*/, SameAnyType&& /*move*/)
			{
				return false;
			}
		};

	public:

		FORCEINLINE static bool Function(AnyType& value, AnyType&& move)
		{
			return GetMoveAssignmentOperator<AnyType, IsMoveAssignable>::Function(value, std::move(move));
		}

		static const bool IsMoveAssignable = std::is_move_assignable<AnyType>::value;
	};

	/** Default implementation of 'Destroy' */
	template <typename AnyType>
	struct Destroy final
	{
	private:

		template <typename SameAnyType, bool isDestructible>
		struct GetDestructor;

		/** Case for if the type IS destructible */
		template <typename SameAnyType>
		struct GetDestructor < SameAnyType, true >
		{
			FORCEINLINE static bool Function(SameAnyType& value)
			{
				delete &value;
				return true;
			}
		};

		/** Case for if the type IS NOT destructible */
		template <typename SameAnyType>
		struct GetDestructor < SameAnyType, false >
		{
			FORCEINLINE static bool Function(SameAnyType& /*value*/)
			{
				return false;
			}
		};

	public:

		FORCEINLINE static bool Function(AnyType& value)
		{
			return GetDestructor<AnyType, IsDestructible>::Function(value);
		}

		static const bool IsDestructible = std::is_destructible<AnyType>::value;
	};

	/** Default implementation of 'ToString' */
	template <typename AnyType>
	struct ToString final
	{
	private:

		/** Template function for if the type defines its own "ToString" method. */
		template <typename SameAnyType>
		FORCEINLINE static auto ToStringImplementation(const SameAnyType& value, int) -> decltype(value.ToString())
		{
			return value.ToString();
		}

		/** Template function for if the type does not define its own "ToString" method. */
		template <typename SameAnyType>
		FORCEINLINE static String ToStringImplementation(const SameAnyType& value, long)
		{
			return ::TypeOf<AnyType>().GetName();
		}

	public:

		FORCEINLINE static String Function(const AnyType& value)
		{
			using ReturnType = decltype(ToStringImplementation(value, 0));
			static_assert(std::is_same<String, ReturnType>::value || std::is_same<const String&, ReturnType>::value,
				"The return type of the 'ToString' method must be either a 'String' or a const reference to one.");

			return ToStringImplementation(value, 0);
		}
	};

	/** Default implementation of 'FromString' */
	template <typename AnyType>
	struct FromString final
	{
	private:

		/** Template function for if the type defines its own 'FromString' method (preferred). */
		template <typename SameAnyType>
		FORCEINLINE static auto FromStringImplementation(SameAnyType& value, const String& string, int) -> decltype(value.FromString(string))
		{
			return value.FromString(string);
		}

		/** Template function for if the type does not define its own 'FromString' method. */
		template <typename SameAnyType>
		FORCEINLINE static const String& FromStringImplementation(SameAnyType& /*value*/, const String& string, long)
		{
			return string;
		}

	public:

		FORCEINLINE static String Function(AnyType& value, const String& string)
		{
			using ReturnType = decltype(FromStringImplementation(value, string, 0));
			static_assert(std::is_same<String, ReturnType>::value || std::is_same<const String&, ReturnType>::value,
				"The return type of the 'FromString' method must either be a 'String' or a const reference to one.");

			return FromStringImplementation(value, string, 0);
		}
	};
}

////////////////////////
///   Constructors   ///

/** @TODO: Documentation */
template <typename AnyType>
TypeInfo::TypeInfo(AnyType* /*dummy*/, const String& name)
	: _name(name)
{
	_defaultConstructor = []()->void*
	{
		return Implementation::Construct<AnyType>::Function();
	};
	_copyConstructor = [](const void* copy)->void*
	{
		return Implementation::Copy<AnyType>::Function(*static_cast<const AnyType*>(copy));
	};
	_moveConstructor = [](void* move)->void*
	{
		return Implementation::Copy<AnyType>::Function(std::move(*static_cast<AnyType*>(move)));
	};
	_copyAssignmentOperator = [](void* value, const void* copy)->bool
	{
		return Implementation::Assign<AnyType>::Function(*static_cast<AnyType*>(value), *static_cast<const AnyType*>(copy));
	};
	_moveAssigmentOperator = [](void* value, void* move)->bool
	{
		return Implementation::Assign<AnyType>::Function(*static_cast<AnyType*>(value), std::move(*static_cast<AnyType*>(move)));
	};
	_destructor = [](void* value)->bool
	{
		return Implementation::Destroy<AnyType>::Function(*static_cast<AnyType*>(value));
	};

	_toStringImplementation = [](const void* value)->String
	{
		return Implementation::ToString<AnyType>::Function(*static_cast<const AnyType*>(value));
	};
	_fromStringImplementation = [](void* value, const String& string)->String
	{
		return Implementation::FromString<AnyType>::Function(*static_cast<AnyType*>(value), string);
	};

	_size = sizeof(AnyType);
	_isCompound = std::is_class<AnyType>::value;
	_isAbstract = std::is_abstract<AnyType>::value;
	_isPolymorphic = std::is_polymorphic<AnyType>::value;
	_isDefaultConstructible = Implementation::Construct<AnyType>::IsConstructible;
	_isCopyConstructible = Implementation::Copy<AnyType>::IsCopyConstructible;
	_isMoveConstructible = Implementation::Copy<AnyType>::IsMoveConstructable;
	_isCopyAssignable = Implementation::Assign<AnyType>::IsCopyAssignable;
	_isMoveAssignable = Implementation::Assign<AnyType>::IsMoveAssignable;
	_isDestructible = Implementation::Destroy<AnyType>::IsDestructible;

	RegisterWithApplication();
}

/////////////////////
///   Functions   ///

/** Safely casts from a reference of one type to the target class/interface/type
* WARNING: Returns a null pointer if the cast is invalid (value does not legally translate to the given type) */
template <typename TargetType, typename AnyType>
FORCEINLINE TargetType* Cast(AnyType& value)
{
	static_assert(!std::is_reference<TargetType>::value, "Using 'Cast' to cast to a reference type is not allowed");

	if (::TypeOf(value).template IsCastableTo<TargetType>())
	{
		return reinterpret_cast<TargetType*>(&value);
	}
	else
	{
		return nullptr;
	}
}

/** Safely casts from an immutable reference of one type to the target class/interface/type
* WARNING: Returns a null pointer if the cast is invalid (value does not legally translate to the given type) */
template <typename TargetType, typename AnyType>
FORCEINLINE const TargetType* Cast(const AnyType& value)
{
	static_assert(!std::is_reference<TargetType>::value, "Using 'Cast' to cast to a reference is not allowed");
	
	if (::TypeOf(value).IsCastableTo(TypeOf<TargetType>()))
	{
		return reinterpret_cast<const TargetType*>(&value);
	}
	else
	{
		return nullptr;
	}
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
* or by specializing the 'Implementation::Copy' struct */
template <typename AnyType>
FORCEINLINE AnyType* Copy(const AnyType& copy)
{
	if (!std::is_polymorphic<AnyType>::value)
	{
		// Call the implementation directly
		return Implementation::Copy<AnyType>::Function(copy);
	}
	else
	{
		// Get copy's type and call its implementation through that
		return static_cast<AnyType*>(TypeOf(copy)._copyConstructor(&copy));
	}
}

/** Returns a pointer to a new instance of the given type, moved from the given value (if it is move-constructible)
* NOTE: If the type is not move-constructible, returns a null pointer
* You can override this behavior by implementing a public move constructor,
* or by specializing the 'Implementation::Copy' struct */
template <typename AnyType>
FORCEINLINE AnyType* Copy(AnyType&& move)
{
	if (!std::is_polymorphic<AnyType>::value)
	{
		// Call the implementation directly
		return Implementation::Copy<AnyType>::Function(std::move(move));
	}
	else
	{
		/** Get move's type and call its implementation through that */
		return static_cast<AnyType*>(TypeOf(move)._moveConstructor(&move));
	}
}

/** Assigns the given instance to the value of another given instance of the same type (if it is copy-assignable)
* NOTE: If the type is not copy-assignable, returns 'false'
* NOTE: If the given values are not of the same type, returns 'false'
* You can override this behavior by implementing a public copy-assignment operator,
* or by specializing the 'Implementation::Assign' struct */
template <typename AnyType>
FORCEINLINE bool Assign(AnyType& value, const AnyType& copy)
{
	if (!std::is_polymorphic<AnyType>::value)
	{
		// Call the implementation directly
		return Implementation::Assign<AnyType>::Function(value, copy);
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

/** Assigns the given instance to the value of another given instance of the same type (if it is move-assignable)
* NOTE: If the type is not move-assignable, returns 'false'
* NOTE: If the given values are not of the same type, returns 'false'
* You can override this behavior by implementing a public move-assignment operator,
* or by specializing the 'Implementation::Assign' struct */
template <typename AnyType>
FORCEINLINE bool Assign(AnyType& value, AnyType&& move)
{
	if (!std::is_polymorphic<AnyType>::value)
	{
		// Call the implementation directly
		return Implementation::Assign<AnyType>::Function(value, std::move(move));
	}
	else
	{
		const TypeInfo* valueType = &TypeOf(value);

		// Make sure the types are compatible
		if (TypeOf(move).IsCastableTo(*valueType))
		{
			// Call the implementation through reflection
			return valueType->_moveAssigmentOperator(&value, &move);
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
* or by specializing the 'Implementation::Destroy' struct */
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
		// Get value's type and call its implementation through that
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
