// IEnumerable.h
#pragma once

#include "config.h"

namespace Willow
{
	template <typename T>
	interface Iterator
	{
		/////////////////////
		///   Operators   ///
	public:

		virtual T& operator*() const = 0;
		virtual void operator++() = 0;
		virtual void operator--() = 0;
	};

	// @TODO: Implement begin() and end()
	template <typename T>
	interface IEnumerable
	{
		///////////////////
		///   Methods   ///
	public:

		virtual size_t Size() const = 0;
		virtual void Add(T item) = 0;
		virtual T& First() = 0;
		virtual const T& First() const = 0;
		virtual T& Last() = 0;
		virtual const T& Last() const = 0;

		/////////////////////
		///   Operators   ///
	public:

		virtual T& operator[](uint32 index) = 0;
		virtual const T& operator[](uint32 index) const = 0;
	};
}