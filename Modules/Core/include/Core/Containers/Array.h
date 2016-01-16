// Array.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <new>
#include <cassert>
#include <utility>
#include <initializer_list>
#include "../STDE/TypeTraits.h"
#include "../Operations/TypeOps.h"
#include "DynamicBuffer.h"

/** A linear, contiguous array. Replacement for 'std::vector'.
* Pros:
* - Faster than 'std::vector' on all fronts (Wooh!).
* - Fastest for iteration.
* - Fastest random element access.
* - Fastest creation/deletion.
* - Most efficient memory usage (after 'ShrinkWrap()').
* - Unlike std::vector, the given type does not have to be default-constructible.
* Cons:
* - Taking pointers to elements is not safe.
* - Element removal and insertion is at worst an O(n) operation.
* - Adding beyond 'Capacity()' requires reallocation of the entire Array. */
template <typename T>
struct Array final
{
	///////////////////////
	///   Information   ///
public:

	static_assert(!std::is_reference<T>::value,
		"You can't create an 'Array' of references, dumbass");

	static_assert(Operations::MoveConstruct<T>::Supported,
		"T must be move-constructible.");

	/** Array's copy-constructor is only supported if T's copy-constructor is supported. */
	static constexpr bool CopyConstructorSupported = Operations::CopyConstruct<T>::Supported;

	/** Array's copy-assignment operator is only supported it T's copy-assignment operator is supported. */
	static constexpr bool CopyAssignmentSupported = Operations::CopyAssign<T>::Supported;

	///////////////////////
	///   Inner Types   ///
public:

	/** Forward iterator for a mutable Array. */
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

	/** Forward iterator for an immutable Array. */
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

	/** Default-constructs an Array. */
	Array()
		: _value(), _numElements(0)
	{
		// All done
	}

	/** Constructs a new Array.
	* 'size' - the starting size of the array. */
	Array(uint32 size)
		: _value(size * sizeof(T)), _numElements(0)
	{
		// All done
	}

	/** Constructs a new Array by copying an existing Array. */
	Array(const Array& copy)
		: Array(copy.Size())
	{
		for (const auto& value : copy)
		{
			FastAdd(value);
		}
	}

	/** Constructs a new Array by moving an existing Array. */
	Array(Array&& move)
		: _value(std::move(move._value)), _numElements(move._numElements)
	{
		move._numElements = 0;
	}
	
	/** Constructs a new Array from a c-style array of related types. */
	template <typename RelatedT, WHERE(std::is_constructible<T, const RelatedT&>::value)>
	Array(const RelatedT cArray[], uint32 size)
		: Array(size)
	{
		for (uint32 i = 0; i < size; ++i)
		{
			FastAdd(cArray[i]);
		}
	}

	/** Constructs a new Array from an initializer-list of related types. */
	template <typename RelatedT, WHERE(std::is_constructible<T, const RelatedT&>::value)>
	Array(const std::initializer_list<RelatedT>& init)
		: Array(static_cast<uint32>(init.size()))
	{
		for (const auto& value : init)
		{
			FastAdd(value);
		}
	}

	/** Constructs a new Array from an Array of related types. */
	template <typename RelatedT, WHERE(std::is_constructible<T, const RelatedT&>::value)>
	Array(const Array<RelatedT>& copy)
		: Array(copy.Size())
	{
		for (const auto& value : copy)
		{
			FastAdd(value);
		}
	}

	/** Constructs an array from an existing array of compatible types. */
	template <typename CompatibleT, WHERE(std::is_convertible<CompatibleT*, T*>::value && sizeof(CompatibleT) == sizeof(T))>
	Array(Array<CompatibleT>&& move)
		: _value(std::move(move._value)), _numElements(move._numElements)
	{
		move._numElements = 0;
	}

