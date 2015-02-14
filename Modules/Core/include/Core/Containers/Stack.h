// Stack.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "List.h"

/** First ones in are the last ones out!
* NOTE: 'StorageType' must be a linear collection that follows the
* Willow engine collection interface (such as 'Array', or 'List') */
template <typename T, template <typename F> class StorageType = List>
struct Stack final
{
	///////////////////////
	///   Inner Types   ///
public:

	typedef typename StorageType<T>::ReverseIterator Iterator;
	typedef typename StorageType<T>::ConstReverseIterator ConstIterator;

	////////////////////////
	///   Constructors   ///
public:

	Stack()
		: _values()
	{
		// All done
	}
	Stack(const std::initializer_list<T>& init)
		: _values(init)
	{
		// All done
	}
	Stack(const Stack& copy)
		: _values(copy._values)
	{
		// All done
	}

	template <template <typename F> class OtherStorageType>
	Stack(const Stack<T, OtherStorageType>& copy)
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

	/** Returns the number of elements in this Stack */
	FORCEINLINE uint32 Size() const
	{
		return _values.Size();
	}

	/** Returns whether this Stack is empty */
	FORCEINLINE bool IsEmpty() const
	{
		return _values.IsEmpty();
	}

	/** Returns a reference to the first element in this Stack 
	* WARNING: Check 'IsEmpty()' first */
	FORCEINLINE T& Peek()
	{
		return _values.Last();
	}

	/** Returns an immutable reference to the first element in this Stack
	* WARNING: Check 'IsEmpty()' first */
	FORCEINLINE const T& Peek() const
	{
		return _values.Last();
	}

	/** Puts a new element on the top of this Stack */
	FORCEINLINE void Push(const T& item)
	{
		_values.Add(item);
	}

	/** Removes the element on the top of this Stack
	WARNING: Check 'IsEmpty()' first */
	FORCEINLINE T Pop()
	{
		return _values.RemoveAt(_values.Size() - 1);
	}

	/** Deletes all elements in this Stack */
	FORCEINLINE void Clear()
	{
		_values.Clear();
	}

	/** Iteration Methods */
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

	Stack& operator=(const std::initializer_list<T>& init)
	{
		Clear();

		for (const auto& value : init)
		{
			Push(value);
		}

		return This;
	}
	Stack& operator=(const Stack& copy)
	{
		if (this != &copy)
		{
			_values = copy._values;
		}

		return This;
	}
	friend FORCEINLINE bool operator==(const Stack& lhs, const Stack& rhs)
	{
		return lhs._values == rhs._values;
	}
	friend FORCEINLINE bool operator!=(const Stack& lhs, const Stack& rhs)
	{
		return lhs._values != rhs._values;
	}

	template <template <typename F> class OtherStorageType>
	Stack& operator=(const Stack<T, OtherStorageType>& copy)
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