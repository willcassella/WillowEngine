// Object.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Core/Containers/Table.h"
#include "../include/Core/Reflection/ClassInfo.h"

///////////////////////
///   Static Data   ///

Table<const Object*, Array<const Object**>>& GetPointerTable()
{
	static Table<const Object*, Array<const Object**>> table;
	return table;
}

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(Object);

////////////////////////
///   Constructors   ///

Object::Object()
{
	GetPointerTable()[this];
}

Object::Object(const Object& copy)
{
	GetPointerTable()[this];
}

Object::Object(Object&& move)
{
	auto& moveTable = GetPointerTable()[&move];

	for (auto ptr : moveTable)
	{
		*ptr = this;
	}

	GetPointerTable()[this] = std::move(moveTable);
}

Object::~Object()
{
	auto& myTable = GetPointerTable()[this];

	for (auto ptr : myTable)
	{
		*ptr = nullptr;
	}

	myTable.Reset(0); // @TODO: Remove table entry completely
}

///////////////////
///   Methods   ///

void Object::AddReference(const Object*& reference)
{
	GetPointerTable()[reference].Add(&reference);
}

void Object::RemoveReference(const Object*& reference)
{
	GetPointerTable()[reference].DeleteFirst(&reference);
}

/////////////////////
///   Operators   ///

Object& Object::operator=(Object&& move)
{
	if (this != &move)
	{
		auto& moveTable = GetPointerTable()[&move];
		auto& myTable = GetPointerTable()[this];

		for (auto ptr : moveTable)
		{
			*ptr = this;
			myTable.Add(ptr);
		}
		
		moveTable.Clear();
	}

	return self;
}