	/** Destroys an Array. */
	~Array()
	{
		Clear();
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns the number of elements in this Array. */
	FORCEINLINE uint32 Size() const
	{
		return _numElements;
	}

	/** Returns the number of elements that can be put into this Array before needing to re-allocate. */
	FORCEINLINE uint32 Capacity() const
	{
		return _value.GetSize() / sizeof(T);
	}

	/** Returns whether this Array is empty. */
	FORCEINLINE bool IsEmpty() const
	{
		return Size() == 0;
	}

	/** Returns a pointer to the start of this Array. */
	FORCEINLINE T* CArray()
	{
		return reinterpret_cast<T*>(_value.GetValue());
	}

	/** Returns a pointer to the start of this Array. */
	FORCEINLINE const T* CArray() const
	{
		return reinterpret_cast<const T*>(_value.GetValue());
	}

	/** Returns whether a copy of the given value exists in this Array. */
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

	/** Appends a new element to the end of this Array, returning the new element's index. */
	template <typename RelatedT, WHERE(std::is_constructible<T, RelatedT>::value)>
	uint32 Add(RelatedT&& value)
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

		return FastAdd(std::forward<RelatedT>(value));
	}

	/** Insert the given value at the given index, returning the index of the new element
	* (which may be different from the given index). */
	template <typename RelatedT, WHERE(std::is_constructible<T, RelatedT>::value)>
	uint32 Insert(RelatedT&& value, uint32 index)
	{
		// If our insert index is beyond the size of the array
		if (index > Size())
		{
			// Add it to the end
			return Add(std::forward<RelatedT>(value));
		}

		// If the array is already full
		if (Size() >= Capacity())
		{
			Resize(Capacity() * 2);
		}

		// Move element on the end up an index
		new(CArray() + Size()) T(std::move(FastGet(Size() - 1)));

		// Move all proceeding elements up an index
		for (uint32 i = Size() - 1; i > index; --i)
		{
			FastGet(i) = std::move(FastGet(i - 1));
		}

		// Insert the value
		FastGet(index) = std::forward<RelatedT>(value);
		++_numElements;
		return index;
	}

	/** Returns a reference to the element at the given index.
	* WARNING: Make sure the index exists in this Array. */
	FORCEINLINE T& Get(uint32 index)
	{
		assert(index < Size());
		return FastGet(index);
	}

	/** Returns an immutable reference to the element at the given index.
	* WARNING: Make sure the index exists in this Array. */
	FORCEINLINE const T& Get(uint32 index) const
	{
		assert(index < Size());
		return FastGet(index);
	}

	/** Returns a reference to the first element in this Array.
	* WARNING: Check 'IsEmpty()' before calling this. */
	FORCEINLINE T& First()
	{
		assert(Size() > 0);
		return FastGet(0);
	}

	/** Returns an immutable reference to the first element in this Array.
	* WARNING: Check 'IsEmpty()' before calling this. */
	FORCEINLINE const T& First() const
	{
		assert(Size() > 0);
		return FastGet(0);
	}

	/** Returns (by value) the first element in this Array, or a default-constructed object if this Array is empty. */
	FORCEINLINE T FirstOrDefault() const
	{
		if (Size() == 0)
		{
			return T();
		}
		else
		{
			return First();
		}
	}

	/** Returns a reference to the last element in this Array.
	* WARNING: Check 'IsEmpty()' before calling this. */
	FORCEINLINE T& Last()
	{
		assert(Size() > 0);
		return FastGet(Size() - 1);
	}

	/** Returns an immutable reference to the last element in this Array.
	* WARNING: Check 'IsEmpty()' before calling this. */
	FORCEINLINE const T& Last() const
	{
		assert(Size() > 0);
		return FastGet(Size() - 1);
	}

	/** Returns (by value) the last element in this Array, or a default-constructed object if this Array is empty. */
	FORCEINLINE T LastOrDefault() const
	{
		if (Size() == 0)
		{
			return T();
		}
		else
		{
			return Last();
		}
	}
		
	/** Returns a portion of this Array from the given index to the end. */
	FORCEINLINE Array Slice(uint32 start) const
	{
		return Slice(start, Size());
	}

