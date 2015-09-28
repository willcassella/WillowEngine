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

	/** Performs operations necessary to begin shutting down the application. 
	* NOTE: This should be the last function called before 'main' returns. */
	static void BeginShutdown();

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

	static const TypeInfo* FindType(const String& name);

private:

	static Application& Instance();

	////////////////
	///   Data   ///
private:

	MemoryManager _memoryManager;
	Array<const TypeInfo*> _types;
};
