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
.AddProperty("Constructible", "Whether this type may be constructed.", &TypeInfo::IsConstructible, nullptr)
.AddProperty("Destructible", "Whether this type is destructible.", &TypeInfo::IsDestructible, nullptr);

////////////////////////
///   Constructors   ///

TypeInfo::TypeInfo(TypeInfo&& move)
	: _data(std::move(move._data))
{
	RegisterWithApplication();
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

String TypeInfo::GetName() const
{
	return _data.name;
}

void TypeInfo::RegisterWithApplication()
{
	Application::Instance()._types.Add(this);
}
