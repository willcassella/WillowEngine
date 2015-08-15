// Application.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Containers/Array.h"
#include "Object.h"
#include "Reflection/TypePtr.h"

struct CORE_API Application final
{
	///////////////////////
	///   Information   ///
public:

	friend TypeInfo;
	
private:

	Application() = default;

	///////////////////
	///   Methods   ///
public:

	static const Array<const TypeInfo*>& GetAllTypes();

	static const TypeInfo* FindType(const String& name);

private:

	static Application& Instance();

	////////////////
	///   Data   ///
private:

	Array<const TypeInfo*> _types;
};