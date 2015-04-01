// StructInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/ClassInfo.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(StructInfo);

////////////////////////
///   Constructors   ///

StructInfo::StructInfo(StructInfo&& move)
	: Super(std::move(move)), _fields(std::move(move._fields))
{
	// All done
}

///////////////////
///   Methods   ///

bool StructInfo::IsCastableTo(const TypeInfo& type) const
{
	// Structs are never castable to anything other than themselves
	return type == This;
}

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Register TypeInfo for String */
	const StructInfo TypeOf<String>::StaticTypeInfo = StructInfo::Create<String>("String");
}