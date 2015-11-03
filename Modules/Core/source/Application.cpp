// Application.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <cstdlib>
#include "../include/Core/Console.h"
#include "../include/Core/Application.h"
#include "../include/Core/Reflection/TypeInfo.h"

////////////////////////
///   Constructors   ///

Application::Application()
{
	// Do nothing
}

Application::~Application()
{
	GetMemoryManager().Sweep();
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
