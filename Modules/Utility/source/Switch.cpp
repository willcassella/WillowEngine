// Switch.cpp

#include "..\include\Utility\Switch.h"
using namespace Willow;

//////////////////////
///   Reflection   ///

BEGIN_CLASS_INFO(Willow::Switch)
HAS_FACTORY
END_REFLECTION_INFO

////////////////////////
///   Constructors   ///

Switch::Switch(bool value)
{
	this->_value = value;
}

///////////////////
///   Methods   ///

bool Switch::Toggle()
{
	if (_value)
	{
		_value = false;
	}
	else
	{
		_value = true;
	}

	return _value;
}

String Switch::ToString() const
{
	return ValueToString(_value);
}