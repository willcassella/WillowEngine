// Test.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Console.h"

namespace WTest
{
	/////////////////
	///   Types   ///

	/** Function signature for a Test. */
	using Test = void();

	/////////////////////
	///   Functions   ///

	/** Runs the given test. */
	void CORE_API RunTest(Test test, CString name);
}

//////////////////
///   Macros   ///

/** Runs the given test. */
#define RUN_TEST(T) ::WTest::RunTest(T, #T)
