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

	REFLECTABLE_CLASS
	EXTENDS(Object)
	friend TypeInfo;

	////////////////////////
	///   Constructors   ///
public:

	Application(const Application& copy) = delete;
	Application(Application&& move) = delete;

private:

	Application() = default;

	///////////////////
	///   Methods   ///
public:

	static const Array<const TypeInfo*>& GetAllTypes();

	static const TypeInfo* FindType(const String& name);

private:

	static Application& Instance();

	/////////////////////
	///   Operators   ///
public:

	Application& operator=(const Application& copy) = delete;
	Application& operator=(Application&& move) = delete;

	////////////////
	///   Data   ///
private:

	// TODO: Make this Array<TypeIndex>?
	Array<const TypeInfo*> _types;
};