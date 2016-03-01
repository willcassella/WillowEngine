// Application.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <iostream>
#include <cstdlib>
#include "../include/Core/Application.h"
#include "../include/Core/IO/Console.h"
#include "../include/Core/Reflection/TypeInfo.h"

//////////////////
///   Macros   ///

/** Implementation for loading modules on Windows. */
#if defined OS_WINDOWS

#include <windows.h>

bool OSLoadModule(const String& name)
{
	auto path = name + ".dll";
	auto module = LoadLibrary(path.Cstr());

	if (module == nullptr)
	{
		Console::Error("Could not load module '@'", path);
		return false;
	}
	else
	{
		Console::WriteLine("Sucessfully loaded module '@'", path);
		return true;
	}
}

/** Implement loading modules for UNIX platforms (Linux and OSX) */
#elif defined OS_UNIX

#include <dlfcn.h>

bool OSLoadModule(const String& name)
{
	auto path = name + ".so";
	auto module = dlopen(path.Cstr(), RTLD_LAZY);

	if (module == nullptr)
	{
		Console::Error(dlerror());
		return false;
	}
	else
	{
		Console::WriteLine("Sucessfully loaded module '@'", path);
		return true;
	}
}

#else

#	error Loading modules at runtime has not been implemented for the current OS

#endif

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
	// At the moment this is all that needs to be done
	Application::InitializeTypes();
}

void Application::Terminate(int code)
{
	// Just exit, I might add more to this in the future
	// NOTE: I should probably determine soon if this needs to have more or not, so I could just get rid of it otherwise.
	std::exit(code);
}

const TypeInfo* Application::FindType(const String& name)
{
	for (auto type : Application::Instance()._types)
	{
		if (type->GetName() == name)
		{
			return type;
		}
	}

	return nullptr;
}

bool Application::LoadModule(const String& name)
{
	if (OSLoadModule(name))
	{
		Application::InitializeTypes();
		return true;
	}
	else
	{
		return false;
	}
}

Application& Application::Instance()
{
	static Application app;
	return app;
}

void Application::InitializeTypes()
{
	auto& instance = Application::Instance();
	instance._types.ReserveAdditional(instance._uninitializedTypes.Size());

	for (auto type : instance._uninitializedTypes)
	{
		// Force the type to generate its name
		type->GetName();
		instance._types.Add(type);
	}

	instance._uninitializedTypes.Reset(0);
}
