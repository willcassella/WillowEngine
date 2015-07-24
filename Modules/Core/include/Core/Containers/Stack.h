// Stack.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Array.h"

/** First ones in are the last ones out! */
template <typename T>
struct Stack final
{
	///////////////////////
	///   Inner Types   ///
public:

	/** Forward iterator for a mutable Stack */
	using Iterator = typename Array<T>::ReverseIterator;

	/** Forward iterator for an immutable Stack */
	using ConstIterator = typename Array<T>::ConstReverseIterator;

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
	template <typename RelatedT, WHERE(std::is_constructible<T, RelatedT>::value)>
	FORCEINLINE void Push(RelatedT&& item)
	{
		_values.Add(std::forward<RelatedT>(item));
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

		return self;
	}
	friend FORCEINLINE bool operator==(const Stack& lhs, const Stack& rhs)
	{
		return lhs._values == rhs._values;
	}
	friend FORCEINLINE bool operator!=(const Stack& lhs, const Stack& rhs)
	{
		return lhs._values != rhs._values;
	}

	////////////////
	///   Data   ///
private:

	Array<T> _values;
};