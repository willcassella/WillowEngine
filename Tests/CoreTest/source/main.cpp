// main.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Core/Core.h>
#include <Math/Vec3.h>

int main()
{
	Vec3 test(1, 2, 3);

	Console::WriteLine("'test' has type '@', with value '@'", test.GetType(), test);
	String input = Console::Prompt("Enter a new vector for 'test'");
	
	String::Parse(input, "<@, @, @>", test.X, test.Y, test.Z);

	Console::WriteLine("'test' now has value '@'", test);
	
	Console::Prompt();
}