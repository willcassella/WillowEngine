// GLPrimitive.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/env.h>

namespace willow
{
	/////////////////
	///   Types   ///

	/** Defined in 'GLRenderSystem.h' */
	class GLRenderSystem;

	/** Defined in 'GLTexture.h' */
	struct GLTexture;

	/** Defined in 'GLShader.h' */
	struct GLShader;

	/** Defined in 'GLMaterial.h' */
	struct GLMaterial;
	
	/** Defined in 'GLStaticMesh.h' */
	struct GLStaticMesh;

	/** Indexes an OpenGL buffer. */
	using BufferID = uint32;

	/** Represents a value returned by an OpenGL function. */
	using GLValue = uint32;

	/** Represents an OpenGL Integer. */
	using GLInteger = int32;
}
