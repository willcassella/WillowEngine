// Material.h
#pragma once

#include <Utility\Table.h>
#include <Utility\Math\Mat4.h>
#include "Shader.h"
#include "Texture.h"

namespace Willow
{
	// @TODO: Implement Resource (?)
	class RENDER_API Material
	{
		//////////////////
		///   Fields   ///
	public:

		ResourcePtr<Shader> VertexShader;
		ResourcePtr<Shader> FragmentShader;
		Table<String, ResourcePtr<Texture>> Textures;

		////////////////////////
		///   Constructors   ///
	public:

		Material();
		~Material();
		// @TODO: Implement rule of 5

		///////////////////
		///   Methods   ///
	public:

		// @TODO: This needs some serious work. Once I have a more finalized rendering pipeline set up I'll do some major refactoring here
		void Compile();
		void Bind() const;
		void UploadModelMatrix(const Mat4& matrix);
		void UploadViewMatrix(const Mat4& matrix);
		void UploadProjectionMatrix(const Mat4& matrix);

		/////////////////////
		///   Operators   ///
	public:

		// @TODO: I think I'll replace this with a method after all
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