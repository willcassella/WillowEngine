// Shader.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Resource/Asset.h>
#include "../config.h"

namespace Willow
{
	class ENGINE_API Shader final : public Asset
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Asset)

		////////////////////////
		///   Constructors   ///
	public:

		Shader(const Path& path);

		///////////////////
		///   Methods   ///
	public:

		/** Returns the source code for this Shader. */
		FORCEINLINE const String& GetSource() const
		{
			return _source;
		}

		////////////////
		///   Data   ///
	private:

		String _source;
	};
}
