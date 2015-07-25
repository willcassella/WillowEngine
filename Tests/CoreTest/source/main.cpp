// main.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Core/Core.h>
#include <Core/Containers/StaticBuffer.h>
#include <Math/Vec3.h>

int main()
{
	Console::WriteLine(test);

	test.DeleteAll("Oh");

	Console::WriteLine(test);

	Console::Prompt();
}