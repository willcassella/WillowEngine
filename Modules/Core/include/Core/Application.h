// Application.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "String.h"
#include "Object.h"

class CORE_API Application final : public Object
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(Object);
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