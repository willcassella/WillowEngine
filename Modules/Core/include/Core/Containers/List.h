// List.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Array.h"

/** A linear linked list, replacement for 'std::list'.
* Pros:
* - Taking pointers to elements is (relatively) safe
* - Adding/Removing elements is always an O(1) operation 
* - Element type does not need to be default-constructible
* Cons:
* - Slowest for iteration
* - Random element access requires traversing the List (slow) */
template <typename T>
struct List final
{
	///////////////////////
	///   Inner Types   ///
private:

	struct Node final
	{
		////////////////////////
		///   Constructors   ///
	public:

		template <typename RelatedT>
		Node(RelatedT&& value)
			: Value(std::forward<RelatedT>(value)), Next(nullptr)
		{
			// All done
		}

		//////////////////
		///   Fields   ///
	public:

		T Value;
		Node* Next;
	};

public:

	struct Iterator final
	{
		////////////////////////
		///   Constructors   ///
	public:

		Iterator(Node* node)
			: _node(node)
		{
			// All done
		}

		/////////////////////
		///   Operators   ///
	public:

		FORCEINLINE Iterator& operator++()
		{
			_node = _node->Next;
			return self;
		}
		FORCEINLINE T& operator*()
		{
			return _node->Value;
		}
		friend FORCEINLINE bool operator!=(const Iterator& lhs, const Iterator& rhs)
		{
			return lhs._node != rhs._node;
		}

		////////////////
		///   Data   ///
	private:

		Node* _node;
	};

	struct ConstIterator final
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
			return self;
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

	/** Constructs a new List */
	List()
		: _first(nullptr), _last(nullptr), _numElements(0)
	{
		// All done
	}

	/** Constructs a new List from a c-style Array */
	List(const T cArray[], uint32 size)
		: List()
	{
		for (uint32 i = 0; i < size; ++i)
		{
			Add(cArray[i]);
		}
	}

