// StaticMesh.h
#pragma once

#include <Utility\String.h>
#include <Utility\Math\Mat4.h>
#include "Material.h"
#include "Vertex.h"

namespace Willow
{
	template class RENDER_API Array<Vertex>;
	template class RENDER_API Array<BufferID>;

	class RENDER_API StaticMesh : public Resource
	{
		///////////////////////
		///   Information   ///
	public:

		typedef Resource Super;

		////////////////////////
		///   Constructors   ///
	public:

		StaticMesh(const String& path);
		~StaticMesh() override;
		// @TODO: implement rule of five

		///////////////////
		///   Methods   ///
	public:

		// Render the mesh at a specific orientation, view, and perspective
		void Render(const Mat4& orientation, const Mat4& view, const Mat4& perspective) const;
		size_t GetNumElements() const;
		Material& GetMaterial() const;
		void SetMaterial(Material& material);

		////////////////
		///   Data   ///
	private:

		BufferID _vao;
		BufferID _vbo;
		BufferID _ebo;

		Array<Vertex> _vertices;
		Array<BufferID> _elements;

		// @TODO: replace with ResourcePtr<Material>
		Material* _mat;
	};

	template class RENDER_API ResourcePtr<StaticMesh>;
}