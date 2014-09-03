// StaticMesh.h
#pragma once

#include <vector>
#include <Utility\String.h>
#include <Utility\Math\Mat4.h>
#include "Material.h"
#include "Vertex.h"

namespace Render
{
	typedef std::vector<Vertex> VertexArray;
	typedef std::vector<BufferID> ElementArray;

	class RENDER_API StaticMesh
	{
		////////////////////////
		///   Constructors   ///
	public:

		StaticMesh(const Willow::String& path);
		~StaticMesh();

		// @TODO: impliment rule of five

		///////////////////
		///   Methods   ///
	public:

		// Render the mesh at a specific orienation, view, and perspective
		void render(const Math::Mat4& orientation, const Math::Mat4& view, const Math::Mat4& perspective) const;
		std::size_t getNumElements() const;
		Material& getMaterial() const;
		void setMaterial(Material& _material);

		// This should be refactored in the future
		static bool loadBinaryModel(const Willow::String& path, std::vector<Vertex>* out_vertices, std::vector<BufferID>* out_elements);

		////////////////
		///   Data   ///
	private:

		BufferID vao;
		BufferID vbo;
		BufferID ebo;

		VertexArray vertices;
		ElementArray elements;

		Material* mat;
	};
}