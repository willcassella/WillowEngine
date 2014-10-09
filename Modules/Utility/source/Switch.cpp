// Switch.cpp

#include "..\include\Utility\Switch.h"
using namespace Willow;

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