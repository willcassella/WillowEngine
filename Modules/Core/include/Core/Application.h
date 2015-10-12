// Application.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Containers/Array.h"
#include "Reflection/TypePtr.h"
#include "Memory/MemoryManager.h"

struct CORE_API Application final
{
	///////////////////////
	///   Information   ///
public:

	friend TypeInfo;
	
private:

	Application() = default;

	///////////////////
	///   Methods   ///
public:

	/** Performs start-up procedures for the Application. This should be the first function called in 'main'. */
	static void Initialize();

	/** Performs shutdown procedure for the Applicaion. This should be the last function called in 'main'. */
	static void Terminate(int code = 0);

	/** Returns the default memory manager for this Application. */
	FORCEINLINE static MemoryManager& GetMemoryManager()
	{
		return Instance()._memoryManager;
	}

	/** Returns a collection of all currently loaded types. */
	FORCEINLINE static const Array<const TypeInfo*>& GetAllTypes()
	{
		return Instance()._types;
	}

	/** Searches for a type matching the given name.
	* NOTE: Returns a null pointer if the type was not found. */
	static const TypeInfo* FindType(const String& name);

private:

	/** Returns the instance of the Application singleton. */
	static Application& Instance();

	/** Behavior run when 'main' returns, registered in 'Initialize' (which is why calling that function is crucial). */
	static void AtExit();

	////////////////
	///   Data   ///
private:

	MemoryManager _memoryManager;
	Array<const TypeInfo*> _types;
};