	List(const std::initializer_list<T>& init)
		: List()
	{
		for (const auto& value : init)
		{
			Add(value);
		}
	}
	List(const List& copy)
		: List()
	{
		for (const auto& value : copy)
		{
			Add(value);
		}
	}
	List(List&& move)
		: _first(move._first), _last(move._last), _numElements(move._numElements)
	{
		move._first = nullptr;
		move._last = nullptr;
		move._numElements = 0;
	}
	~List()
	{
		Clear();
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns the number of elements in this List */
	FORCEINLINE uint32 Size() const
	{
		return _numElements;
	}

	/** Returns whether this List is empty */
	FORCEINLINE bool IsEmpty() const
	{
		return Size() == 0;
	}

	/** Returns whether a copy of the given value exists in this List */
	bool Contains(const T& value) const
	{
		for (const auto& element : self)
		{
			if (value == element)
			{
				return true;
			}
		}

		return false;
	}

	/** Appends a new element to the end of this List */
	template <typename RelatedType>
	void Add(RelatedType&& value)
	{
		if (IsEmpty())
		{
			_first = new Node(std::forward<RelatedType>(value));
			_last = _first;
		}
		else
		{
			_last->Next = new Node(std::forward<RelatedType>(value));
			_last = _last->Next;
		}

		++_numElements;
	}

	/** Returns a reference to the first element in this List 
	* WARNING: Check 'IsEmpty()' before calling this */
	T& First()
	{
		assert(_first);
		return _first->Value;
	}

	/** Returns an immutable reference to the first element in this List
	* WARNING: Check 'IsEmpty()' before calling this */
	const T& First() const
	{
		assert(_first);
		return _first->Value;
	}

	/** Returns a reference to the last element in this List
	* WARNING: Check 'IsEmpty()' before calling this */
	T& Last()
	{
		assert(_last);
		return _last->Value;
	}

	/** Returns an immutable reference to the last element in this List
	* WARNING: Check 'IsEmpty()' before calling this */
	const T& Last() const
	{
		assert(_last);
		return _last->Value;
	}

	/** Returns the indices at which a copy of value occurs in this List */
	Array<uint32> OccurrencesOf(const T& value) const
	{
		Array<uint32> occurrences;

		uint32 index = 0;
		for (const auto& element : self)
		{
			if (element == value)
			{
				occurrences.Add(index);
			}

			++index;
		}

		return occurrences;
	}

	/** Returns a portion of this List from the given index to the end */
	FORCEINLINE List Slice(uint32 start)
	{
		return Slice(start, Size());
	}

	/** Returns the portion of this List between the given 'start' and 'end' indices */
	List Slice(uint32 start, uint32 end)
	{
		List result;

		if (start >= Size() || start >= end)
		{
			return result;
		}

		uint32 i = 0;

		for (const auto& element : self)
		{
			if (i >= start)
			{
				result.Add(element);
			}

			++i;
		}

		return result;
	}

	/** Deletes the element stored at the specified index in this List
	* NOTE: This may offset the index of every proceeding element by -1 */
	void DeleteAt(uint32 index)
	{
		if (index >= Size())
		{
			return;
		}

		Node* target = _first;
		Node* prev = nullptr;

		for (uint32 i = 0; i <= index; ++i)
		{
			prev = target;
			target = target->Next;
		}

		DeleteNode(target, prev);
	}

	/** Deletes the first occurrence of the specified value in this List
	* WARNING: This may offset the index of every proceeding element by -1 */
	void DeleteFirst(const T& value)
	{
		Node* target = _first;
		Node* prev = nullptr;

		while (target->Value != value)
		{
			prev = target;
			target = target->Next;

			if (target == nullptr)
			{
				// We've reached the end of the List
				return;
			}
		}

		DeleteNode(target, prev);
	}

	/** Deletes the last occurrence of the specified value in this List
	* WARNING: This may offset the index of every proceeding element by -1 */
	void DeleteLast(const T& value)
	{
		Node* target = _first;
		Node* prev = nullptr;
			
		Node* occurrence = nullptr;
		Node* occurrencePrev = nullptr;

		while (target != nullptr)
		{
			if (target->Value == value)
			{
				occurrence = target;
				occurrencePrev = prev;
			}

			prev = target;
			target = target->Next;
		}

		// If an occurrence was found
		if (occurrence != nullptr)
		{
			DeleteNode(occurrence, occurrencePrev);
		}
	}

	/** Deletes all occurrences of the specified value in this List
	* WARNING: This offsets the index of every proceeding element */
	void DeleteAll(const T& value)
	{
		Node* target = _first;
		Node* prev = nullptr;

		uint32 size = Size();
		for (uint32 i = 0; i < size; ++i)
		{
			if (target->Value == value)
			{
				target = target->Next;
				DeleteNode(target, prev);
				--size;
			}
			else
			{
				prev = target;
				target = target->Next;
			}
		}
	}

	/** Deletes the element stored at the specified index in this List
	* WARNING: Make sure the given index exists in this Array
	* NOTE: This offsets the index of every proceeding element by -1 */
	T RemoveAt(uint32 index)
	{
		assert(index < Size());

		Node* target = _first;
		Node* prev = nullptr;

		for (uint32 i = 0; i < index; ++i)
		{
			prev = target;
			target = target->Next;
		}

		T value = std::move(target->Value);
		DeleteNode(target, prev);
		return value;
	}

	/** Deletes all elements in this List */
	void Clear()
	{
		Node* next = _first;
		while (next)
		{
			Node* current = next;
			next = next->Next;
			delete current;
		}

		_first = nullptr;
		_last = nullptr;
		_numElements = 0;
	}

	/* Iteration methods */
	FORCEINLINE Iterator begin()
	{
		return Iterator(_first);
	}
	FORCEINLINE ConstIterator begin() const
	{
		return ConstIterator(_first);
	}
	FORCEINLINE Iterator end()
	{
		return Iterator(nullptr);
	}
	FORCEINLINE ConstIterator end() const
	{
		return ConstIterator(nullptr);
	}

private:

	/** Deletes the given node and patches the nodes around it 
	* 'node' - The node to delete 
	* 'prev' - The node that comes before the target node */
	void DeleteNode(Node* target, Node* prev)
	{
		if (prev)
		{
			prev->Next = target->Next;
		}
		else
		{
			_first = target->Next;
		}
		if (target == _last)
		{
			_last = prev;
		}

		delete target;
		--_numElements;
	}

	/////////////////////
	///   Operators   ///
public:

	List& operator=(const std::initializer_list<T>& init)
	{
		Clear();

		for (const auto& value : init)
		{
			Add(value);
		}

		return self;
	}
	List& operator=(const List& copy)
	{
		if (this != &copy)
		{
			Clear();

			for (const auto& value : copy)
			{
				Add(value);
			}
		}

		return self;
	}
	List& operator=(List&& move)
	{
		if (this != &move)
		{
			Clear();

			_first = move._first;
			_last = move._last;
			_numElements = move._numElements;

			move._first = nullptr;
			move._last = nullptr;
			move._numElements = 0;
		}

		return self;
	}
	T& operator[](uint32 index)
	{
		assert(index < Size());

		Node* target = _first;
		for (uint32 i = 0; i < index; ++i)
		{
			target = target->Next;
		}

		return target->Value;
	}
	const T& operator[](uint32 index) const
	{
		assert(index < Size());

		Node* target = _first;
		for (uint32 i = 0; i < index; ++i)
		{
			target = target->Next;
		}

		return target->Value;
	}
	friend List operator+(const List& lhs, const List& rhs)
	{
		List result = lhs;
		for (const auto& value : rhs)
		{
			result.Add(value);
		}
		return result;
	}
	friend FORCEINLINE List& operator+=(List& lhs, const List& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}
	friend bool operator==(const List& lhs, const List& rhs)
	{
		if (lhs.Size() != rhs.Size())
		{
			return false;
		}

		Node* lCurrent = lhs._first;
		Node* rCurrent = rhs._first;

		for (uint32 i = 0; i < lhs.Size(); ++i)
		{
			if (lCurrent->Value != rCurrent->Value)
			{
				return false;
			}

			lCurrent = lCurrent->Next;
			rCurrent = rCurrent->Next;
		}

		return true;
	}
	friend FORCEINLINE bool operator!=(const List& lhs, const List& rhs)
	{
		return !(lhs == rhs);
	}

	////////////////
	///   Data   ///
private:

	Node* _first;
	Node* _last;
	uint32 _numElements;
};