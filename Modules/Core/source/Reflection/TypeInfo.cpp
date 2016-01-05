// TypeInfo.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/PrimitiveInfo.h"
#include "../../include/Core/Application.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(TypeInfo)
.Property("Name", &TypeInfo::GetName, nullptr, "The name of the type.")
.Property("Size", &TypeInfo::GetSize, nullptr, "The size (in bytes) of an instance of this type.")
.Property("Compound", &TypeInfo::IsCompound, nullptr, "Whether this type is a compound type.")
.Property("Abstract", &TypeInfo::IsAbstract, nullptr, "Whether this type is an abstract type.")
.Property("Polymorphic", &TypeInfo::IsPolymorphic, nullptr, "Whether this type is polymorphic.")
.Property("Trivial", &TypeInfo::IsTrivial, nullptr, "Whether this type is trivial.")
.Property("Default Constructible", &TypeInfo::IsDefaultConstructible, nullptr, "Whether this type may be constructed.")
.Property("Has Dynamic Constructor", &TypeInfo::HasDynamicConstructor, nullptr, "Whether this type has a dynamic constructor.")
.Property("Copy Constructible", &TypeInfo::IsCopyConstructible, nullptr, "Whether this type is copy-constructible.")
.Property("Move Constructible", &TypeInfo::IsMoveConstructible, nullptr, "Whether this type is move-constructible")
.Property("Destructible", &TypeInfo::IsDestructible, nullptr, "Whether this type is destructible.")
.Property("Copy Assignable", &TypeInfo::IsCopyAssignable, nullptr, "Whether this type is copy-assignable.")
.Property("Move Assignable", &TypeInfo::IsMoveAssignable, nullptr, "Whether this type is move-assignable");

////////////////////////
///   Constructors   ///

TypeInfo::TypeInfo(TypeInfo&& move)
	: _data(std::move(move._data))
{
	this->RegisterWithApplication();
	// So basically with this, the compiler only has to THINK that TypeInfo objects are move-constructible (which I guess they are, but whatever).
	// When you initialize an object with "T blah = arg", the standard says that the type HAS to be move-constructible, even though the compiler implementor is free to not call it.
	// Honestly, I think this is one of the dumbest fucking things I've ever seen, and an example of the language failing to support the intention of the programmer. If you're initializing
	// something, it should just be initialization, not initialization and then copying.
}

TypeInfo::~TypeInfo()
{
	Application::Instance()._types.DeleteFirst(this);
}

///////////////////
///   Methods   ///

String TypeInfo::GenerateName() const
{
	return _data.rawName;
}

void TypeInfo::RegisterWithApplication()
{
	Application::Instance()._types.Add(this);
}
