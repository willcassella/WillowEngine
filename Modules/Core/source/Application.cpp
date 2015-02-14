// Application.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Core/Application.h"
#include "../include/Core/Reflection/Registration.h"

///////////////////
///   Methods   ///

Application& Application::Instance()
{
	static Application app;
	return app;
}

const Array<const TypeInfo*>& Application::Types() const
{
	return _types;
}