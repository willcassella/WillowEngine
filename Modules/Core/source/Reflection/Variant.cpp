// Variant.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/Variant.h"
#include "../../include/Core/Reflection/VoidInfo.h"

////////////////////////
///   Constructors   ///

Variant::Variant()
	: _value(nullptr), _type(TypeOf<void>())
{
	// All done
}

ImmutableVariant::ImmutableVariant()
	: _value(nullptr), _type(TypeOf<void>())
{
	// All done
}