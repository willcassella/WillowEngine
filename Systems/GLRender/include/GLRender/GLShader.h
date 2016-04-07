// GLShader.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Assets/Shader.h>
#include "GLPrimitive.h"

namespace Willow
{
	struct GLRENDER_API GLShader final : GLPrimitive
	{
		////////////////////////
		///   Constructors   ///
	public:

		/** Constructs a GLShader corresponding to a Shader asset. */
		GLShader(GLRenderSystem& renderer, const Shader& shader);

		/** Constructs a GLShader using a file */
		GLShader(GLRenderSystem& renderer, const Path& path);

		GLShader(GLShader&& move);
		~GLShader();

		///////////////////
		///   Methods   ///
	public:

		FORCEINLINE BufferID GetID() const
		{
			return _id;
		}

		////////////////
		///   Data   ///
	private:

		BufferID _id;
	};
}
