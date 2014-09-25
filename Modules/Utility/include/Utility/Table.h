// Table.h
#pragma once

#include <utility>
#include "List.h"
#include "Pair.h"

namespace Willow
{
	/** An associative array, replacement for std::map */
	template <typename KeyType, typename ValueType>
	class Table
	{
		///////////////////////
		///   Information   ///
	private:

		typedef Pair<KeyType, ValueType> PairType;
		typedef List<PairType> StorageType;

		////////////////////////
		///   Constructors   ///
	public:

		Table() = default;
		Table(const Table& copy)
		{
			_values = copy._values;
		}
		Table(Table&& other)
		{
			_values = std::move(other._values);
		}
		~Table() = default;

		///////////////////
		///   Methods   ///
	public:

		size_t Size() const
		{
			return _values.Size();
		}
		bool HasKey(const KeyType& key) const
		{
			// Search for the key
			for (const auto& i : _values)
			{
				if (i.First == key)
				{
					return true;
				}
			}

			// The key must not have been found
			return false;
		}

		// Iteration methods
		typename StorageType::Iterator begin()
		{
			return _values.begin();
		}
		typename StorageType::ConstIterator begin() const
		{
			return _values.begin();
		}
		typename StorageType::Iterator end()
		{
			return _values.end();
		}
		typename StorageType::ConstIterator end() const
		{
			return _values.end();
		}

		/////////////////////
		///   Operators   ///
	public:

		ValueType& operator[](const KeyType& key)
		{
			// Search for the key
			for (auto& i : _values)
			{
				if (i.First == key)
				{
					return i.Second;
				}
			}

			// The key must not have been found, create new pair
			_values.Add(PairType(key, ValueType()));
			return _values.Last().Second;
		}

		////////////////
		///   Data   ///
	private:

		StorageType _values;
	};
}