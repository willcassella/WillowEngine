// object.cpp
#pragma once

#include "..\..\include\Utility\Reflection\Reflection.h"
using namespace Willow;

///////////////////
///   Methods   ///

String object::ToString() const
{
	String string = this->GetType().GetName() + "{ ";
	bool fence = false;
	for (const auto& field : this->GetType().GetAllFields())
	{
		if (fence)
		{
			string += ", ";
		}
		else
		{
			fence = true;
		}
		
		string += field.GetName() +" : " + field.GetValue(This).ToString();
	}
	string += " }";
	return string;
}

bool object::IsA(const Type& type) const
{
	const ClassType& thisType = this->GetType();

	if (thisType == type)
	{
		return true;
	}
	else if (type.IsA<ClassType>())
	{
		return thisType.IsSubClassOf((const ClassType&)type);
	}
	else
	{
		return false;
	}
}

bool object::Implements(const InterfaceType& interf) const
{
	return this->GetType().ImplementsInterface(interf);
}

/////////////////////
///   Operators   ///

void object::operator=(const object& rhs)
{
	// Nothing to do
}