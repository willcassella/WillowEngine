// GLMaterial.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Core/IO/Console.h>
#include "glew.h"
#include "../include/GLRender/GLMaterial.h"
#include "../include/GLRender/GLRenderSystem.h"

namespace Willow
{
	////////////////////////
	///   Constructors   ///

	GLMaterial::GLMaterial(GLRenderSystem& renderer, const Material& mat)
		: GLPrimitive(renderer), _params(mat.DefaultParams)
	{
		_id = glCreateProgram();

		BufferID vShader = GetRenderer().FindShader(*mat.VertexShader).GetID();
		BufferID fShader = GetRenderer().FindShader(*mat.FragmentShader).GetID();

		glAttachShader(_id, vShader);
		glAttachShader(_id, fShader);
		glBindAttribLocation(_id, 0, "vPosition");
		glBindAttribLocation(_id, 1, "vTexCoord");
		glBindAttribLocation(_id, 2, "vNormal");
		glLinkProgram(_id);

		// Make sure program successfully linked
		GLint linked;
		glGetProgramiv(_id, GL_LINK_STATUS, &linked);
		if (!linked)
		{
			GLsizei length;
			glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &length);

			GLchar* log = new GLchar[length + 1];
			glGetProgramInfoLog(_id, length, &length, log);
			Console::WriteLine("Material compilation failed: \"@\"", log);
			delete[] log;
		}

		_model = glGetUniformLocation(_id, "model");
		_view = glGetUniformLocation(_id, "view");
		_projection = glGetUniformLocation(_id, "projection");

		glDetachShader(_id, vShader);
		glDetachShader(_id, fShader);
	}

	GLMaterial::GLMaterial(GLMaterial&& move)
		: GLPrimitive(move.GetRenderer()), _params(std::move(move._params))
	{
		_id = move._id;
		_model = move._model;
		_view = move._view;
		_projection = move._projection;

		move._id = 0;
	}

	GLMaterial::~GLMaterial()
	{
		glDeleteProgram(_id);
	}

	///////////////////
	///   Methods   ///

	void GLMaterial::Bind(const Table<String, Material::Param>& instanceParams)
	{
		uint32 texIndex = 0;
		glUseProgram(_id);
		UploadParams(_params, texIndex);
		UploadParams(instanceParams, texIndex);
	}

	void GLMaterial::UploadParams(const Table<String, Material::Param>& params, uint32& texIndex)
	{
		for (const auto& param : params)
		{
			// Handles parameter binding in a generic way
			auto bindHandler = [&](const auto& value)
			{
				using T = std::decay_t<decltype(value)>;

				// Get param location
				auto location = glGetUniformLocation(_id, param.First.Cstr());

				// Handle texture case
				if (std::is_same<AssetPtr<Texture>, T>::value)
				{
					const auto& texValue = reinterpret_cast<const AssetPtr<Texture>&>(value);

					// Set active texture, and upload
					glActiveTexture(GL_TEXTURE0 + texIndex);
					glBindTexture(GL_TEXTURE_2D, this->GetRenderer().FindTexture(*texValue).GetID());
					glUniform1i(location, texIndex);
					++texIndex;
				}

				// Upload the parameter
				this->UploadParam(location, value);
			};

			param.Second.Invoke(bindHandler);
		}
	}

	void GLMaterial::UploadParam(int32 location, float value) const
	{
		glUniform1f(location, value);
	}

	void GLMaterial::UploadParam(int32 location, Vec2 value) const
	{
		glUniform1fv(location, 2, (const GLfloat*)&value);
	}

	void GLMaterial::UploadParam(int32 location, Vec3 value) const
	{
		glUniform1fv(location, 3, (const GLfloat*)&value);
	}

	void GLMaterial::UploadParam(int32 location, Vec4 value) const
	{
		glUniform1fv(location, 4, (const GLfloat*)&value);
	}

	void GLMaterial::UploadParam(int32 /*location*/, const AssetPtr<Texture>& /*value*/)
	{
		// Do nothing, uploading performed in bind handler
	}
}
