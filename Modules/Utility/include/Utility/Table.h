// Table.h
#pragma once

#include <map>

namespace Willow
{
	template <typename KeyType, typename ValueType>
	class Table
	{
		////////////////////////
		///   Constructors   ///
	public:

		Table()
		{
			_map = new std::map<KeyType, ValueType>;
		}
		Table(const Table& copy)
		{
			delete _map;
			_map = new std::map<KeyType, ValueType>(*copy._map);
		}
		Table(Table&& other)
		{
			_map = other._map;
			other._map = nullptr;
		}
		~Table()
		{
			delete _map;
		}

		///////////////////
		///   Methods   ///
	public:

		bool HasKey(const KeyType& key)
		{
			return _map->find(key) != _map->end();
		}

		/////////////////////
		///   Operators   ///
	public:

		ValueType& operator[](const KeyType& key)
		{
			return (*_map)[key];
		}
		const ValueType& operator[](const KeyType& key) const
		{
			return (*_map)[key];
		}

		////////////////
		///   Data   ///
	private:

		std::map<KeyType, ValueType>* _map;
	};
}