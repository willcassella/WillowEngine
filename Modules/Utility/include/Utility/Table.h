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

		/** Returns the number of key-value pairs in this table */
		uint32 Size() const
		{
			return _values.Size();
		}

		/** Returns whether a value associated with key exists in this table */
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

		/** Deletes all key-value pairs from the table */
		void Clear()
		{
			_values.Clear();
		}

		/* Iteration methods */
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

		Table<KeyType, ValueType>& operator=(const Table<KeyType, ValueType>& rhs)
		{
			if (this != &rhs)
			{
				_values = rhs._values;
			}

			return This;
		}
		Table<KeyType, ValueType>& operator=(Table<KeyType, ValueType>&& other)
		{
			if (this != &other)
			{
				_values = std::move(other._values);
			}

			return This;
		}
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
			_values.Add(PairType(key));
			return _values.Last().Second;
		}
		const ValueType& operator[](const KeyType& key) const
		{
			// Search for the key
			for (const auto& i : _values)
			{
				if (i.First == key)
				{
					return i.Second;
				}
			}

			// If the program crashed here, you should have checked HasKey(), DUMBASS!
			assert(false);
			return ValueType();
		}
		friend bool operator==(const Table<KeyType, ValueType>& lhs, const Table<KeyType, ValueType>& rhs)
		{
			return lhs._values == rhs._values;
		}
		friend bool operator!=(const Table<KeyType, ValueType>& lhs, const Table<KeyType, ValueType>& rhs)
		{
			return !(lhs == rhs);
		}

		////////////////
		///   Data   ///
	private:

		StorageType _values;
	};
}