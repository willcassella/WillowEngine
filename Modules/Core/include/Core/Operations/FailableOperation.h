// FailableOperations.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../STDE/Utility.h"

/** Attempts to execute the given operation on the given arguments, if the operation is supported. */
template <typename Operation, typename ... Args>
void FailableOperation(Args&& ... args)
{
	// NOTE: In an ideal world I would use this (which is slightly cleaner), but as always it breaks MSVC...
	//auto function = [&](auto op)
	//{
	//	op.Function(std::forward<Args>(args)...);
	//};
	//
	//stde::conditionally_execute<Operation::Supported>(function, Operation());

	auto function = [](auto op, auto&& ... ar)
	{
		op.Function(std::forward<decltype(ar)>(ar)...);
	};

	stde::conditionally_execute<Operation::Supported>(function, Operation(), std::forward<Args>(args)...);
}
