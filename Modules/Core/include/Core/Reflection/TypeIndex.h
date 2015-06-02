// TypeIndex.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Reflection.h"

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
	TypeIndex(const TypeInfo& type)
		: _type(&type)
	{
		// All done
	}

	/////////////////////
	///   Operators   ///
public:

	FORCEINLINE TypeIndex& operator=(const TypeInfo& type)
	{
		_type = &type;
		return This;
	}
	FORCEINLINE operator const TypeInfo&() const
	{
		return *_type;
	}
	FORCEINLINE const TypeInfo& operator*() const
	{
		return *_type;
	}
	FORCEINLINE const TypeInfo* operator->() const
	{
		return _type;
	}
	bool operator==(const TypeIndex& rhs) const;
	bool operator==(const TypeInfo& rhs) const;
	bool operator!=(const TypeIndex& rhs) const;
	bool operator!=(const TypeInfo& rhs) const;

	////////////////
	///   Data   ///
private:

	const TypeInfo* _type;
};
