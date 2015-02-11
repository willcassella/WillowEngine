// InterfaceInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/Registration.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(InterfaceInfo);

////////////////////////
///   Constructors   ///

InterfaceInfo::InterfaceInfo(uint32 size, const String& name)
	: Super(size, name)
{
	// All done
}

InterfaceInfo::InterfaceInfo(InterfaceInfo&& move)
	: Super(std::move(move))
{
	// All done
}

///////////////////
///   Methods   ///

bool InterfaceInfo::IsAbstract() const
{
	return true;
}

bool InterfaceInfo::IsPolymorphic() const
{
	return true;
}

bool InterfaceInfo::IsInstantiable() const
{
	return false;
}

bool InterfaceInfo::IsCastableTo(const TypeInfo& type) const
{
	return type == This || type == TypeOf<Object>();
}

Value InterfaceInfo::StackInstance() const
{
	return Value(); // Null Value
}

Reference InterfaceInfo::HeapInstance() const
{
	return Reference(); // Null Reference
}