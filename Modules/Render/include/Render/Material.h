// Material.h
#pragma once

#include "Shader.h"
#include "Texture.h"

namespace Render
{
	class RENDER_API Material
	{
		////////////////////////
		///   Constructors   ///
	public:

		Material(Shader& _vertex, Shader& _fragment);
		~Material();

		// @TODO: impliment rule of five

		///////////////////
		///   Methods   ///
	public:

		BufferID getID() const;
		Texture& getTexture() const;
		void setTexture(Texture& _texture);
		BufferID getModelID() const;
		BufferID getViewID() const;
		BufferID getProjectionID() const;

		// @TODO: impliment material duplication

		////////////////
		///   Data   ///
	private:

		BufferID id;
		BufferID vModel;
		BufferID vView;
		BufferID vProjection;

		Texture* texture;
		Shader* vertex;
		Shader* fragment;
	};
}