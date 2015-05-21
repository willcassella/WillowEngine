// Reflection.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/Variant.h"
#include "../../include/Core/Reflection/VoidInfo.h"

////////////////////////
///   Constructors   ///

Variant::Variant()
	: _value(nullptr), _type(&TypeOf<void>()), _isImmutable(true), _hasOwnership(false)
{
	// All done
}

Variant::Variant(void* value, const TypeInfo& type, bool hasOwnership)
	: _value(value), _type(&type), _isImmutable(false), _hasOwnership(hasOwnership)
{
	// All done
}

Variant::Variant(const void* value, const TypeInfo& type)
	: _value(const_cast<void*>(value)), _type(&type), _isImmutable(true), _hasOwnership(false)
{
	// All done
}

Variant::Variant(const Variant& copy)
	: _value(copy._value), _type(copy._type), _isImmutable(copy._isImmutable), _hasOwnership(copy._hasOwnership)
{
	if (_hasOwnership)
	{
		_value = _type->_copyConstructor(_value);
	}
}

Variant::Variant(Variant&& move)
	: _value(move._value), _type(move._type), _isImmutable(move._isImmutable), _hasOwnership(move._hasOwnership)
{
	move._value = nullptr;
}

Variant::~Variant()
{
	if (_hasOwnership)
	{
		_type->_destructor(_value);
	}
}

///////////////////
///   Methods   ///

bool Variant::TakeOwnership()
{
	if (!_hasOwnership)
	{
		void* temp = _type->_copyConstructor(_value);
		
		if (temp) // If the copy was successful
		{
			_value = temp;
			_isImmutable = false;
			_hasOwnership = true;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}

bool Variant::Destroy()
{
	if (!_hasOwnership || _isImmutable)
	{
		return false;
	}
	else
	{
		bool sucess = _type->_destructor(_value);

		if (sucess)
		{
			_value = nullptr;
			_type = &TypeOf<void>();
			_isImmutable = true;
			_hasOwnership = false;
		}

		return sucess;
	}
}