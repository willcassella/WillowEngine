// Unpack.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/Unpack.h"

///////////////////////////////////////
///   IncompatibleUnpackException   ///

////////////////////////
///   Constructors   ///

IncompatibleUnpackException::IncompatibleUnpackException(const TypeInfo& actualType, const TypeInfo& attemptedCastType)
	: _actualType(&actualType), _attemptedUnpackType(&attemptedCastType)
{
	// All done
}

///////////////////
///   Methods   ///

String IncompatibleUnpackException::GetError() const
{
	return String::Format("Illegal Cast: '@' to '@'", _actualType->GetName(), _attemptedUnpackType->GetName());
}

const TypeInfo& IncompatibleUnpackException::GetActualType() const
{
	return *_actualType;
}

const TypeInfo& IncompatibleUnpackException::GetAttemptedUnpackType() const
{
	return *_attemptedUnpackType;
}


///////////////////////////////
///   NullValueException   ///

///////////////////
///   Methods   ///

String NullValueException::GetError() const
{
	return "An attempt to interact with a null Value was made";
}


//////////////////////////////////
///   NullReferenceException   ///

///////////////////
///   Methods   ///

String NullReferenceException::GetError() const
{
	return "An attempt to interact with a null Reference was made";
}


///////////////////////////////////////
///   ImmutableReferenceException   ///

///////////////////
///   Methods   ///

String ImmutableReferenceException::GetError() const
{
	return "An attempt to unpack an immutable Reference as a mutable reference type was made";
}