// Application.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Core/Application.h"
#include "../include/Core/Reflection/ClassInfo.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(Application);

///////////////////
///   Methods   ///

Application& Application::Instance()
{
	static Application app;
	return app;
}

const Array<TypeIndex>& Application::Types() const
{
	return _types;
}