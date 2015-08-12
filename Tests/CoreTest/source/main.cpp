// main.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Core/Core.h>

class Test : public Object
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(Object);

	////////////////////////
	///   Constructors   ///
public:

	Test(Object& owner)
		: _owner(&owner)
	{
		// All done	
	}
	Test(DynamicInitializer)
	{
		_owner = nullptr;
		Name = "Fred";
	}

	///////////////////
	///    Fields   ///
public:

	String Name;

	///////////////////
	///   Methods   ///
public:

	FORCEINLINE Object& GetOwner()
	{
		return *_owner;
	}

	FORCEINLINE const Object& GetOwner() const
	{
		return *_owner;
	}

	////////////////
	///   Data   ///
private:

	Object* _owner;
};

BUILD_REFLECTION(Test)
.AddProperty("Name", "The name of this object.", &Test::Name)
.AddProperty("Owner", "The owner of this object", &Test::_owner);

void PrintProperties(Variant v)
{
	Console::WriteLine(v);
}

int main()
{
	TypePtr<> type = *Application::FindType("Test");

	DynamicBuffer testContainer(type->GetSize());
	type->GetConstructor()(testContainer.GetValue());
	Variant test(testContainer.GetValue(), type);

	PrintProperties(test);
	Console::Prompt();
}
