// Queue.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "List.h"

/** Push and pop the British way!
* NOTE: 'StorageType' must be a linear collection that follows the
* Willow engine collection interface (such as 'Array', or 'List') */
template <typename T, template <typename F> class StorageType = List>
struct Queue final
{
	///////////////////////
	///   Inner Types   ///
public:

	typedef typename StorageType<T>::Iterator Iterator;
	typedef typename StorageType<T>::ConstIterator ConstIterator;

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
	Queue(const Queue& copy)
		: _values(copy._values)
	{
		// All done
	}

	template <template <typename F> class OtherStorageType>
	Queue(const Queue<T, OtherStorageType>& copy)
		: _values()
	{
		for (const auto& value : copy)
		{
			Push(value);
		}
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns the number of elements in this Queue */
	inline uint32 Size() const
	{
		return _values.Size();
	}

	/** Returns whether this Queue is empty */
	inline bool IsEmpty() const
	{
		return _values.IsEmpty();
	}

	/** Returns a reference to the first element in this Queue
	* WARNING: Check 'IsEmpty()' first */
	inline T& Peek()
	{
		return _values.First();
	}

	/** Returns an immutable reference to the first element in this Queue
	* WARNING: Check 'IsEmpty()' first */
	inline const T& Peek() const
	{
		return _values.First();
	}

	/** Appends a new element to the end of this Queue */
	inline void Push(const T& item)
	{
		_values.Add(item);
	}

	/** Removes the first element in this Queue
	WARNING: Check 'IsEmpty()' first */
	inline T Pop()
	{
		return _values.RemoveAt(0);
	}

	/** Deletes all elements in this Queue */
	inline void Clear()
	{
		_values.Clear();
	}

	/** Iteration methods */
	inline Iterator begin()
	{
		return _values.begin();
	}
	inline ConstIterator begin() const
	{
		return _values.begin();
	}
	inline Iterator end()
	{
		return _values.end();
	}
	inline ConstIterator end() const
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
	Queue& operator=(const Queue& copy)
	{
		if (this != &copy)
		{
			_values = copy._values;
		}

		return This;
	}
	friend inline bool operator==(const Queue& lhs, const Queue& rhs)
	{
		return lhs._values == rhs._values;
	}
	friend inline bool operator!=(const Queue& lhs, const Queue& rhs)
	{
		return lhs._values != rhs._values;
	}

	template <template <typename F> class OtherStorageType>
	Queue& operator=(const Queue<T, OtherStorageType>& copy)
	{
		Clear();

		for (const auto& value : copy)
		{
			Push(value);
		}

		return This;
	}

	////////////////
	///   Data   ///
private:

	StorageType<T> _values;
};