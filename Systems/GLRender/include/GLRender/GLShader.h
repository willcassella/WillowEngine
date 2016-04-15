// GLShader.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Resources/Shader.h>
#include "Forwards.h"
#include "config.h"

namespace willow
{
	struct GLRENDER_API GLShader final
	{
		////////////////////////
		///   Constructors   ///
	public:

		/** Constructs a GLShader corresponding to a Shader asset. */
		GLShader(const Shader& shader);

		/** Constructs a GLShader using a file */
		GLShader(const Path& path);

		GLShader(GLShader&& move);
		~GLShader();

		///////////////////
		///   Methods   ///
	public:

		FORCEINLINE BufferID get_id() const
		{
			return this->_id;
		}

		////////////////
		///   Data   ///
	private:

		BufferID _id;
	};
}
