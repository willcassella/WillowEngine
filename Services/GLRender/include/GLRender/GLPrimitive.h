// GLPrimitive.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "config.h"

////////////////////////////////
///   Forward-declarations   ///

/** Defined in 'GLRenderer.h' */
class GLRenderer;

/////////////////
///   Types   ///

/** Indexes an OpenGL buffer. */
using BufferID = uint32;

/** Represents a value returned by an OpenGL function. */
using GLValue = uint32;

/** Represents an OpenGL Integer. */
using GLInteger = int32;

/** Base for OpenGL primitives (shaders, texture, materials, meshes, etc.) */
struct GLRENDER_API GLPrimitive
{
	/////////////////////////
	////   Constructors   ///
public:

	GLPrimitive(GLRenderer& renderer)
		: _renderer(&renderer)
	{
		// All done
	}
	GLPrimitive(const GLPrimitive& copy) = delete;
	GLPrimitive(GLPrimitive&& move) = default;
	~GLPrimitive() = default;

	/////////////////////
	///    Methods    ///
public:

	/** Returns the renderer that this Primitive belongs to. */
	FORCEINLINE GLRenderer& GetRenderer()
	{
		return *_renderer;
	}

	/** Returns the renderer that this Primitive belongs to. */
	FORCEINLINE const GLRenderer& GetRenderer() const
	{
		return *_renderer;
	}

	//////////////////////
	///   Operators    ///
public:

	GLPrimitive& operator=(const GLPrimitive& copy) = delete;
	GLPrimitive& operator=(GLPrimitive&& move) = delete;

	////////////////
	///   Data   ///
private:

	GLRenderer* _renderer;
};