	/** Returns a portion of this Array, starting at the 'start' index and ending at the 'end' index. */
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

		return Array(CArray() + start, end - start);
	}

	/** Returns the indices at which a copy of the given value occurs in this Array. */
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

	/** Deletes the value stored at the specified index in this Array.
	* NOTE: This may offset the index of every proceeding element by -1. */
	void DeleteAt(uint32 index)
	{
		for (uint32 i = index; i < Size() - 1; ++i)
		{
			FastGet(i) = std::move(FastGet(i + 1));
		}
		FastGet(--_numElements).~T();
	}

	/** Deletes the first occurrence of the given value in this Array.
	* NOTE: This may offset the index of every proceeding element by -1. */
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

	/** Deletes the last occurrence of the given value in this Array.
	* NOTE: This may offset the index of every proceeding element by -1. */
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

	/** Deletes all occurrences of the specified value in this Array.
	* NOTE: This offsets the index of every proceeding element where a deletion occurs. */
	void DeleteAll(const T& value)
	{
		uint32 x = 0;

		for (uint32 i = 0; i < Size(); ++i)
		{
			// If we've found a match
			if (value == FastGet(i))
			{
				continue;
			}

			// Shift next element down
			FastGet(x++) = std::move(FastGet(i));
		}

		// Adjust size
		uint32 oldSize = _numElements;
		_numElements = x;

		// Destroy remaining elements
		for (; x < oldSize; ++x)
		{
			FastGet(x).~T();
		}
	}

	/** Extracts the value stored at the given index before deleting it.
	* WARNING: Make sure the given index exists in this Array.
	* NOTE: This offsets the index of every proceeding element by -1. */
	T RemoveAt(uint32 index)
	{
		T value = std::move(Get(index));
		DeleteAt(index);
		return value;
	}

	/** Ensures that 'Capacity' is at least as big as the value specified in 'size'. */
	void Reserve(uint32 size)
	{
		if (Capacity() < size)
		{
			Resize(size);
		}
	}

	/** Ensures that 'Capacity' is at least as big as 'Size' + 'size'. */
	void ReserveAdditional(uint32 size)
	{
		Resize(Size() + size);
	}

	/** Reallocates the internal array with more (or less) space, moving existing elements into the new array.
	* NOTE: To prevent loss of data, ensure that the given size is greater than the current size of the array. */
	void Resize(uint32 size)
	{
		auto newBuff = DynamicBuffer(size * sizeof(T));

		uint32 i;
		for (i = 0; i < size && i < Size(); ++i)
		{
			// Move all elements below 'size' into new array
			T& value = FastGet(i);
			new(newBuff.GetValueAs<T>() + i) T(std::move(value));
			value.~T();
		}

		_value = std::move(newBuff);
		_numElements = i;
	}

	/** Frees unused space in internal array, so that 'Capacity() == Size()'. */
	FORCEINLINE void ShrinkWrap()
	{
		Resize(Size());
	}

	/** Quickly deletes all values from this Array, preserving size. */
	FORCEINLINE void Clear()
	{
		for (uint32 i = 0; i < Size(); ++i)
		{
			FastGet(i).~T();
		}
		_numElements = 0;
	}

	/** Deletes all values from this Array, resetting size. */
	void Reset(uint32 size)
	{
		Clear();
		_value.Reset(size);
	}

	/* Iteration methods */
	FORCEINLINE Iterator begin()
	{
		return Iterator(CArray());
	}
	FORCEINLINE ConstIterator begin() const
	{
		return ConstIterator(CArray());
	}
	FORCEINLINE Iterator end()
	{
		return Iterator(&FastGet(Size()));
	}
	FORCEINLINE ConstIterator end() const
	{
		return ConstIterator(&FastGet(Size()));
	}

