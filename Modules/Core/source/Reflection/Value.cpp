// Value.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/Unpack.h"

////////////////////////
///   Constructors   ///

Value::Value()
	: _value(nullptr)
{
	// All done
}

Value::Value(const Value& copy)
	: _value(nullptr)
{
	if (copy._value != nullptr)
	{
		_value = copy._value->Copy();
	}
}

Value::Value(Value&& move)
	: _value(move._value)
{
	move._value = nullptr;
}

Value::~Value()
{
	delete _value;
}

///////////////////
///   Methods   ///

String Value::ToString() const
{
	if (_value)
	{
		return _value->ToString();
	}
	else
	{
		throw NullValueException();
	}
}

const TypeInfo& Value::GetType() const
{
	if (_value)
	{
		return _value->GetType();
	}
	else
	{
		throw NullValueException();
	}
}

bool Value::IsNull() const
{
	return _value == nullptr;
}

/////////////////////
///   Operators   ///

Value& Value::operator=(const Value& copy)
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
			this->_value = nullptr;
		}
	}

	return This;
}

Value& Value::operator=(Value&& move)
{
	if (this != &move)
	{
		delete _value;
		_value = move._value;
		move._value = nullptr;
	}

	return This;
}