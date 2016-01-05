// Table.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
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

	///////////////////////
	///   Information   ///
public:

	static constexpr bool CopyConstructorSupported = StorageType::CopyConstructorSupported;
	static constexpr bool CopyAssignmentSupported = StorageType::CopyAssignmentSupported;

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

	/** Searches for the value associated with the given key in this table, and calls the given function if it's found. 
	* Returns if the key was found and the function was called. */
	template <typename F>
	bool Find(const KeyT& key, F func)
	{
		auto value = Find(key);
		if (value)
		{
			func(*value);
			return true;
		}
		else
		{
			return false;
		}
	}

	/** Searches for the value associated with the given key in this table, and calls the given function if it's found.
	* Returns if the key was found and the function was called. */
	template <typename F>
	bool Find(const KeyT& key, F func) const
	{
		auto value = Find(key);
		if (value)
		{
			func(*value);
			return true;
		}
		else
		{
			return false;
		}
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

	/** Returns an Array of all the keys in this Table. */
	Array<KeyT> GetKeys() const
	{
		Array<KeyT> keys(_values.Size());

		for (const auto& kv : _values)
		{
			keys.Add(kv.First);
		}

		return keys;
	}

	/** Returns an Array of all the values in this Table. */
	Array<ValueT> GetValues() const
	{
		Array<ValueT> values(_values.Size());

		for (const auto& kv : _values)
		{
			values.Add(kv.Second);
		}

		return values;
	}

	/** Inserts a new key-value pair.
	* Returns a reference to the new value. 
	* WARNING: You must be sure that the given key does not already appear in the table. */
	template <typename RelatedKeyT, typename RelatedValueT>
	std::decay_t<RelatedValueT>& Insert(RelatedKeyT&& key, RelatedValueT&& value)
	{
		assert(!HasKey(key));
		auto index = _values.Add(PairT(std::forward<RelatedKeyT>(key), std::forward<RelatedValueT>(value)));
		return _values[index].Second;
	}

	/** Removes the key-value pair associated with the given key.
	* Returns whether the key-value pair was found and removed. */
	bool Remove(const KeyT& key)
	{
		for (uint32 i = 0; i < _values.Size(); ++i)
		{
			if (_values[i].First == key)
			{
				_values.DeleteAt(i);
				return true;
			}
		}

		return false;
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