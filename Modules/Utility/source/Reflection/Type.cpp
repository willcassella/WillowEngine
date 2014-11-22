// Type.cpp

#include "../../include/Utility/Reflection/Reflection.h"
using namespace Willow;

//////////////////////
///   Reflection   ///

BEGIN_CLASS_INFO(Willow::Type)
END_REFLECTION_INFO

///////////////////
///   Methods   ///

String Type::ToString() const
{
	return this->GetFullName();
}

String Type::GetName() const
{
	return _name;
}

uint32 Type::GetSize() const
{
	return _size;
}

/////////////////////
///   Operators   ///

bool Willow::operator==(const Type& lhs, const Type& rhs)
{
	return lhs.GetFullName() == rhs.GetFullName();
}