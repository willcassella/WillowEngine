// Testing.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <chrono>
#include "../../include/Core/IO/Console.h"
#include "../../include/Core/Test/Test.h"
#include "../../include/Core/Operations/ToString.h"

/////////////////
///   Types   ///

struct AssertionFailedException final
{
	////////////////////////
	///   Constructors   ///
public:

	AssertionFailedException(String message)
		: Message(std::move(message))
	{
		// All done
	}

	//////////////////
	///   Fields   ///
public:

	const String Message;

	///////////////////
	///   Methods   ///
public:

	const String& ToString() const
	{
		return Message;
	}
};

///////////////////
///   Methods   ///

void WTest::Context::AssertionFailure(CString assertion, const String& expected, const String& result)
{
	_endTime = std::chrono::system_clock::now();
	throw AssertionFailedException(Format("Assertion \"@\" failed. Expected \"@', got \"@\"", assertion, expected, result));
}

/////////////////////
///   Functions   ///

void WTest::RunTest(Test test, CString name)
{
	// Create start and end time objects
	Context::TimePoint startTime;
	Context::TimePoint endTime;
	
	try
	{
		// Creat context and start timer
		Context context(endTime);
		startTime = std::chrono::system_clock::now();

		// Run the test!
		test(context);

		// Test returned successfully, record end time
		endTime = std::chrono::system_clock::now();
	}
	catch (const AssertionFailedException& failure)
	{
		Console::WriteLine("Test \"@\" failed in @ microseconds: @", name, (endTime - startTime).count(), failure);
		return;
	}

	Console::WriteLine("Test \"@\" completed successfully in @ microseconds", name, (endTime - startTime).count());
}
