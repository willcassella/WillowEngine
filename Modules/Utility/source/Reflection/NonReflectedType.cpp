// NonReflectedType.cpp

#include "../../include/Utility/Reflection/Reflection.h"
using namespace Willow;

//////////////////////
///   Reflection   ///

BEGIN_CLASS_INFO(Willow::NonReflectedType)
END_REFLECTION_INFO

////////////////////////
///   Constructors   ///

NonReflectedType::NonReflectedType(const String& fullName)
{
	auto parsedName = String::ParseNamespace(fullName);
	this->_name = parsedName.Second;
	this->_namespace = parsedName.First;
}

///////////////////
///   Methods   ///

String NonReflectedType::GetNamespace() const
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

String NonReflectedType::GetFullName() const
{
	if (_namespace.IsNullOrEmpty())
	{
		return this->GetName();
	}
	else
	{
		return String::Format("@::@", this->GetNamespace(), this->GetName());
	}
}