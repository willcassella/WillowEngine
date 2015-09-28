// Object.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Core/Reflection/ClassInfo.h"
#include "../include/Core/Application.h"

//////////////////////
///   Reflection   ///

const ClassInfo Object::StaticTypeInfo = TypeInfoBuilder<Object>();

////////////////////////
///   Constructors   ///

Object::Object()
{
	ReferenceClearStatus = ReferenceClearState::Required;
}

Object::~Object()
{
	// 99% of the time the memory manager will have already done this and reset 'ReferenceClearStatus'.
	// This is for the 1%.
	if (ReferenceClearStatus == ReferenceClearState::Required)
	{
		Application::GetMemoryManager().ClearReferences(this);
		ReferenceClearStatus = ReferenceClearState::Complete;
	}

	for (auto& ref : _references)
	{
		*reinterpret_cast<void**>(ref) = nullptr;
	}
}

///////////////////
///   Methods   ///

String Object::ToString() const
{
	return Implementation::Default::ToString(self);
}

String Object::FromString(const String& string)
{
	return Implementation::Default::FromString(self, string);
}

void Object::ToArchive(ArchiveNode& node) const
{
	Implementation::Default::ToArchive(self, node);
}

void Object::FromArchive(const ArchiveNode& node)
{
	Implementation::Default::FromArchive(self, node);
}
