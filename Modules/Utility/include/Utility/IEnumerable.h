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

	template <typename T>
	interface IEnumerable
	{
		///////////////////
		///   Methods   ///
	public:

		virtual uint size() const = 0;
		virtual void add(T item) = 0;

		/////////////////////
		///   Operators   ///
	public:

		virtual T& operator[](uint index) = 0;
		virtual const T& operator[](uint index) const = 0;
	};
}