// Material.h
#pragma once

#include <Utility\Table.h>
#include <Utility\Math\Mat4.h>
#include "Shader.h"
#include "Texture.h"

namespace Willow
{
	class RENDER_API Material : public Resource
	{
		///////////////////////
		///   Information   ///
	public:

		typedef Resource Super;

		//////////////////
		///   Fields   ///
	public:

		ResourcePtr<Shader> VertexShader;
		ResourcePtr<Shader> FragmentShader;
		Table<String, ResourcePtr<Texture>> Textures;

		////////////////////////
		///   Constructors   ///
	public:

		Material(const String& path);
		Material(const Material& copy) = delete;
		Material(Material&& other) = delete;
		~Material() override;

		///////////////////
		///   Methods   ///
	public:

		// @TODO: This needs some serious work. Once I have a more finalized rendering pipeline set up I'll do some major refactoring here
		void Compile();
		void Bind() const;
		BufferID GetID() const;
		void UploadModelMatrix(const Mat4& matrix) const;
		void UploadViewMatrix(const Mat4& matrix) const;
		void UploadProjectionMatrix(const Mat4& matrix) const;

		/////////////////////
		///   Operators   ///
	public:

		Material& operator=(const Material& rhs) = delete;
		Material& operator=(Material&& copy) = delete;

		////////////////
		///   Data   ///
	private:

		BufferID _id;
		BufferID _model;
		BufferID _view;
		BufferID _projection;
	};

	NON_REFLECTABLE(Willow::Material)
}