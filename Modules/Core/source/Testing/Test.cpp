// Testing.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Core/Testing/Test.h"
#include "../../include/Core/Operations/ToString.h"

/////////////////////
///   Functions   ///

void WTest::RunTest(Test test, CString name)
{
	Console::WriteLine("Begin '@':", name);
	Console::WriteLine("-----");
	test();
	Console::WriteLine("-----");
	Console::WriteLine("End '@'", name);
	Console::NewLine();
}
