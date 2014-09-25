// Render.h
#pragma once

#include <Utility\config.h>
#include "config.h"

namespace Willow
{
	typedef uint32 BufferID;
	typedef uint32 GValue;

	enum class API
	{
		Null,
		OpenGL
	};

	// Sets up the defaults for the renderer
	RENDER_API void InitRenderer(API api);

	// Clear the screen for a new image
	RENDER_API void ClearBuffer();
}