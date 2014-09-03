// Texture.h
#pragma once

#include <Utility\String.h>
#include "Render.h"

namespace Render
{
	class RENDER_API Texture
	{
		////////////////////////
		///   Constructors   ///
	public:

		Texture(const Willow::String& path);
		~Texture();

		// @TODO: Impliment rule of five

		///////////////////
		///   Methods   ///
	public:

		BufferID getID() const;

		////////////////
		///   Data   ///
	private:

		BufferID id;
	};
}