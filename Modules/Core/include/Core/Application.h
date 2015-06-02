// Application.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Containers/Array.h"
#include "Object.h"
#include "Reflection/TypeIndex.h"

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

	const Array<TypeIndex>& Types() const;

	////////////////
	///   Data   ///
private:

	Array<TypeIndex> _types;
};