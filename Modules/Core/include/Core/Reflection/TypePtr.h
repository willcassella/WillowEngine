// TypePtr.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../String.h"
#include "Reflection.h"

/////////////////
///   Types   ///

/** TypePtr replaces using "const TypeInfo*" everywhere, with the additional
* benefit of being indexable (TODO). */
template <class TypeInfoT = TypeInfo>
struct TypePtr final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT;

	////////////////////////
	///   Constructors   ///
public:

	/** Constructs a TypePtr to the given type. */
	TypePtr(const TypeInfoT& type)
		: _type(&type)
	{
		static_assert(std::is_base_of<TypeInfo, TypeInfoT>::value, "'TypeInfoT' must be a TypeInfo type.");
	}

	///////////////////
	///   Methods   ///
public:

	/** Formats the state of this TypeInfo as a String */
	FORCEINLINE String ToString() const
	{
		return _type->ToString();
	}

	/////////////////////
	///   Operators   ///
public:

	FORCEINLINE TypePtr& operator=(const TypeInfoT& type)
	{
		_type = &type;
		return self;
	}
	FORCEINLINE operator const TypeInfoT&() const
	{
		return *_type;
	}
	FORCEINLINE const TypeInfoT& operator*() const
	{
		return *_type;
	}
	FORCEINLINE const TypeInfoT* operator->() const
	{
		return _type;
	}
	friend FORCEINLINE bool operator==(const TypePtr& lhs, const TypeInfoT& rhs)
	{
		return *lhs == rhs;
	}
	friend FORCEINLINE bool operator!=(const TypePtr& lhs, const TypeInfoT& rhs)
	{
		return *lhs != rhs;
	}

	////////////////
	///   Data   ///
private:

	const TypeInfoT* _type;
};
