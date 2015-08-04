// Texture.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Resource/Asset.h>
#include <Resource/Resources/Image.h>
#include "../config.h"

class ENGINE_API Texture final : public Asset
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_ASSET
	EXTENDS(Asset)

	////////////////////////
	///   Constructors   ///
public:

	Texture(const Image& image);

	///////////////////
	///   Methods   ///
public:

	void OnReload() override;
};
