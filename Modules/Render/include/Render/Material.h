// Material.h
#pragma once

#include "Shader.h"
#include "Texture.h"

namespace Willow
{
	// @TODO: Implement Resource
	class RENDER_API Material
	{
		//////////////////
		///   Fields   ///
	public:

		ResourcePtr<Shader> VertexShader;
		ResourcePtr<Shader> FragmentShader;
		// @TODO: Replace with List<ResourcePtr<Texture>>
		ResourcePtr<Texture> Textures;

		////////////////////////
		///   Constructors   ///
	public:

		Material();
		~Material();
		// @TODO: implement rule of five

		///////////////////
		///   Methods   ///
	public:

		// @TODO: This needs work
		void Compile();
		BufferID GetModelID() const;
		BufferID GetViewID() const;
		BufferID GetProjectionID() const;

		/////////////////////
		///   Operators   ///
	public:

		operator BufferID() const;

		////////////////
		///   Data   ///
	private:

		BufferID _id;
		BufferID _vModel;
		BufferID _vView;
		BufferID _vProjection;
	};
}