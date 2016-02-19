// MemoryManager.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../config.h"
#include "../Forwards/Core.h"

struct CORE_API MemoryManager final
{
	///////////////////////
	///   Information   ///
public:

	/** MemoryManager is part of the Application singleton. */
	friend Application;

	////////////////////////
	///   Constructors   ///
private:

	MemoryManager() = default;
	MemoryManager(const MemoryManager& copy) = delete;
	MemoryManager(MemoryManager&& move) = delete;
	~MemoryManager() = default;
};
