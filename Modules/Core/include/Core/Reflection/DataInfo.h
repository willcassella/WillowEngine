// DataInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Variant.h"

/////////////////
///   Types   ///

enum DataFlags : byte
{
	DF_None = 0,
	DF_Transient = (1 << 0)
};

/** Class representing the information for a data member (part of the private interface of a compound). */
struct CORE_API DataInfo final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT

	template <typename T, class TypeInfoT>
	friend struct TypeInfoBuilder;

	////////////////////////
	///   Constructors   ///
public:

	DataInfo(CString name, DataFlags flags);

	///////////////////
	///   Methods   ///
public:

	/** Formats this DataInfo as a String. */
	FORCEINLINE String ToString() const
	{
		return GetName();
	}

	/** Gets the name of this data member. */
	FORCEINLINE CString GetName() const
	{
		return _name;
	}

	/** Gets the type of this data member. */
	FORCEINLINE const TypeInfo& GetDataType() const
	{
		return *_dataType;
	}

	/** Get the type that owns this data member. */
	FORCEINLINE const CompoundInfo& GetOwnerType() const
	{
		return *_ownerType;
	}

	/** Returns the flags registered on this data member. */
	FORCEINLINE DataFlags GetFlags() const
	{
		return _flags;
	}

	/** Gets the value of this data member on the given owner.
	* WARNING: The type of 'owner' must be castable to the type that owns this data member (check "GetOwnerType()" first). */
	Variant Get(Variant owner) const;

	/** Gets the value of this data member on the given owner.
	* WARNING: The type of 'owner' must be castable to the type that owns this data member (check "GetOwnerType()" first). */
	ImmutableVariant Get(ImmutableVariant owner) const;

	////////////////
	///   Data   ///
private:

	CString _name;
	const TypeInfo* _dataType;
	const CompoundInfo* _ownerType;
	uint32 _offset;
	DataFlags _flags;
};

//////////////////////
///   Reflection   ///

REFLECTABLE_ENUM(DataFlags)
