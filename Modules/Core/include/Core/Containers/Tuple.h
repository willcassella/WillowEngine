// Tuple.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

template <typename ... AnyTypes>
struct Tuple final
{
	///////////////////////
	///   Inner Types   ///
private:

	template <typename T, typename ... Types>
	struct TupleStorage : TupleStorage<Types...>
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

// @TODO: Figure out a way to make tuples elements appear in order
