// Array.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <cassert>
#include <utility>
#include <initializer_list>
#include "../config.h"

/** A linear, contiguous array. Replacement for 'std::vector'.
* Pros:
* - Faster than 'std::vector' on all fronts (Wooh!)
* - Fastest for iteration
* - Fastest random element access
* - Fastest creation/deletion
* - Most efficient memory usage (after 'ShrinkWrap()')
* Cons:
* - Taking pointers to elements is not safe
* - Element type must be default-constructible
* - Element removal is an O(n) operation
* - Adding beyond 'Capacity()' requires reallocation of the entire Array */
template <typename T>
struct Array final
{
	///////////////////////
	///   Inner Types   ///
public:

	struct Iterator final
	{
		////////////////////////
		///   Constructors   ///
	public:

		Iterator(T* value)
			: _value(value)
		{
			// All done
		}

		/////////////////////
		///   Operators   ///
	public:

		inline Iterator& operator++()
		{
			++_value;
			return This;
		}
		inline T& operator*()
		{
			return *_value;
		}
		friend inline bool operator!=(const Iterator& lhs, const Iterator& rhs)
		{
			return lhs._value != rhs._value;
		}

		////////////////
		///   Data   ///
	private:

		T* _value;
	};

	struct ConstIterator final
	{
		////////////////////////
		///   Constructors   ///
	public:

		ConstIterator(const T* value)
			: _value(value)
		{
			// All done
		}

		/////////////////////
		///   Operators   ///
	public:

		inline ConstIterator& operator++()
		{
			++_value;
			return This;
		}
		inline const T& operator*() const
		{
			return *_value;
		}
		friend inline bool operator!=(const ConstIterator& lhs, const ConstIterator& rhs)
		{
			return lhs._value != rhs._value;
		}

		////////////////
		///   Data   ///
	private:

		const T* _value;
	};

	////////////////////////
	///   Constructors   ///
public:

	/** Default-constructs an Array */
	Array()
		: _allocSize(0), _values(nullptr), _numElements(0)
	{
		// All done
	}

	/** Constructs a new Array
	* 'size' - the starting size of the array */
	Array(uint32 size)
		: _allocSize(size), _values(new T[_allocSize]), _numElements(0)
	{
		// All done
	}

	/** Constructs a new Array from a c-style array */
	Array(const T cArray[], uint32 size)
		: Array(size)
	{
		for (uint32 i = 0; i < size; ++i)
		{
			FastAdd(cArray[i]);
		}
	}

