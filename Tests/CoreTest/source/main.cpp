// main.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Core/Core.h>
#include <Core/Math/Vec4.h>
#include <Core/Containers/Nullable.h>
#include <Core/Containers/Union.h>
#include <Core/Test/Test.h>

void FormatTest(WTest::Context& context)
{
	String test = Format("UniquePtr<@>{ <@, @, @> }", TypeOf<Vec3>().GetName(), 1.f, 2.5f, 3.5f);
	String fTest = fFormat("UniquePtr<@>{ <@, @, @> }", TypeOf<Vec3>().GetName(), 1.f, 2.5f, 3.5f);

	context.AssertEquals(test, fTest);
}

void StringTest(WTest::Context& context)
{
	String test = "Hello";
	context.AssertEquals("hello", test.ToLower());
	context.AssertEquals("HELLO", test.ToUpper());
}

void NullableTest(WTest::Context& context)
{
	auto func = [](auto) {};

	String receptor;
	Nullable<String> test;
	context.AssertFalse(test.HasValue());
	context.AssertFalse(test.Invoke(func));
	context.AssertFalse(test.GetValue(receptor));
	context.AssertEquals("", receptor);

	test = "Hello, world";
	context.AssertTrue(test.HasValue());
	context.AssertTrue(test.Invoke(func));
	context.AssertTrue(test.GetValue(receptor));
	context.AssertEquals("Hello, world", receptor);
}

void UnionTest(WTest::Context& context)
{
	Union<int32, Scalar, String> test = 3;
	context.AssertTrue(test.HasValue());
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
