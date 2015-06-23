// main.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Core/Core.h>
#include <Math/Vec3.h>

void Test(const Array<const TypeInfo*>& types)
{
	// Fuck if I know
}

int main()
{
	Array<const ClassInfo*> test;
	test.Add(&TypeOf<Object>());
	test.Add(&TypeOf<ClassInfo>());
	test.Add(&TypeOf<Event>());

	Test(test);
	
	Console::Prompt();
}