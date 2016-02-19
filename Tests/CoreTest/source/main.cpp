// main.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Core/Application.h>
#include <Core/Math/Vec4.h>
#include <Core/Reflection/StructInfo.h>
#include <Core/Functional/EnumeratorView.h>
#include <Core/Containers/Nullable.h>
#include <Core/Containers/Union.h>
#include <Core/Test/Test.h>

void FormatTest(WTest::Context& context)
{
	String test = Format("TestPtr<@>{ <@, @, @> }", TypeOf<Vec3>().GetName(), 1.f, 2.5f, 3.5f);
	String fTest = fFormat("TestPtr<@>{ <@, @, @> }", TypeOf<Vec3>().GetName(), 1.f, 2.5f, 3.5f);

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

void EnumerationViewTest(WTest::Context& context)
{
	auto func = [](EnumeratorView<int> enumerator)
	{
		Array<int> collectionA = { 1, 2, 3, 4 };
		Queue<int> collectionB = { 5, 6, 7, 8 };
		enumerator.Enumerate(collectionA);
		enumerator.Enumerate(collectionB);
	};

	int sum = 0;
	func([&sum](int value) { sum += value; });
	context.AssertEquals(1 + 2 + 3 + 4 + 5 + 6 + 7 + 8, sum);

	sum = 0;
	func([&sum](int value) { sum += value; return sum == 6 ? EnumeratorResult::Break : EnumeratorResult::Continue; });
	context.AssertEquals(6, sum);
}

////////////////////////
///   Static Tests   ///

namespace TypeTraitsTest
{
#	define COPY_CONST_ERROR "'stde::copy_const' does not work as intended on this compiler."
	static_assert(std::is_same<int, stde::copy_const_t<int, int>>::value, COPY_CONST_ERROR);
	static_assert(std::is_same<const int, stde::copy_const_t<const int, int>>::value, COPY_CONST_ERROR);
	static_assert(std::is_same<const int, stde::copy_const_t<const int, const int>>::value, COPY_CONST_ERROR);
	static_assert(std::is_same<const int, stde::copy_const_t<const volatile int, int>>::value, COPY_CONST_ERROR);
#	undef COPY_CONST_ERROR

#	define COPY_VOLATILE_ERROR "'stde::copy_volatile' does not work as intended on this compiler."
	static_assert(std::is_same<int, stde::copy_volatile_t<int, int>>::value, COPY_VOLATILE_ERROR);
	static_assert(std::is_same<volatile int, stde::copy_volatile_t<volatile int, int>>::value, COPY_VOLATILE_ERROR);
	static_assert(std::is_same<volatile int, stde::copy_volatile_t<volatile int, volatile int>>::value, COPY_VOLATILE_ERROR);
	static_assert(std::is_same<volatile int, stde::copy_volatile_t<const volatile int, int>>::value, COPY_VOLATILE_ERROR);
#	undef COPY_VOLATILE_ERROR

#	define COPY_VC_ERROR "'stde::copy_cv' does not work as intended on this compiler."
	static_assert(std::is_same<int, stde::copy_cv_t<int, int>>::value, COPY_VC_ERROR);
	static_assert(std::is_same<const int, stde::copy_cv_t<const int, int>>::value, COPY_VC_ERROR);
	static_assert(std::is_same<const int, stde::copy_cv_t<const int, const int>>::value, COPY_VC_ERROR);
	static_assert(std::is_same<volatile int, stde::copy_cv_t<volatile int, int>>::value, COPY_VC_ERROR);
	static_assert(std::is_same<volatile int, stde::copy_cv_t<volatile int, volatile int>>::value, COPY_VC_ERROR);
	static_assert(std::is_same<const volatile int, stde::copy_cv_t<const volatile int, int>>::value, COPY_VC_ERROR);
	static_assert(std::is_same<const volatile int, stde::copy_cv_t<const volatile int, const int>>::value, COPY_VC_ERROR);
	static_assert(std::is_same<const volatile int, stde::copy_cv_t<const volatile int, volatile int>>::value, COPY_VC_ERROR);
	static_assert(std::is_same<const volatile int, stde::copy_cv_t<const volatile int, const volatile int>>::value, COPY_VC_ERROR);
#	undef COPY_VC_ERROR

#	define COPY_REF_ERROR "'stde::copy_ref' does not work as intended on this compiler."
	static_assert(std::is_same<int, stde::copy_ref_t<int, int>>::value, COPY_REF_ERROR);
	static_assert(std::is_same<int&, stde::copy_ref_t<int&, int>>::value, COPY_REF_ERROR);
	static_assert(std::is_same<int&, stde::copy_ref_t<int&, int&>>::value, COPY_REF_ERROR);
	static_assert(std::is_same<int&, stde::copy_ref_t<const int&, int>>::value, COPY_REF_ERROR);
	static_assert(std::is_same<int&&, stde::copy_ref_t<int&&, int>>::value, COPY_REF_ERROR);
	static_assert(std::is_same<int&&, stde::copy_ref_t<int&&, int&&>>::value, COPY_REF_ERROR);
#	undef COPY_REF_ERROR
}

int main()
{
	Application::Initialize();	

	RUN_TEST(FormatTest);
	RUN_TEST(StringTest);
	RUN_TEST(NullableTest);
	RUN_TEST(UnionTest);
	RUN_TEST(EnumerationViewTest);

	Console::Prompt();

	Application::Terminate();
}
