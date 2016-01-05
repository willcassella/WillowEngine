// TimeStamp.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../config.h"

/////////////////
///   Types   ///

struct CORE_API TimeStamp final
{
	//////////////////
	///   Fields   ///
public:


};

//////////////////
///   Macros   ///

/** Creates a new TimeStamp holding the  */
#define TIMESTAMP_TIME_NOW ::TimeStamp(__TIME__)
#define TIMESTAMP_DATE_NOW ::TimeStamp(__DATE__)
#define TIMESTAMP_DATE_TIME_NOW ::TimeStamp(__TIME__, __DATE__)