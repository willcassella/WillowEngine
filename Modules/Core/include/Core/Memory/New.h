// New.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <cassert>
#include "../Application.h"

/////////////////
///   Types   ///

/** Type holding ownership over a new instance of a type, who's ownership semantics have not been yet determined.
* NOTE: This is ONLY created by the 'New<T>()' function. */
template <typename T>
struct NewPtr final
{
	///////////////////////
	///   Information   ///
public:

	/** NewPtr may only be created by this function. */
	template <typename T, typename ... ArgT>
	friend NewPtr<T> New(ArgT&&...);

	////////////////////////
	///   Constructors   ///
public:

	NewPtr(const NewPtr& copy) = delete;
	NewPtr(NewPtr&& move) = default;
	~NewPtr()
	{
		assert(_controller == nullptr /* A value was created by 'New', but it was never taken ownership of. */);
	}

private:

	NewPtr(MemoryBlockController* controller)
		: _controller(controller)
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns the controller for the new instance of 'T', taking ownership away from this NewPtr.
	* WARNING: This should only be called once. */
	MemoryBlockController* TakeOwnership()
	{
		MemoryBlockController* temp = _controller;
		_controller = nullptr;
		return temp;
	}

	/////////////////////
	///   Operators   ///
public:

	NewPtr& operator=(const NewPtr& copy) = delete;
	NewPtr& operator=(NewPtr&& move) = delete;

	////////////////
	///   Data   ///
private:

	MemoryBlockController* _controller;
};

/////////////////////
///   Functions   ///

/** Constructs a new instance of 'T'. */
template <typename T, typename ... ArgT>
NewPtr<T> New(ArgT&& ... args)
{
	auto controller = Application::GetMemoryManager().AllocateNew(TypeOf<T>());
	controller->template Construct<T>(std::forward<ArgT>(args)...);

	return controller;
}
