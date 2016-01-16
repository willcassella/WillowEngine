// Testing.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Core/IO/Console.h"
#include "../../include/Core/Test/Test.h"
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
