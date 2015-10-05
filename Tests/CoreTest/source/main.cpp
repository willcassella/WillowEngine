// main.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Core/Core.h>
#include <Core/Math/Vec4.h>
#include <Core/Math/Quat.h>	

int main()
{
	Application::Initialize();

	String test = Format("UniquePtr<@>{ <@, @, @> }", TypeOf<Vec3>().GetName(), 1.f, 2.5f, 3.5f);
        String fTest = fFormat("UniquePtr<@>{ <@, @, @> }", TypeOf<Vec3>().GetName(), 1.f, 2.5f, 3.5f);
        
        Console::WriteLine(test);
        Console::WriteLine(fTest);
}
