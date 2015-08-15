// Application.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Core/Application.h"
#include "../include/Core/Reflection/TypeInfo.h"

///////////////////
///   Methods   ///

Application& Application::Instance()
{
	static Application app;
	return app;
}

const Array<const TypeInfo*>& Application::GetAllTypes()
{
	return Instance()._types;
}

const TypeInfo* Application::FindType(const String& name)
{
	for (auto type : GetAllTypes())
	{
		if (type->GetName() == name)
		{
			return &*type;
		}
	}

	return nullptr;
}
