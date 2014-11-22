// InterfaceType.cpp

#include "../../include/Utility/Reflection/Reflection.h"
using namespace Willow;

//////////////////////
///   Reflection   ///

BEGIN_CLASS_INFO(Willow::InterfaceType)
END_REFLECTION_INFO

////////////////////////
///   Constructors   ///

InterfaceType::InterfaceType(const String& fullName)
{
	auto parsedName = String::ParseNamespace(fullName);
	this->_name = parsedName.Second;
	this->_namespace = parsedName.First;
}

///////////////////
///   Methods   ///

String InterfaceType::GetNamespace() const
{
	if (_namespace.IsNullOrEmpty())
	{
		return "global";
	}
	else
	{
		return _namespace;
	}
}

String InterfaceType::GetFullName() const
{
	if (_namespace.IsNullOrEmpty())
	{
		return _name;
	}
	else
	{
		return String::Format("@::@", _namespace, _name);
	}
}