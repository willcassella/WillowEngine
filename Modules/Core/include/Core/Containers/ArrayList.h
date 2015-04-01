// ArrayList.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Array.h"

/** A linear linked list with contiguously allocated nodes.
* Pros:
* - Iteration speed approaches that of Array
* - Removing elements is always an O(1) operation
* - Fast creation/deletion
* Cons:
* - Taking pointers to elements is not safe
* - Element type must be default-constructible
* - Adding beyond MaxSize() requires reallocation of the entire List
* - Random access requires traversing the List (slow) */
template <typename T>
struct ArrayList
{
	///////////////////////
	///   Inner Types   ///
private:

	struct Node
	{
		//////////////////
		///   Fields   ///
	public:

		T Value;
		uint32 Next;
	};

public:

	struct Iterator
	{
		////////////////////////
		///   Constructors   ///
	public:

		Iterator(ArrayList* list, Node* node)
			: _list(list), _node(node)
		{
			// All done
		}

		/////////////////////
		///   Operators   ///
	public:

		FORCEINLINE Iterator& operator++()
		{
			_node = 
			return This;
		}
		FORCEINLINE T& operator*()
		{
			return _node->Value;
		}
		friend FORCEINLINE bool operator!=(const Iterator& lhs, const Iterator& rhs)
		{
			return lhs._node == rhs._node;
		}

		////////////////
		///   Data   ///
	private:

		ArrayList* _list;
		Node* _node;
	};

	struct ConstIterator
	{
		////////////////////////
		///   Constructors   ///
	public:

		ConstIterator(const Node* node)
			: _node(node)
		{
			// All done
		}

		/////////////////////
		///   Operators   ///
	public:

		FORCEINLINE ConstIterator& operator++()
		{
			_node = _node->Next;
			return This;
		}
		FORCEINLINE const T& operator*() const
		{
			return _node->Value;
		}
		friend FORCEINLINE bool operator!=(const ConstIterator& lhs, const ConstIterator& rhs)
		{
			return lhs._node != rhs._node;
		}

		////////////////
		///   Data   ///
	private:

		const Node* _node;
	};

	////////////////////////
	///   Constructors   ///
public:

	ArrayList()
		: _values(), _first(0), _last(0), _numElements(0)
	{
		// All done
	}
	ArrayList(const T cArray[], uint32 size)
		: ArrayList()
	{
		// @TODO: Implement this
	}
	ArrayList(const std::initializer_list<T>& init)
		: ArrayList()
	{
		// @TODO: Implement this
	}

	///////////////////
	///   Methods   ///
public:

	/////////////////////
	///   Operators   ///
public:

	ArrayList& operator=(const std::initializer_list& init)
	{
		// @TODO: Implement this
	}

	////////////////
	///   Data   ///
private:

	Array<Node> _values;
	uint32 _first;
	uint32 _last;
	uint32 _numElements;
};