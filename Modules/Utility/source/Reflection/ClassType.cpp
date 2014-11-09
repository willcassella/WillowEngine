// ClassType.cpp

#include "..\..\include\Utility\Reflection\Reflection.h"
using namespace Willow;

//////////////////////
///   Reflection   ///

BEGIN_CLASS_INFO(Willow::ClassType)
END_REFLECTION_INFO

////////////////////////
///   Constructors   ///

ClassType::ClassType(const String& fullName)
{
	auto parsedName = String::ParseNamespace(fullName);
	this->_name = parsedName.Second;
	this->_namespace = parsedName.First;
	this->_factory = nullptr;
	this->_base = nullptr;
}

ClassType::~ClassType()
{
	for (auto& field : _fields)
	{
		delete field;
	}
}

///////////////////
///   Methods   ///

String ClassType::GetNamespace() const
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

String ClassType::GetFullName() const
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

const ClassType* ClassType::GetBase() const
{
	return _base;
}

List<const IField&> ClassType::GetAllFields() const
{
	if (!this->IsRoot())
	{
		return this->GetFields() + _base->GetAllFields();
	}
	else
	{
		return this->GetFields();
	}
}

List<const IField&> ClassType::GetFields() const
{
	List<const IField&> fields;

	for (const auto& field : _fields)
	{
		fields.Add(*field);
	}

	return fields;
}

bool ClassType::IsRoot() const
{
	return _base == nullptr;
}

bool ClassType::IsSubClassOf(const ClassType& type) const
{
	const ClassType* base = _base;

	while (base != nullptr)
	{
		if (*base == type)
		{
			return true;
		}
		else
		{
			base = base->_base;
		}
	}

	return false;
}

bool ClassType::ImplementsInterface(const InterfaceType& interf) const
{
	const ClassType* type = this;

	while (type)
	{
		if (_interfaces.HasElement(&interf))
		{
			return true;
		}
		else
		{
			type = type->_base;
		}
	}

	return false;
}

bool ClassType::HasFactory() const
{
	return _factory != nullptr;
}

object& ClassType::CreateNew() const
{
	if (this->HasFactory())
	{
		return _factory();
	}
	else
	{
		Console::Error("Attempt to instantiate @, type does not have a factory", this->GetFullName());
		throw String("Attempt to instantiate a type that does not have a factor!");
	}
}