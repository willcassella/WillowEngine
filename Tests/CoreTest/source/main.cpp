// main.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Core/Core.h>
#include <Math/Vec3.h>

int main()
{
	TypeIndex b = TypeOf<const float* const*>();

	for (TypeIndex type : Application::Instance().Types())
	{
		Console::WriteLine(type.ToString());
	}

	Console::Prompt(String());
}