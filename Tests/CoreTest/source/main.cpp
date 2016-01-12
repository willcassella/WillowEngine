// main.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Core/Core.h>
#include <Core/Math/Vec4.h>
#include <Core/Containers/Nullable.h>
#include <Core/Containers/Union.h>
#include <Core/Testing/Test.h>

void FormatTest()
{
	String test = Format("UniquePtr<@>{ <@, @, @> }", TypeOf<Vec3>().GetName(), 1.f, 2.5f, 3.5f);
	String fTest = fFormat("UniquePtr<@>{ <@, @, @> }", TypeOf<Vec3>().GetName(), 1.f, 2.5f, 3.5f);

	Console::WriteLine(test);
	Console::WriteLine(fTest);
}

void StringTest()
{
	String test = "Hello";
	Console::WriteLine(test);
	test = test.ToUpper();
	Console::WriteLine(test);
	test = test.ToLower();
	Console::WriteLine(test);
}

void NullableTest()
{
	auto printer = [](String value) { Console::WriteLine(value); };

	Nullable<String> test;
	test = "Hello, world";
	test.Invoke(printer);

	Nullable<String>{"Test"}.Invoke(printer);
}

void UnionTest()
{
	Union<int32, Scalar, String> test = 3;
	test.Invoke([](auto v) { Console::WriteLine(v); });
}

int main()
{
	Application::Initialize();	

	RUN_TEST(FormatTest);
	RUN_TEST(StringTest);
	RUN_TEST(NullableTest);
	RUN_TEST(UnionTest);

	Console::Prompt();

	Application::Terminate();
}
