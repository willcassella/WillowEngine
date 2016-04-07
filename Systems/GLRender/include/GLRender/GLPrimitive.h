// GLPrimitive.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "config.h"

namespace Willow
{
	////////////////////////////////
	///   Forward-declarations   ///

	/** Defined in 'GLRenderSystem.h' */
	class GLRenderSystem;

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

		GLPrimitive(GLRenderSystem& renderer)
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
		FORCEINLINE GLRenderSystem& GetRenderer()
		{
			return *_renderer;
		}

		/** Returns the renderer that this Primitive belongs to. */
		FORCEINLINE const GLRenderSystem& GetRenderer() const
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

		GLRenderSystem* _renderer;
	};
}
