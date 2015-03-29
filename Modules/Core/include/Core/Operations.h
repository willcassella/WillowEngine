// Operations.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <type_traits>
#include "config.h"

////////////////////////////////
///   Forward Declarations   ///

/** Defined in 'String.h' */
struct String;

/////////////////////
///   Functions   ///

/** Returns a pointer to a new instance of the given type (if it is default-constructible)
* NOTE: If the type is not default-constructible, returns a null pointer
* You can override this behavior by implementing a public default constructor,
* or by specializing the 'Implementation::Construct' struct */
template <typename AnyType>
AnyType* Construct();

/** Returns a pointer to a new instance of the given type, copied from the given value (if it is copy-constructible)
* NOTE: If the type is not copy-constructible, returns a null pointer
* You can override this behavior by implementing a public copy constructor,
* or by specializing the 'Implementation::CopyConstruct' struct */
template <typename AnyType>
AnyType* CopyConstruct(const AnyType& copy);

/** Assigns the given instance to the value of another given instance of the same type (if it is copy-assignable)
* NOTE: If the type is not copy-assignable, returns 'false' 
* You can override this behavior by implementing a public copy-assignment operator,
* or by specializing the 'Implementation::CopyAssign' struct */
template <typename AnyType>
bool CopyAssign(AnyType& value, const AnyType& copy);

/** Destroys the given instance using 'delete' (if the type is destructible)
* NOTE: If the type is not destructible, returns 'false'
* You can override this behavior by implementing a public destructor,
* or by specializing the 'Implementation::Destruct' struct */
template <typename AnyType>
bool Destroy(AnyType& value);

/** Formats the state of the given value as a String
* NOTE: The default behavior is to return the value's type name
* You can override this behavior by implementing the 'String ToString() const' public member function,
* or by specializing the 'Implementation::ToString' struct */
template <typename AnyType>
String ToString(const AnyType& value);

/** Sets the state of the given value by parsing a String, returning the remainder of the String
* NOTE: The default behavior is to not modify the value and return the String as is
* You can override this behavior by implementing the 'String FromString(const String& string)' public member function,
* or by specializing the 'Implementation::FromString' struct */
template <typename AnyType>
String FromString(AnyType& value, const String& string);

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Default implementation of 'Construct' */
	template <typename AnyType>
	struct Construct
	{
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

		FORCEINLINE static AnyType* Function()
		{
			return GetConstructor<AnyType, std::is_default_constructible<AnyType>::value>::Function();
		}
	};

	/** Default implementation of 'CopyConstruct' */
	template <typename AnyType>
	struct CopyConstruct
	{
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
			FORCEINLINE static SameAnyType* Function(const SameAnyType& copy)
			{
				return nullptr;
			}
		};

		FORCEINLINE static AnyType* Function(const AnyType& copy)
		{
			return GetCopyConstructor<AnyType, std::is_copy_constructible<AnyType>::value>::Function(copy);
		}
	};

	/** Default implementation of 'CopyAssign' */
	template <typename AnyType>
	struct CopyAssign
	{
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
			FORCEINLINE static bool Function(SameAnyType& value, const SameAnyType& copy)
			{
				return false;
			}
		};

		FORCEINLINE static bool Function(AnyType& value, const AnyType& copy)
		{
			return GetCopyAssignmentOperator<AnyType, std::is_copy_assignable<AnyType>::value>::Function(value, copy);
		}
	};

	/** Default implementation of 'Destroy' */
	template <typename AnyType>
	struct Destroy
	{
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
			FORCEINLINE static bool Function(SameAnyType& value)
			{
				return false;
			}
		};

		FORCEINLINE static bool Function(AnyType& value)
		{
			return GetDestructor<AnyType, std::is_destructible<AnyType>::value>::Function(value);
		}
	};

	/** Default implementation of 'ToString' */
	template <typename AnyType>
	struct ToString
	{
		// @TODO: Implement this
	};

	/** Default implementation of 'FromString' */
	template <typename AnyType>
	struct FromString
	{
		// @TODO: Implement this
	};
}