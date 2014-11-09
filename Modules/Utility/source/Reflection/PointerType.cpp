// PointerType.cpp

#include "..\..\include\Utility\Reflection\Reflection.h"
using namespace Willow;

//////////////////////
///   Reflection   ///

BEGIN_CLASS_INFO(Willow::PointerType)
END_REFLECTION_INFO

////////////////////////
///   Constructors   ///

PointerType::PointerType(const Type& pointedType)
	: Super(pointedType.GetFullName() + "*"), _pointedType(&pointedType)
{
	// All done
}

///////////////////
///   Methods   ///

const Type& PointerType::GetPointedType() const
{
	return *_pointedType;
}