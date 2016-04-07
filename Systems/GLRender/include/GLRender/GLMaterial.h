// GLMaterial.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Assets/Material.h>
#include "GLShader.h"
#include "GLTexture.h"

namespace Willow
{
	struct GLRENDER_API GLMaterial final : GLPrimitive
	{
		////////////////////////
		///   Constructors   ///
	public:

		/** Constructs an OpenGL material from the given Material asset. */
		GLMaterial(GLRenderSystem& renderer, const Material& mat);

		GLMaterial(GLMaterial&& move);
		~GLMaterial();

		///////////////////
		///   Methods   ///
	public:

		/** Returns the ID of this Material. */
		FORCEINLINE BufferID GetID() const
		{
			return _id;
		}

		/** Sets this material as the current active material, with the given instance parameters. */
		void Bind(const Table<String, Material::Param>& instanceParams);

	private:

		/** Uploads the given parameters to this material. */
		void UploadParams(const Table<String, Material::Param>& params, uint32& texIndex);

		/** Uploads a scalar parameter to the given location. */
		void UploadParam(int32 location, float value) const;

		/** Uploads a Vec2 parameter to the given location. */
		void UploadParam(int32 location, Vec2 value) const;

		/** Uploads a Vec3 parameter to the given location. */
		void UploadParam(int32 location, Vec3 value) const;

		/** Uploads a Vec4 location to the given location. */
		void UploadParam(int32 location, Vec4 value) const;

		/** Uploads a texture parameter to the given location. */
		void UploadParam(int32 location, const AssetPtr<Texture>& value);

		////////////////
		///   Data   ///
	private:

		Table<String, Material::Param> _params;
		BufferID _id;
		BufferID _model;
		BufferID _view;
		BufferID _projection;
	};
}
