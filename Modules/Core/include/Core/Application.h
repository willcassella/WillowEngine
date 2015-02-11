// Application.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "String.h"
#include "Reflection/Reflection.h"

struct CORE_API Application final
{
	///////////////////////
	///   Information   ///
public:

	friend TypeInfo;

	////////////////////////
	///   Constructors   ///
private:

	Application() = default;

	///////////////////
	///   Methods   ///
public:

	// @TODO: Documentation
	static Application& Instance();

	const Array<const TypeInfo*>& Types() const;

	////////////////
	///   Data   ///
private:

	Array<const TypeInfo*> _types;
};