// Texture.h
#pragma once

#include <Utility\String.h>
#include <Resource\ResourcePtr.h>
#include "Render.h"

namespace Willow
{
	class RENDER_API Texture : public Resource
	{
		///////////////////////
		///   Information   ///
	public:

		typedef Resource Super;

		////////////////////////
		///   Constructors   ///
	public:

		Texture(const String& path);
		~Texture() override;

		// @TODO: Implement rule of five

		///////////////////
		///   Methods   ///
	public:

		BufferID GetID() const;

		////////////////
		///   Data   ///
	private:

		BufferID _id;
	};

	template class RENDER_API ResourcePtr<Texture>;
}