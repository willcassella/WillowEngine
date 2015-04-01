// Module.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/Module.h"
#include "../../include/Core/Reflection/ClassInfo.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(Module);

////////////////////////
///   Constructors   ///

Module::Module(const String& name)
	: _name(name)
{
	// All done
}

///////////////////
///   Methods   ///

String Module::GetName() const
{
	return _name;
}

String Module::GetAuthors() const
{
	return _authors;
}

Array<const TypeInfo*> Module::GetTypes() const
{
	Array<const TypeInfo*> types(_types.Size());

	for (const auto& type : _types)
	{
		types.Add(type.Second);
	}

	return types;
}