// Render.h
#pragma once

#include <Utility\config.h>
#include "config.h"

/////////////////
///   Types   ///

typedef uint32 BufferID;
typedef uint32 GValue;

enum class API
{
	Null,
	OpenGL
};

////////////////
///   Data   ///

extern BufferID gBuffer;
extern BufferID depthBuffer;
extern BufferID positionBuffer;
extern BufferID diffuseBuffer;
extern BufferID normalBuffer;
extern BufferID specularBuffer;
extern BufferID metallicBuffer;
extern BufferID roughnessBuffer;

/////////////////////
///   Functions   ///

/** Sets up the defaults for the renderer with the given height and width */
RENDER_API void InitRenderer(uint32 width, uint32 height);

/** Cleans up renderer buffers */
RENDER_API void CleanUpRenderer();

/** Resize the renderer drawing area */
RENDER_API void Resize(uint32 width, uint32 height);

/** Prepare to render a new frame */
RENDER_API void BeginFrame();

/** Complete rendering a frame */
RENDER_API void EndFrame();