// Shader.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Resource/Asset.h>
#include <Resource/Resources/TextFile.h>
#include "../config.h"

class ENGINE_API Shader final : public Asset
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_ASSET
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
