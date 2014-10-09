// StaticMesh.h
#pragma once

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
		StaticMesh(const StaticMesh& copy) = delete;
		StaticMesh(StaticMesh&& other) = delete;
		~StaticMesh() override;

		///////////////////
		///   Methods   ///
	public:

		/** Render the mesh at a specific orientation, view, and perspective */
		void Render(const Mat4& orientation, const Mat4& view, const Mat4& perspective) const;
		Material& GetMaterial();
		const Material& GetMaterial() const;
		void SetMaterial(const String& path);

		/////////////////////
		///   Operators   ///
	public:

		StaticMesh& operator=(const StaticMesh& copy) = delete;
		StaticMesh& operator=(StaticMesh&& other) = delete;

		////////////////
		///   Data   ///
	private:

		BufferID _vao;
		BufferID _vbo;
		BufferID _ebo;
		uint32 _numElements;
		ResourcePtr<Material> _mat;
	};
}