// Shader.h
#pragma once

#include <Utility\String.h>
#include <Resource\ResourcePtr.h>
#include "Render.h"

namespace Willow
{
	class RENDER_API Shader : public Resource
	{
		///////////////////////
		///   Information   ///
	public:

		typedef Resource Super;

		////////////////////////
		///   Constructors   ///
	public:

		Shader(const String& path);
		~Shader();
		// @TODO: Implement move constructor, move destructor, and copy constructor

		/////////////////////
		///   Operators   ///
	public:

		operator BufferID() const;

		////////////////
		///   Data   ///
	private:

		BufferID _id;
	};
}