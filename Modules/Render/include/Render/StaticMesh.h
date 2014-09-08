// StaticMesh.h
#pragma once

#include <Utility\String.h>
#include <Utility\Array.h>
#include <Utility\Math\Mat4.h>
#include "Material.h"
#include "Vertex.h"

namespace Render
{
	template class RENDER_API Willow::Array < Vertex >;
	template class RENDER_API Willow::Array < BufferID >;

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
		uint getNumElements() const;
		Material& getMaterial() const;
		void setMaterial(Material& _material);

		// This should be refactored in the future
		static bool loadBinaryModel(const Willow::String& path, Willow::Array<Vertex>* out_vertices, Willow::Array<BufferID>* out_elements);

		////////////////
		///   Data   ///
	private:

		BufferID vao;
		BufferID vbo;
		BufferID ebo;

		Willow::Array<Vertex> vertices;
		Willow::Array<BufferID> elements;

		Material* mat;
	};
}