// OwnerPtr.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Memory/OwnerPtr.h"
#include "../../include/Core/Reflection/VoidInfo.h"
#include "../../include/Core/Reflection/Variant.h"
#include "../../include/Core/Reflection/StructInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(OwnerPtr<void>);

////////////////////////
///   Constructors   ///

OwnerPtr<void>::OwnerPtr()
	: _value(nullptr), _type(&TypeOf<void>())
{
	// All done
}

OwnerPtr<void>::OwnerPtr(OwnerPtr&& move)
	: _value(move._value), _type(move._type)
{
	move._value = nullptr;
	move._type = &TypeOf<void>();
}

OwnerPtr<void>::~OwnerPtr()
{
	_type->GetDestructor()(_value);
}

/////////////////////
///   Operators   ///

OwnerPtr<void>& OwnerPtr<void>::operator=(std::nullptr_t)
{
	_type->GetDestructor()(_value);

	_value = nullptr;
	_type = &TypeOf<void>();

	return self;
}

OwnerPtr<void>& OwnerPtr<void>::operator=(OwnerPtr&& move)
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

Variant OwnerPtr<void>::operator*()
{
	return Variant(_value, *_type);
}

ImmutableVariant OwnerPtr<void>::operator*() const
{
	return ImmutableVariant(_value, *_type);
}
