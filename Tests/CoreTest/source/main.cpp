// main.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Core/Core.h>
#include <Core/Math/Vec4.h>

int main()
{
	Application::Initialize();

	Vec3 test(1, 2, 3);

	auto y = test.GetType().FindData("Y")->Get(Variant{ test }).ToString();
	Console::Prompt(y);
}
