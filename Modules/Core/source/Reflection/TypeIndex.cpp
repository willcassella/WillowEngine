// TypeIndex.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/TypeIndex.h"
#include "../../include/Core/Reflection/VoidInfo.h"
#include "../../include/Core/Reflection/StructInfo.h"

//////////////////////
///   Reflection   ///

STRUCT_REFLECTION(TypeIndex);

////////////////////////
///   Constructors   ///

TypeIndex::TypeIndex()
	: _type(&TypeOf<void>())
{
	// All done
}

///////////////////
///   Methods   ///

String TypeIndex::ToString() const
{
	return _type->GetName();
}

/////////////////////
///   Operators   ///

bool TypeIndex::operator==(const TypeIndex& rhs) const
{
	return *_type == *rhs._type;
}

bool TypeIndex::operator==(const TypeInfo& rhs) const
{
	return *_type == rhs;
}

bool TypeIndex::operator!=(const TypeIndex& rhs) const
{
	return *_type != *rhs._type;
}

bool TypeIndex::operator!=(const TypeInfo& rhs) const
{
	return *_type != rhs;
}