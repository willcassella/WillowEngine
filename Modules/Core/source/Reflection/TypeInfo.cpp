// TypeInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../Include/Core/Application.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(TypeInfo);

////////////////////////
///   Constructors   ///

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

String TypeInfo::GetName() const
{
	return _name;
}