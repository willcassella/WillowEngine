// Material.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Resource/AssetPtr.h>
#include <Resource/Resources/TextFile.h>
#include "Texture.h"
#include "Shader.h"

class ENGINE_API Material final : public Asset
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_ASSET
	EXTENDS(Asset)

	////////////////////////
	///   Constructors   ///
public:

	Material(const TextFile& file);
	
	//////////////////
	///   Fields   ///
public:

	AssetPtr<Shader> VertexShader;

	AssetPtr<Shader> FragmentShader;

	Table<String, AssetPtr<Texture>> Textures;

	///////////////////
	///   Methods   ///
public:

	void OnReload() override;
};
