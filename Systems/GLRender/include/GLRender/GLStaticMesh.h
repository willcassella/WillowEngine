// GLStaticMesh.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Assets/StaticMesh.h>
#include "GLPrimitive.h"

namespace Willow
{
	struct GLRENDER_API GLStaticMesh final : GLPrimitive
	{
		////////////////////////
		///   Constructors   ///
	public:

		/** Uploads the given Mesh asset to the GPU. */
		GLStaticMesh(GLRenderSystem& renderer, const StaticMesh& mesh);

		GLStaticMesh(GLStaticMesh&& move);
		~GLStaticMesh();

		///////////////////
		///   Methods   ///
	public:

		void Bind() const;

		/** Returns the ID of the Vertex Array Object for this StaticMesh. */
		FORCEINLINE BufferID GetVao() const
		{
			return _vao;
		}

		/** Returns the Vertex Buffer Object for this StaticMesh. */
		FORCEINLINE BufferID GetVBO() const
		{
			return _vbo;
		}

		/** Returns the number of vertices in this Mesh. */
		FORCEINLINE GLInteger GetNumVertices() const
		{
			return _numVertices;
		}

		////////////////
		///   Data   ///
	private:

		BufferID _vao;
		BufferID _vbo;
		GLInteger _numVertices;
	};
}
