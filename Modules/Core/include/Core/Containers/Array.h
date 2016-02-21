// Array.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <new>
#include <cassert>
#include <utility>
#include <algorithm>
#include "../STDE/TypeTraits.h"
#include "../Operations/TypeOps.h"
#include "../Memory/Buffers/DynamicBuffer.h"

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

	static_assert(!std::is_reference<T>::value, "You can't create an 'Array' of references, dumbass");

	static_assert(Operations::MoveConstruct<T>::Supported, "T must be move-constructible.");

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
			return *this;
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
			return *this;
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
		: _buffer(), _numElements(0)
	{
		// All done
	}

	/** Constructs a new Array.
	* 'size' - the starting size of the array. */
	Array(std::size_t size)
		: _buffer(sizeof(T) * size), _numElements(0)
	{
		// All done
	}

	/** Constructs a new Array by copying an existing Array. */
	Array(const Array& copy)
		: Array(copy.Size())
	{
		for (const auto& value : copy)
		{
			this->FastAdd(value);
		}
	}

	/** Constructs a new Array by moving an existing Array. */
	Array(Array&& move)
		: _buffer(std::move(move._buffer)), _numElements(move._numElements)
	{
		move._numElements = 0;
	}
	
	/** Constructs a new Array by copying a C-style array. */
	template <typename F, std::size_t Size>
	Array(const F (&cArray)[Size])
		: Array(cArray, Size)
	{
		// All done
	}

	/** Constructs a new Array by copying a C-style array. */
	template <typename F>
	Array(const F cArray[], std::size_t size)
		: Array(size)
	{
		static_assert(Operations::Construct<T, const F&>::Supported, "The given C-style array cannot be used to initialize this Array.");

		for (std::size_t i = 0; i < size; ++i)
		{
			this->FastAdd(cArray[i]);
		}
	}

	/** Constructs a new Array by moving a C-style array. */
	template <typename F, std::size_t Size>
	Array(F (&&cArray)[Size])
		: Array(Size)
	{
		static_assert(Operations::Construct<T, F&&>::Supported, "The given C-style array cannot be used to intiailize this Array.");

		for (std::size_t i = 0; i < Size; ++i)
		{
			this->FastAdd(std::move(cArray[i]));
		}
	}

	/** Constructs a new Array from a std::initializer_list. */
	template <typename F>
	Array(const std::initializer_list<F>& init)
		: Array(init.size())
	{
		static_assert(Operations::Construct<T, const F&>::Supported, "The given 'std::initializer_list' cannot be used to initialize this Array.");

		for (const auto& value : init)
		{
			this->FastAdd(value);
		}
	}

	/** Constructs a new Array by copying an existing Array of different types. */
	template <typename F>
	Array(const Array<F>& copy)
		: Array(copy.Size())
	{
		static_assert(Operations::Construct<T, const F&>::Supported, "The given Array cannot be used to initialize this Array.");

		for (const auto& value : copy)
		{
			this->FastAdd(value);
		}
	}

	/** Constructs a new Array by moving an existing Array of different types. */
	template <typename F>
	Array(Array<F>&& move)
		: Array(move.Size())
	{
		static_assert(Operations::Construct<T, F&&>::Supported, "The given Array cannot be used to initialize this Array.");

		for (auto& value : move)
		{
			this->FastAdd(std::move(value));
		}
	}

	/** Destroys this Array. */
	~Array()
	{
		this->Clear();
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns the number of elements in this Array. */
	FORCEINLINE std::size_t Size() const
	{
		return _numElements;
	}

	/** Returns the number of elements that can be put into this Array before requring reallocation. */
	FORCEINLINE std::size_t Capacity() const
	{
		return _buffer.GetSize() / sizeof(T);
	}

	/** Returns whether this Array is empty. */
	FORCEINLINE bool IsEmpty() const
	{
		return this->Size() == 0;
	}

	/** Returns a pointer to the start of this Array. */
	FORCEINLINE T* CArray()
	{
		return _buffer.GetPointer<T>();
	}

	/** Returns a pointer to the start of this Array. */
	FORCEINLINE const T* CArray() const
	{
		return _buffer.GetPointer<T>();
	}

	/** Returns whether a copy of the given value exists in this Array. */
	bool Contains(const T& value)
	{
		for (const auto& element : *this)
		{
			if (element == value)
			{
				return true;
			}
		}

		return false;
	}

	/** Appends a new element to the end of this Array, returning the new element's index. */
	template <typename UT>
	std::size_t Add(UT&& value)
	{
		if (this->Size() >= this->Capacity())
		{
			if (this->IsEmpty())
			{
				this->Resize(1);
			}
			else
			{
				this->Resize(this->Capacity() * 2);
			}
		}

		return this->FastAdd(std::forward<UT>(value));
	}

	/** Insert the given value at the given index, returning the index of the new element
	* (which may be different from the given index). */
	template <typename UT>
	std::size_t Insert(UT&& value, std::size_t index)
	{
		// If our insert index is beyond the size of the array
		if (index > this->Size())
		{
			// Add it to the end
			return this->Add(std::forward<UT>(value));
		}

		// If the array is already full
		if (this->Size() >= this->Capacity())
		{
			Resize(this->Capacity() * 2);
		}

		// Move element on the end up an index
		new(this->CArray() + this->Size()) T(std::move(this->FastGet(this->Size() - 1)));

		// Move all proceeding elements up an index
		for (auto i = this->Size() - 1; i > index; --i)
		{
			this->FastGet(i) = std::move(this->FastGet(i - 1));
		}

		// Insert the value
		this->FastGet(index) = std::move(value);
		++_numElements;
		return index;
	}

	/** Returns a reference to the element at the given index.
	* WARNING: Make sure the index exists in this Array. */
	FORCEINLINE T& Get(std::size_t index)
	{
		assert(index < this->Size());
		return this->FastGet(index);
	}

	/** Returns an immutable reference to the element at the given index.
	* WARNING: Make sure the index exists in this Array. */
	FORCEINLINE const T& Get(std::size_t index) const
	{
		assert(index < this->Size());
		return this->FastGet(index);
	}

	/** Returns a reference to the first element in this Array.
	* WARNING: Check 'IsEmpty()' before calling this. */
	FORCEINLINE T& First()
	{
		return this->Get(0);
	}

	/** Returns an immutable reference to the first element in this Array.
	* WARNING: Check 'IsEmpty()' before calling this. */
	FORCEINLINE const T& First() const
	{
		return this->Get(0);
	}

	/** Returns (by value) the first element in this Array, or a default-constructed object if this Array is empty. */
	FORCEINLINE T FirstOrDefault() const
	{
		if (this->IsEmpty())
		{
			return T();
		}
		else
		{
			return this->First();
		}
	}

	/** Returns a reference to the last element in this Array.
	* WARNING: Check 'IsEmpty()' before calling this. */
	FORCEINLINE T& Last()
	{
		return this->Get(this->Size() - 1);
	}

	/** Returns an immutable reference to the last element in this Array.
	* WARNING: Check 'IsEmpty()' before calling this. */
	FORCEINLINE const T& Last() const
	{
		return this->Get(this->Size() - 1);
	}

	/** Returns (by value) the last element in this Array, or a default-constructed object if this Array is empty. */
	FORCEINLINE T LastOrDefault() const
	{
		if (this->IsEmpty())
		{
			return T();
		}
		else
		{
			return this->Last();
		}
	}
		
	/** Returns a portion of this Array from the given index to the end. */
	FORCEINLINE Array Slice(std::size_t start) const
	{
		return this->Slice(start, this->Size());
	}

	/** Returns a portion of this Array, starting at the 'start' index and ending at the 'end' index. */
	Array Slice(std::size_t start, std::size_t end) const
	{
		end = std::min(end, this->Size());

		if (start >= end)
		{
			return Array();
		}

		return Array(this->CArray() + start, end - start);
	}

	/** Returns the indices at which a copy of the given value occurs in this Array. */
	Array<std::size_t> OccurrencesOf(const T& value) const
	{
		Array<std::size_t> occurrences;

		for (std::size_t i = 0; i < this->Size(); ++i)
		{
			if (value == this->FastGet(i))
			{
				occurrences.Add(i);
			}
		}

		return occurrences;
	}

	/** Deletes the value stored at the specified index in this Array.
	* NOTE: This may offset the index of every proceeding element by -1. */
	void DeleteAt(std::size_t index)
	{
		for (auto i = index; i < this->Size() - 1; ++i)
		{
			this->FastGet(i) = std::move(this->FastGet(i + 1));
		}
		this->FastGet(--_numElements).~T();
	}

	/** Deletes the first occurrence of the given value in this Array.
	* NOTE: This may offset the index of every proceeding element by -1. */
	void DeleteFirst(const T& value)
	{
		for (std::size_t i = 0; i < this->Size(); ++i)
		{
			if (value == this->FastGet(i))
			{
				this->DeleteAt(i);
				return;
			}
		}
	}

	/** Deletes the last occurrence of the given value in this Array.
	* NOTE: This may offset the index of every proceeding element by -1. */
	void DeleteLast(const T& value)
	{
		for (auto i = this->Size(); i > 0; --i)
		{
			if (value == this->FastGet(i - 1))
			{
				this->DeleteAt(i - 1);
				return;
			}
		}
	}

	/** Deletes all occurrences of the specified value in this Array.
	* NOTE: This offsets the index of every proceeding element where a deletion occurs. */
	void DeleteAll(const T& value)
	{
		std::size_t x = 0;

		for (std::size_t i = 0; i < this->Size(); ++i)
		{
			// If we've found a match
			if (value == this->FastGet(i))
			{
				continue;
			}

			// Shift next element down
			this->FastGet(x++) = std::move(this->FastGet(i));
		}

		// Adjust size
		std::size_t oldSize = _numElements;
		_numElements = x;

		// Destroy remaining elements
		for (; x < oldSize; ++x)
		{
			this->FastGet(x).~T();
		}
	}

	/** Extracts the value stored at the given index before deleting it.
	* WARNING: Make sure the given index exists in this Array.
	* NOTE: This offsets the index of every proceeding element by -1. */
	T RemoveAt(std::size_t index)
	{
		T value = std::move(this->Get(index));
		this->DeleteAt(index);
		return value;
	}

	/** Ensures that 'Capacity' is at least as big as the value specified in 'size'. */
	void Reserve(std::size_t size)
	{
		if (this->Capacity() < size)
		{
			this->Resize(size);
		}
	}

	/** Ensures that 'Capacity' is at least as big as 'Size' + 'size'. */
	void ReserveAdditional(std::size_t size)
	{
		this->Resize(this->Size() + size);
	}

	/** Reallocates the internal array with more (or less) space, moving existing elements into the new array.
	* NOTE: To prevent loss of data, ensure that the given size is greater than the current size of the array. */
	void Resize(std::size_t size)
	{
		DynamicBuffer newBuff(size * sizeof(T));

		std::size_t i = 0;
		for (; i < size && i < this->Size(); ++i)
		{
			// Move all elements below 'size' into new array
			T& value = this->FastGet(i);
			new (newBuff.GetPointer<T>() + i) T(std::move(value));
			value.~T();
		}

		_buffer = std::move(newBuff);
		_numElements = i;
	}

	/** Frees unused space in internal array, so that 'Capacity() == Size()'. */
	FORCEINLINE void ShrinkWrap()
	{
		this->Resize(this->Size());
	}

	/** Quickly deletes all values from this Array, preserving size. */
	FORCEINLINE void Clear()
	{
		for (std::size_t i = 0; i < this->Size(); ++i)
		{
			this->FastGet(i).~T();
		}
		_numElements = 0;
	}

	/** Deletes all values from this Array, resetting size. */
	void Reset(std::size_t size)
	{
		this->Clear();
		_buffer.Reset(size);
	}

	/* Iteration methods */
	FORCEINLINE Iterator begin()
	{
		return Iterator(this->CArray());
	}
	FORCEINLINE ConstIterator begin() const
	{
		return ConstIterator(this->CArray());
	}
	FORCEINLINE Iterator end()
	{
		return Iterator(&this->FastGet(this->Size()));
	}
	FORCEINLINE ConstIterator end() const
	{
		return ConstIterator(&this->FastGet(this->Size()));
	}

private:

	/** Returns a reference to the element at the given index.
	* WARNING: Only use this if you KNOW (algorithmically) that the index exists in this Array. */
	FORCEINLINE T& FastGet(std::size_t index)
	{
		return this->CArray()[index];
	}

	/** Returns an immutable reference to the element at the given index.
	* WARNING: Only use this if you KNOW (algorithmically) that the index exists in this Array. */
	FORCEINLINE const T& FastGet(std::size_t index) const
	{
		return this->CArray()[index];
	}

	/** Adds an element to the end of this Array without checking for available space.
	* Returns the index of the new element.
	* WARNING: Only use this if you KNOW (algorithmically) that there is enough space. */
	template <typename UT>
	FORCEINLINE std::size_t FastAdd(UT&& value)
	{
		new (this->CArray() + this->Size()) T(std::forward<UT>(value));
		return _numElements++;
	}

	/////////////////////
	///   Operators   ///
public:

	FORCEINLINE T& operator[](std::size_t index)
	{
		return this->Get(index);
	}
	FORCEINLINE const T& operator[](std::size_t index) const
	{
		return this->Get(index);
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

		for (std::size_t i = 0; i < lhs.Size(); ++i)
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
			this->Reset(copy.Size());

			for (const auto& value : copy)
			{
				this->FastAdd(value);
			}
		}

		return *this;
	}

	/** Moves an existing Array. */
	Array& operator=(Array&& move)
	{
		if (this != &move)
		{
			this->Reset(0);
			
			_buffer = std::move(move._buffer);
			_numElements = move._numElements;

			move._numElements = 0;
		}

		return *this;
	}

	/** Copies an initializer-list of related types onto this Array. */
	template <typename RelatedT, WHERE(std::is_constructible<T, const RelatedT&>::value)>
	Array& operator=(const std::initializer_list<RelatedT>& init)
	{
		this->Reset(init.size());

		for (const auto& value : init)
		{
			this->FastAdd(value);
		}

		return *this;
	}
	
	/** Copies an Array of related types. */
	template <typename RelatedT, WHERE(std::is_constructible<T, const RelatedT&>::value)>
	Array& operator=(const Array<RelatedT>& copy)
	{
		if (this != &copy)
		{
			this->Reset(copy.Size());

			for (const auto& value : copy)
			{
				this->FastAdd(value);
			}
		}

		return *this;
	}

	/** Moves an Array of compatible types. */
	template <typename CompatibleT, WHERE(std::is_convertible<CompatibleT*, T*>::value && sizeof(CompatibleT) == sizeof(T))>
	Array& operator=(Array<CompatibleT>&& move)
	{
		if (this != &move)
		{
			this->Reset(0);
			_buffer = std::move(move._buffer);
			_numElements = move._numElements;

			move._numElements = 0;
		}

		return *this;
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

	////////////////
	///   Data   ///
private:
	
	DynamicBuffer _buffer;
	std::size_t _numElements;
};
