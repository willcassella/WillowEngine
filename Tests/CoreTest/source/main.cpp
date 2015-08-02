// main.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Core/Core.h>

int main()
{
	for (auto type : Application::GetAllTypes())
	{
		Console::WriteLine(type);
	}
	Console::WriteLine("Hello");
	Console::Prompt();
}
