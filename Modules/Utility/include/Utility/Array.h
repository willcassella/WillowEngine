// Array.h
#pragma once

#include <cassert>
#include <utility>
#include "List.h"

namespace Willow
{
	/** A contigous container, replacement for std::vector */
	template <typename T>
	class Array
	{
		///////////////////////
		///   Information   ///
	private:

		class Iterator
		{
			////////////////////////
			///   Constructors   ///
		public:

			Iterator(T* value)
			{
				this->_value = value;
			}

			/////////////////////
			///   Operators   ///
		public:

			Iterator& operator++()
			{
				++_value;
				return This;
			}
			T& operator*()
			{
				return *_value;
			}
			friend bool operator!=(const Iterator& lhs, const Iterator& rhs)
			{
				return lhs._value != rhs._value;
			}

			////////////////
			///   Data   ///
		private:

			T* _value;
		};

		class ConstIterator
		{
			////////////////////////
			///   Constructors   ///
		public:

			ConstIterator(const T* value)
			{
				this->_value = value;
			}

			/////////////////////
			///   Operators   ///
		public:

			ConstIterator& operator++()
			{
				++_value;
				return This;
			}
			const T& operator*() const
			{
				return *_value;
			}
			friend bool operator!=(const ConstIterator& lhs, const ConstIterator& rhs)
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

		/** Constructs a new array
		size - the starting size of the array*/
		Array(uint32 size = 0)
		{
			this->_size = size;
			this->_values = new T[_size];
			this->_freeIndex = 0;
		}
		Array(const Array<T>& copy)
		{
			this->_size = 0;
			this->_freeIndex = 0;
			this->_values = nullptr;

			This = copy;
		}
		Array(Array<T>&& other)
		{
			this->_size = other._size;
			this->_values = other._values;
			this->_freeIndex = other._freeIndex;

			other._values = nullptr;
		}
		~Array()
		{
			delete[] _values;
			_size = 0;
			_freeIndex = 0;
		}

		///////////////////
		///   Methods   ///
	public:

		/** Returns the number of elements in this array */
		uint32 Size() const
		{
			return _freeIndex;
		}

		/** Returns whether this array has any elements */
		bool IsEmpty() const
		{
			return this->Size() == 0;
		}

		/** Returns whether a copy of item exists in this array */
		bool HasElement(const T& item)
		{
			for (const auto& element : This)
			{
				if (element == item)
				{
					return true;
				}
			}

			return false;
		}

		/** Appends a new item to the end of this list */
		void Add(T item)
		{
			if (_freeIndex >= _size)
			{
				if (_size == 0)
				{
					this->Resize(1);
				}
				else
				{
					this->Resize(_size * 2);
				}
			}
			_values[_freeIndex++] = std::move(item);
		}

		/** Returns a reference to the first element in this array
		* WARNING: Check IsEmpty() before calling this */
		T& First()
		{
			assert(!this->IsEmpty());
			return _values[0];
		}

		/** Returns a reference to the first element in this array
		* WARNING: Check IsEmpty() before calling this */
		const T& First() const
		{
			assert(!this->IsEmpty());
			return _values[0];
		}

		/** Returns a reference to the last element in this array
		* WARNING: Check IsEmpty() before calling this */
		T& Last()
		{
			assert(!this->IsEmpty());
			return _values[_freeIndex - 1];
		}

		/** Returns a reference to the last element in this array
		* WARNING: Check IsEmpty() before calling this */
		const T& Last() const
		{
			assert(!this->IsEmpty());
			return _values[_freeIndex - 1];
		}

		/** Returns the indices at which a copy of value occurs in this array */
		List<uint32> OccurrencesOf(const T& value) const
		{
			List<uint32> occurrences;

			for (uint32 i = 0; i < this->Size(); ++i)
			{
				if (This[i] == value)
				{
					occurrences.Add(i);
				}
			}

			return occurrences;
		}

		/** Deletes the value stored at the specified index in this array
		* WARNING: This offsets the index of every proceeding element by -1 */
		void RemoveAt(uint32 index)
		{
			if (index >= _freeIndex)
			{
				return;
			}

			for (uint32 i = index; i < _freeIndex - 1; ++i)
			{
				_values[i] = std::move(values[i] + 1);
			}

			_freeIndex--;
		}

		/** Deletes all instances of the specified value in this array
		* WARNING: This offsets the index of every proceeding element */
		void RemoveAll(const T& value)
		{
			uint32 i = 0;
			while (i < this->Size())
			{
				if (This[i] == value)
				{
					this->RemoveAt(i);
				}
				else
				{
					++i;
				}
			}
		}

		/** Deletes all values from this array, preserving size */
		void Clear()
		{
			_freeIndex = 0;
		}

		/** Deletes all values from this array, resetting size */
		void Reset(uint32 size = 0)
		{
			delete[] _values;

			_size = size;
			_values = new T[size];
			_freeIndex = 0;
		}

		/* Iteration methods */
		Iterator begin()
		{
			return Iterator(&_values[0]);
		}
		ConstIterator begin() const
		{
			return ConstIterator(&_values[0]);
		}
		Iterator end()
		{
			return Iterator(&_values[_freeIndex]);
		}
		ConstIterator end() const
		{
			return ConstIterator(&_values[_freeIndex]);
		}

	private:

		void Resize(uint32 size)
		{
			assert(size >= _size);

			T* newValues = new T[size];

			for (uint32 i = 0; i < _freeIndex; i++)
			{
				newValues[i] = std::move(_values[i]);
			}

			delete[] _values;
			_values = newValues;
			_size = size;
		}

		/////////////////////
		///   Operators   ///
	public:

		Array<T>& operator=(const Array<T>& rhs)
		{
			if (this != &rhs)
			{
				delete[] _values;
				this->_size = rhs._size;
				this->_freeIndex = rhs._freeIndex;

				this->_values = new T[_size];
				for (uint32 i = 0; i < _freeIndex; i++)
				{
					_values[i] = rhs._values[i];
				}
			}
			return This;
		}
		Array<T>& operator=(Array<T>&& other)
		{
			if (this != &other)
			{
				delete[] _values;
				this->_values = other._values;
				this->_size = other._size;
				this->_freeIndex = other._freeIndex;

				other._values = nullptr;
				other._size = 0;
				other._freeIndex = 0;
			}
			return This;
		}
		T& operator[](uint32 index)
		{
			assert(index < _freeIndex);
			return _values[index];
		}
		const T& operator[](uint32 index) const
		{
			assert(index < _freeIndex);
			return _values[index];
		}
		friend bool operator==(const Array<T>& lhs, const Array<T>& rhs)
		{
			if (lhs.Size() != rhs.Size())
			{
				return false;
			}

			for (uint32 i = 0; i < lhs.Size(); i++)
			{
				if (lhs[i] != rhs[i])
				{
					return false;
				}
			}

			return true;
		}
		friend inline bool operator!=(const Array<T>& lhs, const Array<T>& rhs)
		{
			return !(lhs == rhs);
		}

		////////////////
		///   Data   ///
	private:

		T* _values;
		uint32 _size;
		uint32 _freeIndex;
	};
}