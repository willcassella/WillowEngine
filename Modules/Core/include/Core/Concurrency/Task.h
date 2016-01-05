// Task.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <thread>
#include "../Containers/Nullable.h"

template <typename T>
struct Task final
{
	///////////////////
	///   Methods   ///
public:

	T& Get();

	const T& Get() const;

private:

	void Await() const
	{
		
	}

	////////////////
	///   Data   ///
private:

	Nullable<T> _result;
	std::thread _thread; // TODO: Implement thread pooling
};
