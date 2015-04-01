// Operations.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
/** "Operations" are a collection of generic functions that can be performed on polymorphic and non-polymorphic types.
* These functions can see through polymorphism (using the reflection system), so even if the visible type doesn't implement 
* the desired function, it can still be called if the derived type does. */
#pragma once

#include <type_traits>
#include "config.h"

////////////////////////////////
///   Forward Declarations   ///

/** Defined in 'String.h' */
struct String;

/////////////////////
///   Functions   ///

/** Defined in 'TypeInfo.h' */
template <typename AnyType>
AnyType* Construct();

/** Defined in 'TypeInfo.h' */
template <typename AnyType>
AnyType* CopyConstruct(const AnyType& copy);

/** Defined in 'TypeInfo.h' */
template <typename AnyType>
bool CopyAssign(AnyType& value, const AnyType& copy);

/** Defined in 'TypeInfo.h' */
template <typename AnyType>
bool Destroy(AnyType& value);

/** Defined in 'TypeInfo.h' */
template <typename AnyType>
String ToString(const AnyType& value);

/** Defined in 'TypeInfo.h' */
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
			return GetConstructor<AnyType, IsConstructible>::Function();
		}

		static const bool IsConstructible = std::is_default_constructible<AnyType>::value;
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
			return GetCopyConstructor<AnyType, IsCopyConstructible>::Function(copy);
		}

		static const bool IsCopyConstructible = std::is_copy_constructible<AnyType>::value;
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
			return GetCopyAssignmentOperator<AnyType, IsCopyAssignable>::Function(value, copy);
		}

		static const bool IsCopyAssignable = std::is_copy_assignable<AnyType>::value;
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
			return GetDestructor<AnyType, IsDestructible>::Function(value);
		}

		static const bool IsDestructible = std::is_destructible<AnyType>::value;
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