private:

	/** Returns a reference to the element at the given index.
	* WARNING: Only use this if you KNOW (algorithmically) that the index exists in this Array. */
	FORCEINLINE T& FastGet(uint32 index)
	{
		return CArray()[index];
	}

	/** Returns an immutable reference to the element at the given index.
	* WARNING: Only use this if you KNOW (algorithmically) that the index exists in this Array. */
	FORCEINLINE const T& FastGet(uint32 index) const
	{
		return CArray()[index];
	}

	/** Adds an element to the end of this Array without checking for available space.
	* Returns the index of the new element.
	* WARNING: Only use this if you KNOW (algorithmically) that there is enough space. */
	template <typename RelatedT, WHERE(std::is_constructible<T, RelatedT>::value)>
	FORCEINLINE uint32 FastAdd(RelatedT&& value)
	{
		new(CArray() + Size()) T(std::forward<RelatedT>(value));
		return _numElements++;
	}

	/////////////////////
	///   Operators   ///
public:

	FORCEINLINE T& operator[](uint32 index)
	{
		return Get(index);
	}
	FORCEINLINE const T& operator[](uint32 index) const
	{
		return Get(index);
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

	/** Copies an existing Array. */
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

	/** Moves an existing Array. */
	Array& operator=(Array&& move)
	{
		if (this != &move)
		{
			Reset(0);
			
			_value = std::move(move._value);
			_numElements = move._numElements;

			move._numElements = 0;
		}

		return self;
	}

	/** Copies an initializer-list of related types onto this Array. */
	template <typename RelatedT, WHERE(std::is_constructible<T, const RelatedT&>::value)>
	Array& operator=(const std::initializer_list<RelatedT>& init)
	{
		Reset(init.size());

		for (const auto& value : init)
		{
			FastAdd(value);
		}

		return self;
	}
	
	/** Copies an Array of related types. */
	template <typename RelatedT, WHERE(std::is_constructible<T, const RelatedT&>::value)>
	Array& operator=(const Array<RelatedT>& copy)
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

	/** Moves an Array of compatible types. */
	template <typename CompatibleT, WHERE(std::is_convertible<CompatibleT*, T*>::value && sizeof(CompatibleT) == sizeof(T))>
	Array& operator=(Array<CompatibleT>&& move)
	{
		if (this != &move)
		{
			Reset(0);
			_value = std::move(move._value);
			_numElements = move._numElements;

			move._numElements = 0;
		}

		return self;
	}

	/** Produces an Array of the concatenation of an Array and an initializer-list. */
	template <typename RelatedT, WHERE(std::is_constructible<T, const RelatedT&>::value)>
	friend Array operator+(const Array& lhs, const std::initializer_list<RelatedT>& rhs)
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

	/** Produces an Array of the concatenation of two other Arrays. */
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
	
	/** Appends an initializer-list onto an Array. */
	template <typename RelatedT, WHERE(std::is_constructible<T, const RelatedT&>::value)>
	friend Array& operator+=(Array& lhs, const std::initializer_list<RelatedT>& rhs)
	{
		lhs.ReserveAdditional(rhs.size());

		for (const auto& item : rhs)
		{
			lhs.FastAdd(item);
		}

		return lhs;
	}

	/** Appends an Array onto another Array. */
	template <typename RelatedT, WHERE(std::is_constructible<T, const RelatedT&>::value)>
	friend Array& operator+=(Array& lhs, const Array<RelatedT>& rhs)
	{
		lhs.ReserveAdditional(rhs.Size());

		for (const auto& item : rhs)
		{
			lhs.FastAdd(item);
		}

		return lhs;
	}

	/** Converts this Array to another Array by reference. */
	template <typename CompatibleT, WHERE(std::is_convertible<T*, const CompatibleT*>::value && sizeof(T) == sizeof(CompatibleT))>
	explicit operator const Array<CompatibleT>&() const
	{
		return reinterpret_cast<const Array<CompatibleT>&>(self);
	}

	////////////////
	///   Data   ///
private:
	
	DynamicBuffer _value;
	uint32 _numElements;
};
