// TypeInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/PrimitiveInfo.h"
#include "../../include/Core/Application.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(TypeInfo)
.AddProperty("Name", "The name of the type.", &TypeInfo::GetName, nullptr)
.AddProperty("Size", "The size (in bytes) of an instance of this type.", &TypeInfo::GetSize, nullptr)
.AddProperty("Compound", "Whether this type is a compound type.", &TypeInfo::IsCompound, nullptr)
.AddProperty("Abstract", "Whether this type is an abstract type.", &TypeInfo::IsAbstract, nullptr)
.AddProperty("Polymorphic", "Whether this type is polymorphic.", &TypeInfo::IsPolymorphic, nullptr)
.AddProperty("Default-Constructible", "Whether this type is default-constructible", &TypeInfo::IsDefaultConstructible, nullptr)
.AddProperty("Copy-Constructible", "Whether this type is copy-constructible.", &TypeInfo::IsCopyConstructible, nullptr)
.AddProperty("Move-Constructible", "Whether this type is move-constructible.", &TypeInfo::IsMoveConstructible, nullptr)
.AddProperty("Copy-Assignable", "Whether this type is copy-assignable.", &TypeInfo::IsCopyAssignable, nullptr)
.AddProperty("Move-Assignable", "Whether this type is move-assignable.", &TypeInfo::IsMoveAssignable, nullptr)
.AddProperty("Destructible", "Whether this type is destructible.", &TypeInfo::IsDestructible, nullptr);

TypeInfo::~TypeInfo()
{
	Application::Instance()._types.DeleteFirst(self);
}

///////////////////
///   Methods   ///

String TypeInfo::GetName() const
{
	return _data.name;
}

void TypeInfo::RegisterWithApplication()
{
	Application::Instance()._types.Add(self);
}