	Array(const std::initializer_list<T>& init)
		: Array(static_cast<uint32>(init.size()))
	{
		for (const auto& value : init)
		{ 
			FastAdd(value);
		}
	}
	Array(const Array& copy)
		: Array(copy.Size())
	{
		for (const auto& value : copy)
		{
			FastAdd(value);
		}
	}
	Array(Array&& move)
		: _allocSize(move._allocSize), _values(move._values), _numElements(move._numElements)
	{
		move._values = nullptr;
		move._numElements = 0;
		move._allocSize = 0;
	}
	~Array()
	{
		delete[] _values;
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns the number of elements in this Array */
	inline uint32 Size() const
	{
		return _numElements;
	}

	/** Returns the number of elements that can be put into this Array before needing to re-allocate */
	inline uint32 Capacity() const
	{
		return _allocSize;
	}

	/** Returns whether this Array is empty */
	inline bool IsEmpty() const
	{
		return Size() == 0;
	}

	/** Returns whether a copy of the given value exists in this Array */
	bool Contains(const T& value)
	{
		for (const auto& element : This)
		{
			if (element == value)
			{
				return true;
			}
		}

		return false;
	}

	/** Appends a new element to the end of this Array */
	void Add(const T& value)
	{
		if (Size() >= Capacity())
		{
			if (IsEmpty())
			{
				Resize(1);
			}
			else
			{
				Resize(Capacity() * 2);
			}
		}

		FastAdd(value);
	}

	/** Returns a reference to the element at the given index 
	* WARNING: Make sure the index exists in this Array */
	inline T& Get(uint32 index)
	{
		assert(index < Size());
		return FastGet(index);
	}

	/** Returns an immutable reference to the element at the given index
	* WARNING: Make sure the index exists in this Array */
	inline const T& Get(uint32 index) const
	{
		assert(index < Size());
		return FastGet(index);
	}

	/** Returns a reference to the first element in this Array
	* WARNING: Check 'IsEmpty()' before calling this */
	inline T& First()
	{
		assert(Size() > 0);
		return FastGet(0);
	}

	/** Returns an immutable reference to the first element in this Array
	* WARNING: Check 'IsEmpty()' before calling this */
	inline const T& First() const
	{
		assert(Size() > 0);
		return FastGet(0);
	}

	/** Returns a reference to the last element in this Array
	* WARNING: Check 'IsEmpty()' before calling this */
	inline T& Last()
	{
		assert(Size() > 0);
		return FastGet(Size() - 1);
	}

	/** Returns an immutable reference to the last element in this Array
	* WARNING: Check 'IsEmpty()' before calling this */
	inline const T& Last() const
	{
		assert(Size() > 0);
		return FastGet(Size() - 1);
	}
		
	/** Returns a portion of this Array from the given index to the end */
	inline Array Slice(uint32 start) const
	{
		return Slice(start, Size());
	}

	/** Returns a portion of this Array, starting at the 'start' index and ending at the 'end' index */
	Array Slice(uint32 start, uint32 end) const
	{
		if (start >= end || start > Size())
		{
			return Array();
		}

		return Array(_values + start, end - start);
	}

	/** Returns the indices at which a copy of the given value occurs in this Array */
	Array<uint32> OccurrencesOf(const T& value) const
	{
		Array<uint32> occurrences;

		for (uint32 i = 0; i < Size(); ++i)
		{
			if (value == FastGet(i))
			{
				occurrences.Add(i);
			}
		}

		return occurrences;
	}

	/** Deletes the value stored at the specified index in this Array
	* NOTE: This may offset the index of every proceeding element by -1 */
	void DeleteAt(uint32 index)
	{
		if (index >= Size())
		{
			return;
		}

		for (uint32 i = index; i < Size() - 1; ++i)
		{
			_values[i] = std::move(_values[i + 1]);
		}

		--_numElements;
	}

	/** Deletes the first occurrence of the given value in this Array
	* NOTE: This may offset the index of every proceeding element by -1 */
	void DeleteFirst(const T& value)
	{
		for (uint32 i = 0; i < Size(); ++i)
		{
			if (value == FastGet(i))
			{
				DeleteAt(i);
				return;
			}
		}
	}

	/** Deletes the last occurrence of the given value in this Array
	* NOTE: This may offset the index of every proceeding element by -1 */
	void DeleteLast(const T& value)
	{
		for (uint32 i = Size(); i > 0; --i)
		{
			if (value == FastGet(i - 1))
			{
				DeleteAt(i - 1);
				return;
			}
		}
	}

	/** Deletes all occurrences of the specified value in this Array
	* NOTE: This offsets the index of every proceeding element where a deletion occurs */
	void DeleteAll(const T& value)
	{
		uint32 i = 0;
		while (i < Size())
		{
			if (value == FastGet(i))
			{
				DeleteAt(i);
			}
			else
			{
				++i;
			}
		}
	}

	/** Returns a copy of the value stored at the given index before deleting it
	* WARNING: Make sure the index exists in this Array
	* NOTE: This offsets the index of every proceeding element by -1 */
	T RemoveAt(uint32 index)
	{
		assert(index < Size());
		T value = std::move(FastGet(index));
		DeleteAt(index);
		return value;
	}

	/** Reallocates the internal array with more (or less) space, moving existing elements into the new array
	* NOTE: To prevent loss of data, ensure that the given size is greater than the current size of the array */
	void Resize(uint32 size)
	{
		T* newValues = new T[size];

		uint32 i;
		for (i = 0; i < size && i < Size(); ++i)
		{
			newValues[i] = std::move(_values[i]);
		}

		delete[] _values;
		_values = newValues;
		_allocSize = size;
		_numElements = i;
	}

	/** Frees unused space in internal array, so that 'Capacity() == Size()' */
	inline void ShrinkWrap()
	{
		Resize(Size());
	}

	/** Quickly deletes all values from this Array, preserving size 
	* NOTE: Does not actually call destructor on existing elements. For that call 'Reset(Size())' */
	inline void Clear()
	{
		_numElements = 0;
	}

	/** Deletes all values from this Array, resetting size */
	void Reset(uint32 size)
	{
		delete[] _values;

		_allocSize = size;
		_values = new T[_allocSize];
		_numElements = 0;
	}

	/* Iteration methods */
	inline Iterator begin()
	{
		return Iterator(_values);
	}
	inline ConstIterator begin() const
	{
		return ConstIterator(_values);
	}
	inline Iterator end()
	{
		return Iterator(&_values[Size()]);
	}
	inline ConstIterator end() const
	{
		return ConstIterator(&_values[Size()]);
	}

private:

	/** Returns a reference to the element at the given index
	* WARNING: Only use this if you KNOW (algorithmically) that the index exists in this Array */
	inline T& FastGet(uint32 index)
	{
		return _values[index];
	}

	/** Returns an immutable reference to the element at the given index 
	* WARNING: Only use this if you KNOW (algorithmically) that the index exists in this Array */
	inline const T& FastGet(uint32 index) const
	{
		return _values[index];
	}

	/** Adds an element to the end of this Array without checking for available space
	* WARNING: Only use this if you KNOW (algorithmically) that there is enough space */
	inline void FastAdd(const T& value)
	{
		_values[_numElements++] = value;
	}

	/////////////////////
	///   Operators   ///
public:

	Array& operator=(const std::initializer_list<T>& init)
	{
		Reset(init.size());
			
		for (const auto& value : init)
		{
			FastAdd(value);
		}

		return This;
	}
	Array& operator=(const Array& copy)
	{
		if (this != &copy)
		{
			Reset(copy.Size());

			for (const auto& value : copy)
			{
				FastAdd(value);
			}
		}
		return This;
	}
	Array& operator=(Array&& move)
	{
		if (this != &move)
		{
			delete[] _values;
			_allocSize = move._allocSize;
			_values = move._values;
			_numElements = move._numElements;

			move._allocSize = 0;
			move._values = nullptr;
			move._numElements = 0;
		}
		return This;
	}
	T& operator[](uint32 index)
	{
		assert(index < Size());
		return FastGet(index);
	}
	const T& operator[](uint32 index) const
	{
		assert(index < Size());
		return FastGet(index);
	}
	friend Array operator+(const Array& lhs, const Array& rhs)
	{
		Array<T> result(lhs.Size() + rhs.Size());

		for (const auto& item : lhs)
		{
			result.FastAdd(item);
		}

		for (const auto& item : rhs)
		{
			result.FastAdd(item);
		}

		return result;
	}
	friend Array& operator+=(Array& lhs, const Array& rhs)
	{
		if (lhs.Capacity() >= lhs.Size() + rhs.Size())
		{
			for (const auto& item : rhs)
			{
				lhs.FastAdd(item);
			}
		}
		else
		{
			lhs.Resize(lhs.Size() + rhs.Size());

			for (const auto& item : rhs)
			{
				lhs.FastAdd(item);
			}
		}

		return lhs;
	}
	friend bool operator==(const Array& lhs, const Array& rhs)
	{
		if (lhs.Size() != rhs.Size())
		{
			return false;
		}

		for (uint32 i = 0; i < lhs.Size(); ++i)
		{
			if (lhs.FastGet(i) != rhs.FastGet(i))
			{
				return false;
			}
		}

		return true;
	}
	friend inline bool operator!=(const Array& lhs, const Array& rhs)
	{
		return !(lhs == rhs);
	}

	////////////////
	///   Data   ///
private:

	uint32 _allocSize;
	T* _values;
	uint32 _numElements;
};