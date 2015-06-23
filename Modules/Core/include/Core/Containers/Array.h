// Array.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <cassert>
#include <utility>
#include <new>
#include "../Reflection/Reflection.h"

/** A linear, contiguous array. Replacement for 'std::vector'.
* Pros:
* - Faster than 'std::vector' on all fronts (Wooh!)
* - Fastest for iteration
* - Fastest random element access
* - Fastest creation/deletion
* - Most efficient memory usage (after 'ShrinkWrap()')
* - Unlike std::vector, the given type does not have to be default-constructible
* Cons:
* - Taking pointers to elements is not safe
* - Element removal and insertion is at worst an O(n) operation
* - Adding beyond 'Capacity()' requires reallocation of the entire Array */
template <typename T>
struct Array final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT;

	static_assert(std::is_destructible<T>::value,
		"The given inner type of 'Array' must have a public destructor");
	static_assert(!std::is_reference<T>::value,
		"You can't create an 'Array' of references, dumbass");

	///////////////////////
	///   Inner Types   ///
public:

	/** Forward iterator for a mutable Array */
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

		FORCEINLINE Iterator& operator++()
		{
			++_value;
			return self;
		}
		FORCEINLINE T& operator*()
		{
			return *_value;
		}
		friend FORCEINLINE bool operator!=(const Iterator& lhs, const Iterator& rhs)
		{
			return lhs._value != rhs._value;
		}

		////////////////
		///   Data   ///
	private:

		T* _value;
	};

	/** Forward iterator for an immutable Array */
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

		FORCEINLINE ConstIterator& operator++()
		{
			++_value;
			return self;
		}
		FORCEINLINE const T& operator*() const
		{
			return *_value;
		}
		friend FORCEINLINE bool operator!=(const ConstIterator& lhs, const ConstIterator& rhs)
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
		: _values(nullptr), _allocSize(0), _numElements(0)
	{
		// All done
	}

	/** Constructs a new Array
	* 'size' - the starting size of the array */
	Array(uint32 size)
		: Array()
	{
		_values = (T*)new byte[sizeof(T) * size];
		_allocSize = size;
	}

	/** Constructs a new Array by copying an existing Array */
	Array(const Array& copy)
		: Array(copy.Size())
	{
		for (const auto& value : copy)
		{
			FastAdd(value);
		}
	}

	/** Constructs a new Array by moving an existing Array */
	Array(Array&& move)
		: _values(move._values), _allocSize(move._allocSize), _numElements(move._numElements)
	{
		move._values = nullptr;
		move._allocSize = 0;
		move._numElements = 0;
	}
	
	/** Constructs a new Array from a c-style array of related types */
	template <typename RelatedType, WHERE(std::is_constructible<T, const RelatedType&>::value)>
	Array(const RelatedType cArray[], uint32 size)
		: Array(size)
	{
		for (uint32 i = 0; i < size; ++i)
		{
			FastAdd(cArray[i]);
		}
	}

	/** Constructs a new Array from an initializer-list of related types */
	template <typename RelatedType, WHERE(std::is_constructible<T, const RelatedType&>::value)>
	Array(const std::initializer_list<RelatedType>& init)
		: Array(static_cast<uint32>(init.size()))
	{
		for (const auto& value : init)
		{
			FastAdd(value);
		}
	}

	/** Constructs a new Array from an Array of related types */
	template <typename RelatedType, WHERE(std::is_constructible<T, const RelatedType&>::value)>
	Array(const Array<RelatedType>& copy)
		: Array(copy.Size())
	{
		for (const auto& value : copy)
		{
			FastAdd(value);
		}
	}

	/** Constructs an array from an existing array of compatible types */
	template <typename CompatibleType, 
		WHERE(std::is_convertible<CompatibleType*, T*>::value 
		&& sizeof(CompatibleType) == sizeof(T))>
	Array(Array<CompatibleType>&& move)
		: _values(move._values), _allocSize(move._allocSize), _numElements(move._numElements)
	{
		move._values = nullptr;
		move._allocSize = 0;
		move._numElements = 0;
	}

	~Array()
	{
		for (uint32 i = 0; i < _numElements; ++i)
		{
			_values[i].~T();
		}
		delete[] (byte*)_values;
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns the number of elements in this Array */
	FORCEINLINE uint32 Size() const
	{
		return _numElements;
	}

	/** Returns the number of elements that can be put into this Array before needing to re-allocate */
	FORCEINLINE uint32 Capacity() const
	{
		return _allocSize;
	}

	/** Returns whether this Array is empty */
	FORCEINLINE bool IsEmpty() const
	{
		return Size() == 0;
	}

	/** Converts this Array to a c-style array */
	FORCEINLINE T* CArray()
	{
		return _values;
	}

	/** Converts this Array to a c-style array */
	FORCEINLINE const T* CArray() const
	{
		return _values;
	}

	/** Returns whether a copy of the given value exists in this Array */
	bool Contains(const T& value)
	{
		for (const auto& element : self)
		{
			if (element == value)
			{
				return true;
			}
		}

		return false;
	}

	/** Appends a new element to the end of this Array, returning the new element's index */
	template <typename RelatedType, WHERE(std::is_constructible<T, RelatedType>::value)>
	uint32 Add(RelatedType&& value)
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

		return FastAdd(std::forward<RelatedType>(value));
	}

	// @TODO: Test this
	/** Insert the given value at the given index, returning the index of the new element
	* (which may be different from the given index) */
	template <typename RelatedType, WHERE(std::is_constructible<T, RelatedType>::value)>
	uint32 Insert(RelatedType&& value, uint32 index)
	{
		// If our insert index is beyond the size of the array
		if (index > Size())
		{
			// Add it to the end
			return Add(std::forward<RelatedType>(value));
		}

		// If the array is already full
		if (Size() >= Capacity())
		{
			Resize(Capacity() * 2);
		}

		// Move element on the end up an index
		new(_values + _numElements) T(std::move(_values[_numElements - 1]));

		// Move all proceeding elements up an index
		for (uint32 i = _numElements - 1; i > index; --i)
		{
			_values[i] = std::move(_values[i - 1]);
		}

		// Insert the value
		_values[index] = std::forward<RelatedType>(value);
		++_numElements;
		return index;
	}

	/** Returns a reference to the element at the given index 
	* WARNING: Make sure the index exists in this Array */
	FORCEINLINE T& Get(uint32 index)
	{
		assert(index < Size());
		return FastGet(index);
	}

	/** Returns an immutable reference to the element at the given index
	* WARNING: Make sure the index exists in this Array */
	FORCEINLINE const T& Get(uint32 index) const
	{
		assert(index < Size());
		return FastGet(index);
	}

	/** Returns a reference to the first element in this Array
	* WARNING: Check 'IsEmpty()' before calling this */
	FORCEINLINE T& First()
	{
		assert(Size() > 0);
		return FastGet(0);
	}

	/** Returns an immutable reference to the first element in this Array
	* WARNING: Check 'IsEmpty()' before calling this */
	FORCEINLINE const T& First() const
	{
		assert(Size() > 0);
		return FastGet(0);
	}

	/** Returns a reference to the last element in this Array
	* WARNING: Check 'IsEmpty()' before calling this */
	FORCEINLINE T& Last()
	{
		assert(Size() > 0);
		return FastGet(Size() - 1);
	}

	/** Returns an immutable reference to the last element in this Array
	* WARNING: Check 'IsEmpty()' before calling this */
	FORCEINLINE const T& Last() const
	{
		assert(Size() > 0);
		return FastGet(Size() - 1);
	}
		
	/** Returns a portion of this Array from the given index to the end */
	FORCEINLINE Array Slice(uint32 start) const
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

		if (end > Size())
		{
			end = Size();
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
		for (uint32 i = index; i < Size(); ++i)
		{
			_values[i] = std::move(_values[i + 1]);
		}
		_values[--_numElements].~T();
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

	/** Extracts the value stored at the given index before deleting it
	* WARNING: Make sure the given index exists in this Array
	* NOTE: This offsets the index of every proceeding element by -1 */
	T RemoveAt(uint32 index)
	{
		T value = std::move(Get(index));
		DeleteAt(index);
		return value;
	}

	/** Reallocates the internal array with more (or less) space, moving existing elements into the new array
	* NOTE: To prevent loss of data, ensure that the given size is greater than the current size of the array */
	void Resize(uint32 size)
	{
		T* newValues = (T*)new byte[sizeof(T) * size];

		uint32 i;
		for (i = 0; i < size && i < Size(); ++i)
		{
			// Move all elements below 'size' into new array
			new(newValues + i) T(std::move(_values[i]));
		}
		for (i = 0; i < Size(); ++i)
		{
			// Destroy all elements in old array
			_values[i].~T();
		}
		delete[] (byte*)_values;

		_values = newValues;
		_allocSize = size;
		_numElements = i;
	}

	/** Frees unused space in internal array, so that 'Capacity() == Size()' */
	FORCEINLINE void ShrinkWrap()
	{
		Resize(Size());
	}

	/** Quickly deletes all values from this Array, preserving size */
	FORCEINLINE void Clear()
	{
		for (uint32 i = _numElements; i > 0; --i)
		{
			_values[i - 1].~T();
		}
		_numElements = 0;
	}

	/** Deletes all values from this Array, resetting size */
	void Reset(uint32 size)
	{
		for (uint32 i = 0; i < Size(); ++i)
		{
			_values[i].~T();
		}
		_numElements = 0;

		_values = (T*)new byte[sizeof(T) * size];
		_allocSize = size;
	}

	/* Iteration methods */
	FORCEINLINE Iterator begin()
	{
		return Iterator(_values);
	}
	FORCEINLINE ConstIterator begin() const
	{
		return ConstIterator(_values);
	}
	FORCEINLINE Iterator end()
	{
		return Iterator(&_values[Size()]);
	}
	FORCEINLINE ConstIterator end() const
	{
		return ConstIterator(&_values[Size()]);
	}

private:

	/** Returns a reference to the element at the given index
	* WARNING: Only use this if you KNOW (algorithmically) that the index exists in this Array */
	FORCEINLINE T& FastGet(uint32 index)
	{
		return _values[index];
	}

	/** Returns an immutable reference to the element at the given index
	* WARNING: Only use this if you KNOW (algorithmically) that the index exists in this Array */
	FORCEINLINE const T& FastGet(uint32 index) const
	{
		return _values[index];
	}

	/** Adds an element to the end of this Array without checking for available space
	* Returns the index of the new element
	* WARNING: Only use this if you KNOW (algorithmically) that there is enough space */
	template <typename RelatedType, WHERE(std::is_constructible<T, RelatedType>::value)>
	FORCEINLINE uint32 FastAdd(RelatedType&& value)
	{
		new(_values + _numElements) T(std::forward<RelatedType>(value));
		return _numElements++;
	}

	/////////////////////
	///   Operators   ///
public:

	FORCEINLINE T& operator[](uint32 index)
	{
		assert(index < Size());
		return FastGet(index);
	}
	FORCEINLINE const T& operator[](uint32 index) const
	{
		assert(index < Size());
		return FastGet(index);
	}
	friend FORCEINLINE bool operator!=(const Array& lhs, const Array& rhs)
	{
		return !(lhs == rhs);
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

	/** Copies an existing Array */
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

		return self;
	}

	/** Moves an existing Array */
	Array& operator=(Array&& move)
	{
		if (this != &move)
		{
			Reset(0);
			_values = move._values;
			_allocSize = move._allocSize;
			_numElements = move._numElements;

			move._values = nullptr;
			move._allocSize = 0;
			move._numElements = 0;
		}

		return self;
	}

	/** Copies an initializer-list of related types onto this Array */
	template <typename RelatedType, WHERE(std::is_constructible<T, const RelatedType&>::value)>
	Array& operator=(const std::initializer_list<RelatedType>& init)
	{
		Reset(init.size());

		for (const auto& value : init)
		{
			FastAdd(value);
		}

		return self;
	}
	
	/** Copies an Array of related types */
	template <typename RelatedType, WHERE(std::is_constructible<T, const RelatedType&>::value)>
	Array& operator=(const Array<RelatedType>& copy)
	{
		if (this != &copy)
		{
			Reset(copy.Size());

			for (const auto& value : copy)
			{
				FastAdd(value);
			}
		}

		return self;
	}

	/** Moves an Array of compatible types */
	template <typename CompatibleType, 
		WHERE(std::is_convertible<CompatibleType*, T*>::value 
		&& sizeof(CompatibleType) == sizeof(T))>
	Array& operator=(Array<CompatibleType>&& move)
	{
		if (this != &move)
		{
			Reset(0);
			_allocSize = move._allocSize;
			_values = move._values;
			_numElements = move._numElements;

			move._allocSize = 0;
			move._values = nullptr;
			move._numElements = 0;
		}

		return self;
	}

	/** Produces an Array of the concatenation of an Array and an initializer-list */
	template <typename RelatedType, WHERE(std::is_constructible<T, const RelatedType&>::value)>
	friend Array operator+(const Array& lhs, const std::initializer_list<RelatedType>& rhs)
	{
		Array result(lhs.Size() + rhs.size());

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

	/** Produces an Array of the concatenation of two other Arrays */
	friend Array operator+(const Array& lhs, const Array& rhs)
	{
		Array result(lhs.Size() + rhs.Size());

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
	
	/** Appends an initializer-list onto an Array */
	template <typename RelatedType, WHERE(std::is_constructible<T, const RelatedType&>::value)>
	friend Array& operator+=(Array& lhs, const std::initializer_list<RelatedType>& rhs)
	{
		if (lhs.Capacity() < lhs.Size() + rhs.size())
		{
			lhs.Resize(lhs.Size() + rhs.size());
		}

		for (const auto& item : rhs)
		{
			lhs.FastAdd(item);
		}

		return lhs;
	}

	/** Appends an Array onto another Array */
	template <typename RelatedType, WHERE(std::is_constructible<T, const RelatedType&>::value)>
	friend Array& operator+=(Array& lhs, const Array<RelatedType>& rhs)
	{
		if (lhs.Capacity() < lhs.Size() + rhs.Size())
		{
			lhs.Resize(lhs.Size() + rhs.Size());
		}

		for (const auto& item : rhs)
		{
			lhs.FastAdd(item);
		}

		return lhs;
	}

	////////////////
	///   Data   ///
private:
	
	T* _values;
	uint32 _allocSize;
	uint32 _numElements;
};