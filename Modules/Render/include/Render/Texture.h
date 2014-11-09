// Texture.h
#pragma once

#include <Utility\String.h>
#include <Utility\ResourcePtr.h>
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
		Texture(const Texture& copy) = delete;
		Texture(Texture&& other) = delete;
		~Texture() override;

		///////////////////
		///   Methods   ///
	public:

		BufferID GetID() const;

		/////////////////////
		///   Operators   ///
	public:

		Texture& operator=(const Texture& copy) = delete;
		Texture& operator=(Texture&& other) = delete;

		////////////////
		///   Data   ///
	private:

		BufferID _id;
	};

	NON_REFLECTABLE(Willow::Texture)
}