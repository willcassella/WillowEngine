// Tuple.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../config.h"

template <typename ... AnyTypes>
struct Tuple final
{
	///////////////////////
	///   Inner Types   ///
private:

	template <typename T, typename ... Types>
	struct TupleStorage : public TupleStorage<Types...>
	{
		T Value;
	};

	template <typename T>
	struct TupleStorage < T >
	{
		T Value;
	};

	////////////////
	///   Data   ///
private:

	TupleStorage<AnyTypes...> _value;
};

// Tuple<int, float, char> = 

// @TODO: Figure out a way to make tuples elements appear in order