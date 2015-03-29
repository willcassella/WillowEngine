// Queue.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Array.h"

/** Push and pop the British way! */
template <typename T>
struct Queue final
{
	///////////////////////
	///   Inner Types   ///
public:

	typedef typename Array<T>::Iterator Iterator;
	typedef typename Array<T>::ConstIterator ConstIterator;

	////////////////////////
	///   Constructors   ///
public:

	Queue()
		: _values()
	{
		// All done
	}
	Queue(const std::initializer_list<T>& init)
		: _values(init)
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns the number of elements in this Queue */
	FORCEINLINE uint32 Size() const
	{
		return _values.Size();
	}

	/** Returns whether this Queue is empty */
	FORCEINLINE bool IsEmpty() const
	{
		return _values.IsEmpty();
	}

	/** Returns a reference to the first element in this Queue
	* WARNING: Check 'IsEmpty()' first */
	FORCEINLINE T& Peek()
	{
		return _values.First();
	}

	/** Returns an immutable reference to the first element in this Queue
	* WARNING: Check 'IsEmpty()' first */
	FORCEINLINE const T& Peek() const
	{
		return _values.First();
	}

	/** Appends a new element to the end of this Queue */
	FORCEINLINE void Push(const T& item)
	{
		_values.Add(item);
	}

	/** Removes the first element in this Queue
	WARNING: Check 'IsEmpty()' first */
	FORCEINLINE T Pop()
	{
		return _values.RemoveAt(0);
	}

	/** Deletes all elements in this Queue */
	FORCEINLINE void Clear()
	{
		_values.Clear();
	}

	/** Iteration methods */
	FORCEINLINE Iterator begin()
	{
		return _values.begin();
	}
	FORCEINLINE ConstIterator begin() const
	{
		return _values.begin();
	}
	FORCEINLINE Iterator end()
	{
		return _values.end();
	}
	FORCEINLINE ConstIterator end() const
	{
		return _values.end();
	}

	/////////////////////
	///   Operators   ///
public:

	Queue& operator=(const std::initializer_list<T>& init)
	{
		Clear();

		for (const auto& value : init)
		{
			Push(value);
		}

		return This;
	}
	friend FORCEINLINE bool operator==(const Queue& lhs, const Queue& rhs)
	{
		return lhs._values == rhs._values;
	}
	friend FORCEINLINE bool operator!=(const Queue& lhs, const Queue& rhs)
	{
		return lhs._values != rhs._values;
	}

	////////////////
	///   Data   ///
private:

	Array<T> _values;
};