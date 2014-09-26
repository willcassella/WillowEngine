// Array.h
#pragma once

#include <cassert>
#include <utility>
#include "config.h"

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

			bool operator!=(const Iterator& rhs) const
			{
				return _value != rhs._value;
			}
			Iterator& operator++()
			{
				++_value;
				return *this;
			}
			T& operator*()
			{
				return *_value;
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

			bool operator!=(const ConstIterator& rhs) const
			{
				return _value != rhs._value;
			}
			ConstIterator& operator++()
			{
				++_value;
				return *this;
			}
			const T& operator*() const
			{
				return *_value;
			}

			////////////////
			///   Data   ///
		private:

			const T* _value;
		};

		////////////////////////
		///   Constructors   ///
	public:

		Array(uint32 size = 0)
		{
			this->_size = size;
			this->_values = new T[_size];
			this->_freeIndex = 0;
		}
		Array(const Array<T>& copy)
		{
			this->_size = copy._size;
			this->_freeIndex = copy._freeIndex;
			this->_values = new T[_size];

			for (uint32 i = 0; i < _freeIndex; i++)
			{
				_values[i] = copy._values[i];
			}
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

		uint32 Size() const
		{
			return _freeIndex;
		}
		bool IsEmpty() const
		{
			return this->Size() == 0;
		}
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
		T& First()
		{
			assert(_freeIndex > 0);
			return _values[0];
		}
		const T& First() const
		{
			assert(_freeIndex > 0);
			return _values[0];
		}
		T& Last()
		{
			assert(_freeIndex > 0);
			return _values[_freeIndex - 1];
		}
		const T& Last() const
		{
			assert(_freeIndex > 0);
			return _values[_freeIndex - 1];
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
			delete[] _values;
			this->_size = rhs._size;
			this->_freeIndex = rhs._freeIndex;

			this->_values = new T[_size];
			for (uint32 i = 0; i < _freeIndex; i++)
			{
				_values[i] = rhs._values[i];
			}

			return *this;
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
			return *this;
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
		
		// @TODO: Make this a friend operator
		bool operator==(const Array<T>& rhs) const
		{
			if (this->Size() != rhs.Size())
			{
				return false;
			}

			for (uint32 i = 0; i < this->Size(); i++)
			{
				if ((*this)[i] != rhs[i])
				{
					return false;
				}
			}

			return true;
		}
		// @TODO: Make this a friend operator
		bool operator!=(const Array<T>& rhs) const
		{
			return !(*this == rhs);
		}

		////////////////
		///   Data   ///
	private:

		T* _values;
		uint32 _size;
		uint32 _freeIndex;
	};
}