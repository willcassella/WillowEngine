// Shader.h
#pragma once

#include <Utility\String.h>
#include "Render.h"

namespace Render
{
	namespace ShaderType
	{
		enum ShaderType
		{
			VERTEX_SHADER, FRAGMENT_SHADER, GEOMERTY_SHADER
		};
	}

	class RENDER_API Shader
	{
		////////////////////////
		///   Constructors   ///
	public:

		Shader(const Willow::String& _source, ShaderType::ShaderType type);
		~Shader();

		// @TODO: Impliment move constructor, move destructor, and copy constructor

		///////////////////
		///   Methods   ///
	public:

		// @TODO: Reimpliment as a cast operator?
		BufferID getID() const;

		//////////////////////////
		///   Static Members   ///
	public:

		static const Willow::String basic_vert_source;
		static const Willow::String basic_frag_source;

		////////////////
		///   Data   ///
	private:

		BufferID id;
		Willow::String source;
	};
}