// Reference.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/Unpack.h"

////////////////////////
///   Constructors   ///

Reference::Reference()
	: _value(nullptr)
{
	// All done
}

Reference::Reference(const Reference& copy)
	: _value(nullptr)
{
	if (copy._value != nullptr)
	{
		_value = copy._value->Copy();
	}
}

Reference::Reference(Reference&& move)
	: _value(move._value)
{
	move._value = nullptr;
}

Reference::~Reference()
{
	delete _value;
}

///////////////////
///   Methods   ///

String Reference::ToString() const
{
	if (_value)
	{
		return _value->ToString();
	}
	else
	{
		throw NullReferenceException();
	}
}

const TypeInfo& Reference::GetType() const
{
	if (_value)
	{
		return _value->GetType();
	}
	else
	{
		throw NullReferenceException();
	}
}

bool Reference::IsNull() const
{
	return _value == nullptr;
}

bool Reference::IsImmutable() const
{
	if (_value)
	{
		return _value->IsImmutable();
	}
	else
	{
		throw NullReferenceException();
	}
}

void Reference::Nullify()
{
	delete _value;
	_value = nullptr;
}

/////////////////////
///   Operators   ///

Reference& Reference::operator=(std::nullptr_t)
{
	delete _value;
	_value = nullptr;

	return This;
}

Reference& Reference::operator=(const Reference& copy)
{
	if (this != &copy)
	{
		delete _value;

		if (copy._value != nullptr)
		{
			_value = copy._value->Copy();
		}
		else
		{
			_value = nullptr;
		}
	}

	return This;
}

Reference& Reference::operator=(Reference&& move)
{
	if (this != &move)
	{
		delete _value;
		_value = move._value;
		move._value = nullptr;
	}

	return This;
}