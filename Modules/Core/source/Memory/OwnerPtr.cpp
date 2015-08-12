// UniquePtr.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Memory/UniquePtr.h"
#include "../../include/Core/Reflection/VoidInfo.h"
#include "../../include/Core/Reflection/Variant.h"
#include "../../include/Core/Reflection/StructInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(UniquePtr<void>);

////////////////////////
///   Constructors   ///

UniquePtr<void>::UniquePtr()
	: _value(nullptr), _type(&TypeOf<void>())
{
	// All done
}

UniquePtr<void>::UniquePtr(UniquePtr&& move)
	: _value(move._value), _type(move._type)
{
	move._value = nullptr;
	move._type = &TypeOf<void>();
}

UniquePtr<void>::~UniquePtr()
{
	_type->GetDestructor()(_value);
}

/////////////////////
///   Operators   ///

UniquePtr<void>& UniquePtr<void>::operator=(std::nullptr_t)
{
	_type->GetDestructor()(_value);

	_value = nullptr;
	_type = &TypeOf<void>();

	return self;
}

UniquePtr<void>& UniquePtr<void>::operator=(UniquePtr&& move)
{
	if (this != &move)
	{
		_type->GetDestructor()(_value);
		
		_value = move._value;
		_type = move._type;

		move._value = nullptr;
		move._type = &TypeOf<void>();
	}

	return self;
}

Variant UniquePtr<void>::operator*()
{
	return Variant(_value, *_type);
}

ImmutableVariant UniquePtr<void>::operator*() const
{
	return ImmutableVariant(_value, *_type);
}
