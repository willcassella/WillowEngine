// main.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Core/Core.h>

class Test : public Object
{
	REFLECTABLE_CLASS
	EXTENDS(Object)

public:
	String Name;
};

BUILD_REFLECTION(Test);

int main()
{

	Ptr<Test> ptr;
	
	{
		OwnerPtr<Test> value = New<Test>();
		value->Name = "Test";
		ptr = value.Get();
	}

	ptr = nullptr;
}
