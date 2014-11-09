// PrimitiveType.cpp

#include "..\..\include\Utility\Reflection\Reflection.h"
using namespace Willow;

//////////////////////
///   Reflection   ///

BEGIN_CLASS_INFO(Willow::PrimitiveType)
END_REFLECTION_INFO

////////////////////////
///   Constructors   ///

PrimitiveType::PrimitiveType(const String& name)
{
	this->_name = name;
}

///////////////////
///   Methods   ///

String PrimitiveType::GetFullName() const
{
	return this->GetName();
}