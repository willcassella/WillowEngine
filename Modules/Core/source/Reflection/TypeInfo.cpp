// TypeInfo.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/PrimitiveInfo.h"
#include "../../include/Core/Application.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(TypeInfo)
.Property("Name", &TypeInfo::get_name, nullptr, "The name of the type.")
.Property("Size", &TypeInfo::get_size, nullptr, "The size (in bytes) of an instance of this type.")
.Property("Compound", &TypeInfo::is_compound, nullptr, "Whether this type is a compound type.")
.Property("Abstract", &TypeInfo::is_abstract, nullptr, "Whether this type is an abstract type.")
.Property("Polymorphic", &TypeInfo::is_polymorphic, nullptr, "Whether this type is polymorphic.")
.Property("Trivial", &TypeInfo::is_trivial, nullptr, "Whether this type is trivial.")
.Property("Default Constructible", &TypeInfo::is_default_constructible, nullptr, "Whether this type may be constructed.")
.Property("Has Dynamic Constructor", &TypeInfo::is_dynamically_constructible, nullptr, "Whether this type has a dynamic constructor.")
.Property("Copy Constructible", &TypeInfo::is_copy_constructible, nullptr, "Whether this type is copy-constructible.")
.Property("Move Constructible", &TypeInfo::is_move_constructible, nullptr, "Whether this type is move-constructible")
.Property("Destructible", &TypeInfo::is_destructible, nullptr, "Whether this type is destructible.")
.Property("Copy Assignable", &TypeInfo::is_copy_assignable, nullptr, "Whether this type is copy-assignable.")
.Property("Move Assignable", &TypeInfo::is_move_assignable, nullptr, "Whether this type is move-assignable");

////////////////////////
///   Constructors   ///

TypeInfo::TypeInfo(TypeInfo&& move)
	: Base(NoReferenceCount), _data(std::move(move._data))
{
	this->register_with_application();
	// So basically with this, the compiler only has to THINK that TypeInfo objects are move-constructible (which I guess they are, but whatever).
	// When you initialize an object with "T blah = arg", the standard says that the type HAS to be move-constructible, even though the compiler implementor is free to not call it.
	// Honestly, I think this is one of the dumbest fucking things I've ever seen, and an example of the language failing to support the intention of the programmer. If you're initializing
	// something, it should just be initialization, not initialization and then copying.
}

TypeInfo::~TypeInfo()
{
	Application::Instance()._uninitializedTypes.DeleteFirst(this);
}

///////////////////
///   Methods   ///

String TypeInfo::generate_name() const
{
	return _data.raw_name;
}

void TypeInfo::register_with_application()
{
	Application::Instance()._uninitializedTypes.Add(this);
}
