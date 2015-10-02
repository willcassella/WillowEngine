// Application.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <cstdlib>
#include "../include/Core/Application.h"
#include "../include/Core/Reflection/TypeInfo.h"

///////////////////
///   Methods   ///

void Application::Initialize()
{
	// Register the 'Application::AtExit' function to execute when 'main' returns
	int atExitResult = std::atexit(Application::AtExit);
	assert(atExitResult == 0);
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

Application& Application::Instance()
{
	static Application app;
	return app;
}

void Application::AtExit()
{
	// Remove all references
	GetMemoryManager().Sweep();
}
