// Texture.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Resource/Image.h>
#include "Render.h"

class RENDER_API Texture : public Image
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(Image);

	////////////////////////
	///   Constructors   ///
public:

	Texture(const String& path);
	Texture(const Texture& copy) = delete;
	Texture(Texture&& move) = delete;
	~Texture() override;

	///////////////////
	///   Methods   ///
public:

	BufferID GetID() const;

	/////////////////////
	///   Operators   ///
public:

	Texture& operator=(const Texture& copy) = delete;
	Texture& operator=(Texture&& move) = delete;

	////////////////
	///   Data   ///
private:

	BufferID _id;
};