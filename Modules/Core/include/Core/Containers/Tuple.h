// Tuple.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../config.h"

template <typename ... AnyTypes>
struct Tuple;

// Empty tuple
template <>
struct Tuple <>
{
	// Nothing here
};

// Variadic tuple
template <typename AnyType, typename ... MoreAnyTypes>
struct Tuple < AnyType, MoreAnyTypes... > : public Tuple<MoreAnyTypes...>
{
	////////////////
	///   Data   ///
private:

	AnyType _value;
};

// @TODO: Figure out a way to make tuples elements appear in order