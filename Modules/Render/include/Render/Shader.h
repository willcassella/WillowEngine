// Shader.h
#pragma once

#include <Utility\ResourcePtr.h>
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
		Shader(const Shader& copy) = delete;
		Shader(Shader&& other) = delete;
		~Shader() override;

		///////////////////
		///   Methods   ///
	public:

		BufferID GetID() const;

		/////////////////////
		///   Operators   ///
	public:

		Shader& operator=(const Shader& copy) = delete;
		Shader& operator=(Shader&& other) = delete;

		////////////////
		///   Data   ///
	private:

		BufferID _id;
	};

	NON_REFLECTABLE(Willow::Shader)
}