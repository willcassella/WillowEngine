// Render.h
#pragma once

#include "config.h"

namespace Render
{
	typedef unsigned int BufferID;
	typedef unsigned int GValue;

	namespace API
	{
		enum API
		{
			API_NULL,
			API_OPENGL
		};
	}

	// Sets up the defaults for the renderer
	RENDER_API void InitRenderer(API::API API);

	// Clear the screen for a new image
	RENDER_API void clearBuffer();
}