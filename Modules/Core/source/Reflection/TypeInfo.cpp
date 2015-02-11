// TypeInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/Registration.h"
#include "../../include/Core/Application.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(TypeInfo);

////////////////////////
///   Constructors   ///

TypeInfo::TypeInfo(uint32 size, const String& name)
	: _size(0), _name(name)
{
	Application::Instance()._types.Add(this);
}

TypeInfo::TypeInfo(TypeInfo&& move)
	: _size(move._size), _name(std::move(move._name))
{
	Application::Instance()._types.Add(this);
}

TypeInfo::~TypeInfo()
{
	Application::Instance()._types.DeleteAll(this);
}

///////////////////
///   Methods   ///

uint32 TypeInfo::GetSize() const
{
	return _size;
}

String TypeInfo::GetName() const
{
	return _name;
}