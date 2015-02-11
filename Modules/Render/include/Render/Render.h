// Render.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "config.h"

/////////////////
///   Types   ///

typedef uint32 BufferID;
typedef uint32 GValue;

/////////////////////
///   Functions   ///

/** Sets up the renderer */
RENDER_API void SetupRenderer();

/** Clear the screen for a new image */
RENDER_API void ClearScreen();

/** Render a frame */
//RENDER_API void Draw();