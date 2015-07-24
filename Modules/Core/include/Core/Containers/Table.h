// Table.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Array.h"
#include "Pair.h"

/** An associative array, replacement for 'std::map' */
template <typename KeyT, typename ValueT>
struct Table final
{
	///////////////////////
	///   Inner Types   ///
private:

	using PairT = Pair<KeyT, ValueT>;
	using StorageType = Array<PairT>;

public:

	/** Forward iterator for a mutable Table */
	using Iterator = typename StorageType::Iterator;

	/** Forward iterator for an immutable Table */
	using ConstIterator = typename StorageType::ConstIterator;

	////////////////////////
	///   Constructors   ///
public:

	Table() = default;
	Table(const std::initializer_list<PairT>& init)
		: _values(static_cast<uint32>(init.size()))
	{
		for (const auto& value : init)
		{
			self[value.First] = value.Second;
		}
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns the number of key-value pairs in this table */
	FORCEINLINE uint32 Size() const
	{
		return _values.Size();
	}

	/** Searches for the value associated with the given key in this table */
	ValueT* Find(const KeyT& key)
	{
		for (auto& pair : _values)
		{
			if (pair.First == key)
			{
				return &pair.Second;
			}
		}

		return nullptr;
	}

	/** Searches for the value associated with the given key in this table */
	const ValueT* Find(const KeyT& key) const
	{
		for (const auto& pair : _values)
		{
			if (pair.First == key)
			{
				return &pair.Second;
			}
		}

		return nullptr;
	}

	/** Returns whether the given key-value pair exists in this Table */
	FORCEINLINE bool Contains(const Pair<KeyT, ValueT>& pair)
	{
		return _values.Contains(pair);
	}

	/** Returns whether a value associated with the given key exists in this Table */
	bool HasKey(const KeyT& key) const
	{
		for (const auto& i : _values)
		{
			if (i.First == key)
			{
				return true;
			}
		}

		return false;
	}

	/** Returns whether a key associated with the given value exists in this table */
	bool HasValue(const ValueT& value) const
	{
		for (const auto& pair : _values)
		{
			if (pair.Second == value)
			{
				return true;
			}
		}

		return false;
	}

	/** Inserts a new key-value pair, replacing the existing entry if there is a conflict */
	template <typename RelatedKeyT, typename RelatedValueT>
	void Insert(RelatedKeyT&& key, RelatedValueT&& value)
	{
		for (auto& entry : _values)
		{
			if (entry.First == key)
			{
				entry.Second = std::forward<RelatedValueT>(value);
				return;
			}
		}

		_values.Add(PairType(std::forward<RelatedKeyT>(key), std::forward<RelatedValueT>(value)));
	}

	/** Deletes all key-value pairs from the table */
	FORCEINLINE void Clear()
	{
		_values.Clear();
	}

	/* Iteration methods */
	FORCEINLINE Iterator begin()
	{
		return _values.begin();
	}
	FORCEINLINE ConstIterator begin() const
	{
		return _values.begin();
	}
	FORCEINLINE Iterator end()
	{
		return _values.end();
	}
	FORCEINLINE ConstIterator end() const
	{
		return _values.end();
	}

	/////////////////////
	///   Operators   ///
public:

	Table& operator=(const std::initializer_list<PairT>& init)
	{
		_values.Reset(init.size());

		for (const auto& value : init)
		{
			self[value.First] == value.Second;
		}
	}
	friend bool operator==(const Table& lhs, const Table& rhs)
	{
		return lhs._values == rhs._values;
	}
	friend bool operator!=(const Table& lhs, const Table& rhs)
	{
		return lhs._values != rhs._values;
	}
	
	template <typename RelatedKeyT>
	ValueT& operator[](RelatedKeyT&& key)
	{
		// Search for the key
		for (auto& i : _values)
		{
			if (i.First == key)
			{
				return i.Second;
			}
		}

		_values.Add(PairT{ std::forward<RelatedKeyT>(key) });
		return _values.Last().Second;
	}

	////////////////
	///   Data   ///
private:

	StorageType _values;
};