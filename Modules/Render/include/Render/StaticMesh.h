// StaticMesh.h
#pragma once

#include <Utility\String.h>
#include <Utility\Math\Mat4.h>
#include "Material.h"

namespace Willow
{
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
		Material& GetMaterial();
		const Material& GetMaterial() const;
		void SetMaterial(Material& material);

		////////////////
		///   Data   ///
	private:

		BufferID _vao;
		BufferID _vbo;
		BufferID _ebo;

		uint32 _numElements;

		// @TODO: replace with ResourcePtr<Material>
		Material* _mat;
	};
}