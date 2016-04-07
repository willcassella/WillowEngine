// Exception.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../include/Core/Exception.h"

////////////////////////
///   Constructors   ///

Exception::Exception(String message)
	: _message{ std::move(message) }
{
	// All done
}
