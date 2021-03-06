// GLStaticMesh.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Resources/StaticMesh.h>
#include "Forwards.h"
#include "config.h"

namespace willow
{
	struct GLRENDER_API GLStaticMesh final
	{
		////////////////////////
		///   Constructors   ///
	public:

		/** Uploads the given Mesh asset to the GPU. */
		GLStaticMesh(const StaticMesh& mesh);

		GLStaticMesh(GLStaticMesh&& move);
		~GLStaticMesh();

		///////////////////
		///   Methods   ///
	public:

		void bind() const;

		/** Returns the ID of the Vertex Array Object for this StaticMesh. */
		FORCEINLINE BufferID get_vao() const
		{
			return this->_vao;
		}

		/** Returns the Vertex Buffer Object for this StaticMesh. */
		FORCEINLINE BufferID get_vbo() const
		{
			return this->_vbo;
		}

		/** Returns the number of vertices in this Mesh. */
		FORCEINLINE GLInteger get_num_vertices() const
		{
			return this->_numVertices;
		}

		////////////////
		///   Data   ///
	private:

		BufferID _vao;
		BufferID _vbo;
		GLInteger _numVertices;
	};
}
