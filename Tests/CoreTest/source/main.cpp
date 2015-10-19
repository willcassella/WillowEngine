// main.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Core/Core.h>
#include <Core/Math/Vec4.h>
#include <Core/Containers/Union.h>

void FormatTest()
{
	String test = Format("UniquePtr<@>{ <@, @, @> }", TypeOf<Vec3>().GetName(), 1.f, 2.5f, 3.5f);
	String fTest = fFormat("UniquePtr<@>{ <@, @, @> }", TypeOf<Vec3>().GetName(), 1.f, 2.5f, 3.5f);

	Console::WriteLine(test);
	Console::WriteLine(fTest);
}

int main()
{
	Application::Initialize();

	auto printer = [](const auto& v)
	{
		Console::WriteLine(v);
	};

	{
		Union<int, float, String> test;
		test.Set<String>("herro");

		auto test2 = std::move(test);
		
		test2.Invoke(printer);
		
		test.Set(3);

		test.Invoke(printer);

		test.Set(2.5f);

		test.Invoke(printer);

		Console::WriteLine(*test.GetCurrentType());

		Console::Prompt();
	}

	Application::Terminate();
}
