// DataInfo.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/DataInfo.h"
#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/EnumInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(DataInfo);

BUILD_ENUM_REFLECTION(DataFlags);

////////////////////////
///   Constructors   ///

DataInfo::DataInfo(CString name, DataFlags flags)
	: _name(name), _flags(flags)
{
	// All done
}

///////////////////
///   Methods   ///

Variant DataInfo::Get(Variant owner) const
{
	assert(owner.GetType().IsCastableTo(*_ownerType));
	return Variant((byte*)owner.GetValue() + _offset, *_dataType);
}

ImmutableVariant DataInfo::Get(ImmutableVariant owner) const
{
	assert(owner.GetType().IsCastableTo(*_ownerType));
	return ImmutableVariant((const byte*)owner.GetValue() + _offset, *_dataType);
}
