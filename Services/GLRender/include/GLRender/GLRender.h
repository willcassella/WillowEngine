// GLRender.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Math/Vec3.h>
#include "config.h"

/////////////////
///   Types   ///

typedef uint32 BufferID;
typedef uint32 GValue;

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
GLRENDER_API void InitRenderer(uint32 width, uint32 height);

/** Cleans up renderer buffers */
GLRENDER_API void CleanUpRenderer();

/** Resize the renderer drawing area */
GLRENDER_API void Resize(uint32 width, uint32 height);

/** Prepare to render a new frame */
GLRENDER_API void BeginFrame();

/** Complete rendering a frame */
GLRENDER_API void EndFrame(const Vec3& camPos);