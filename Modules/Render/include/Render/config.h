// config.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Reflection/Module.h>

///////////////////////////////
///   Build Configuration   ///

#ifdef RENDER_BUILD
	#define RENDER_API EXPORT
#else
	#define RENDER_API IMPORT
#endif

//////////////////////////
///   Initialization   ///

namespace Render
{
	RENDER_API const Module* GetModuleInfo();
}