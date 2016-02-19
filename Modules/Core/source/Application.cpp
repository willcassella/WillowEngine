// Application.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <iostream>
#include <cstdlib>
#include "../include/Core/Application.h"
#include "../include/Core/Reflection/TypeInfo.h"

////////////////////////
///   Constructors   ///

Application::Application()
{
	// For some reason this needs to be constructed, otherwise printing upon starting (ie, pre-main) on linux will
	// occasionally fail completely.
	std::ios_base::Init initializer;
}

///////////////////
///   Methods   ///

void Application::Initialize()
{
	for (auto type : Instance()._types)
	{
		// Force the type to generate its name
		type->GetName();
	}
}

void Application::Terminate(int code)
{
	std::exit(code);
}

const TypeInfo* Application::FindType(const String& name)
{
	for (auto type : GetAllTypes())
	{
		if (type->GetName() == name)
		{
			return type;
		}
	}

	return nullptr;
}

Application& Application::Instance()
{
	static Application app;
	return app;
}
