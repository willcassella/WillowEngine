// Vector.h
#pragma once

#include <vector>
#include "IEnumerable.h"

namespace Willow
{
	// A contigous container, implemented as a replacement for std::vector
	template <typename T>
	class Array : public IEnumerable<T>
	{
		////////////////////////
		///   Constructors   ///
	public:

		Array()
		{
			_vec = new std::vector<T>();
		}
		Array(Array<T>& copy)
		{
			_vec = new std::vector<T>(*copy._vec);
		}
		Array(Array<T>&& other)
		{
			this->_vec = other._vec;
			other._vec = nullptr;
		}
		~Array()
		{
			delete _vec;
		}

		///////////////////
		///   Methods   ///
	public:

		size_t Size() const override
		{
			return _vec->size();
		}
		void Add(T item) override
		{
			_vec->push_back(item);
		}
		T& First() override
		{
			return (*_vec)[0];
		}
		const T& First() const override
		{
			return (*_vec)[0];
		}
		T& Last() override
		{
			return (*_vec)[_vec->size() - 1];
		}
		const T& Last() const override
		{
			return (*_vec)[_vec->size() - 1];
		}

		/////////////////////
		///   Operators   ///
	public:

		Array<T>& operator=(const Array<T>& rhs)
		{
			delete _vec;
			_vec = new std::vector<T>(*rhs._vec);
			return *this;
		}
		Array<T>& operator=(Array<T>&& other)
		{
			if (this != &other)
			{
				delete _vec;
				this->_vec = other._vec;
				other._vec = nullptr;
			}
			return *this;
		}
		T& operator[](uint32 index) override
		{
			return (*_vec)[index];
		}
		const T& operator[](uint32 index) const override
		{
			return (*_vec)[index];
		}

		////////////////
		///   Data   ///
	private:

		std::vector<T>* _vec;
	};
}