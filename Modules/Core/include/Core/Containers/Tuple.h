// Tuple.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Reflection/Reflection.h"

template <typename ... AnyTypes>
struct Tuple final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT;

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