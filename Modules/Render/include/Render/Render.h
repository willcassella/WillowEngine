// Render.h
#pragma once

#include <Utility\config.h>
#include "config.h"

namespace Willow
{
	typedef uint32 BufferID;
	typedef uint32 GValue;

	namespace API
	{
		enum API
		{
			Null,
			OpenGL
		};
	}

	// Sets up the defaults for the renderer
	RENDER_API void InitRenderer(API::API API);

	// Clear the screen for a new image
	RENDER_API void ClearBuffer();
}