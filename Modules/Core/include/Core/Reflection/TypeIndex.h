// TypeIndex.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../config.h"
#include "../Forwards/Core.h"
#include "Reflection.h"

/////////////////
///   Types   ///

struct CORE_API TypeIndex final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT;

	////////////////////////
	///   Constructors   ///
public:

	/** Constructs a TypeIndex to 'void' */
	TypeIndex();

	/** Constructs a TypeIndex to the given type */
	TypeIndex(const TypeInfo& type);

	///////////////////
	///   Methods   ///
public:

	/** Formats the state of this TypeInfo as a String */
	String ToString() const;

	/////////////////////
	///   Operators   ///
public:

	TypeIndex& operator=(const TypeInfo& type);
	operator const TypeInfo&() const;
	const TypeInfo& operator*() const;
	const TypeInfo* operator->() const;
	bool operator==(const TypeIndex& rhs) const;
	bool operator==(const TypeInfo& rhs) const;
	bool operator!=(const TypeIndex& rhs) const;
	bool operator!=(const TypeInfo& rhs) const;

	////////////////
	///   Data   ///
private:

	const TypeInfo* _type;
};
