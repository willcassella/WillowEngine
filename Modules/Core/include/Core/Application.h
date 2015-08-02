// Application.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Containers/Array.h"
#include "Object.h"
#include "Reflection/TypePtr.h"

class CORE_API Application final : public Object
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(Object)
	friend TypeInfo;
	
private:

	Application() = default;

	///////////////////
	///   Methods   ///
public:

	static const Array<TypePtr<TypeInfo>>& GetAllTypes();

	static const TypeInfo* FindType(const String& name);

private:

	static Application& Instance();

	////////////////
	///   Data   ///
private:

	Array<TypePtr<TypeInfo>> _types;
};