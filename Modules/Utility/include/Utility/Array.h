// Vector.h
#pragma once

#include <vector>
#include "IEnumerable.h"

namespace Willow
{
	// A contigous container, implimented as a replacement for std::vector
	template <typename T>
	class Array : public IEnumerable<T>
	{
		////////////////////////
		///   Constructors   ///
	public:

		Array()
		{
			vec = new std::vector<T>();
		}

		~Array()
		{
			delete vec;
		}

		///////////////////
		///   Methods   ///
	public:

		uint size() const override
		{
			return (uint)vec->size();
		}

		void add(T item) override
		{
			vec->push_back(item);
		}

		/////////////////////
		///   Operators   ///
	public:

		T& operator[](uint index) override
		{
			return (*vec)[index];
		}

		const T& operator[](uint index) const override
		{
			return (*vec)[index];
		}

		////////////////
		///   Data   ///
	private:

		std::vector<T>* vec;
	};
}