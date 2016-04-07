// Material.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Containers/Union.h>
#include <Core/Math/Vec4.h>
#include <Resource/AssetPtr.h>
#include "Texture.h"
#include "Shader.h"

namespace Willow
{
	class ENGINE_API Material final : public Asset
	{
		///////////////////////
		///   Inner Types   ///
	public:

		/** A material parameter may either be a Scalars, Vec2, Vec3, Vec4, or texture. */
		using Param = Union<Scalar, Vec2, Vec3, Vec4, AssetPtr<Texture>>;
		
		/** A table mapping parameter names to parameter values. */
		using ParamTable = Table<String, Param>;

		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Asset)

		////////////////////////
		///   Constructors   ///
	public:

		Material(const Path& path);

		//////////////////
		///   Fields   ///
	public:

		/** The vertex shader for this Material. */
		AssetPtr<Shader> VertexShader;

		/** The fragment shader for this Material. */
		AssetPtr<Shader> FragmentShader;

		/** The default parameters for this material. */
		ParamTable DefaultParams;
	};
}
