// StructInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/Registration.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(StructInfo);

////////////////////////
///   Constructors   ///

StructInfo::StructInfo(uint32 size, const String& name, Value(*stackFactory)(), Variant(*heapFactory)())
	: Super(size, name), _stackFactory(stackFactory), _heapFactory(heapFactory), _fields()
{
	// All done
}

StructInfo::StructInfo(StructInfo&& move)
	: Super(std::move(move)), _stackFactory(move._stackFactory), _heapFactory(move._heapFactory), _fields(std::move(move._fields))
{
	// All done
}

StructInfo::~StructInfo()
{
	for (const auto& pair : _fields)
	{
		delete pair.Second;
	}
}

///////////////////
///   Methods   ///

bool StructInfo::IsAbstract() const
{
	return false;
}

bool StructInfo::IsPolymorphic() const
{
	return false;
}

bool StructInfo::IsInstantiable() const
{
	return true;
}

bool StructInfo::IsCastableTo(const TypeInfo& type) const
{
	// Structs are never castable to anything other than themselves
	return type == This;
}

Value StructInfo::StackInstance() const
{
	return _stackFactory();
}

Variant StructInfo::HeapInstance() const
{
	return _heapFactory();
}

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Register TypeInfo for String */
	const StructInfo TypeOf<String>::StaticTypeInfo = StructInfo::Create<String>("String");
}