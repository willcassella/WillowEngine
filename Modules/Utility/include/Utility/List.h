// List.h
#pragma once

#include <cassert>
#include <utility>
#include "config.h"

namespace Willow
{
	/** A linked list, replacement for std::list */
	template <typename T>
	class List
	{
		//////////////////////
		///   SubClasses   ///
	private:

		class Node
		{
			//////////////////
			///   Fields   ///
		public:

			Node* Next;
			Node* Prev;
			T Value;

			////////////////////////
			///   Constructors   ///
		public:

			Node(T value, Node* prev = nullptr, Node* next = nullptr)
				: Value(value)
			{
				this->Next = next;
				this->Prev = prev;
			}
		};

	public:

		class Iterator
		{
			////////////////////////
			///   Constructors   ///
		public:

			Iterator(Node* node)
			{
				this->_node = node;
			}

			/////////////////////
			///   Operators   ///
		public:

			Iterator& operator++()
			{
				_node = _node->Next;
				return *this;
			}
			T& operator*()
			{
				return _node->Value;
			}
			friend bool operator!=(const Iterator& lhs, const Iterator& rhs)
			{
				return lhs._node != rhs._node;
			}

			////////////////
			///   Data   ///
		private:

			Node* _node;
		};

		class ConstIterator
		{
			////////////////////////
			///   Constructors   ///
		public:

			ConstIterator(Node* node)
			{
				this->_node = node;
			}

			/////////////////////
			///   Operators   ///
		public:

			ConstIterator& operator++()
			{
				_node = _node->Next;
				return *this;
			}
			const T& operator*() const
			{
				return _node->Value;
			}
			friend bool operator!=(const ConstIterator& lhs, const ConstIterator& rhs)
			{
				return lhs._node != rhs._node;
			}

			////////////////
			///   Data   ///
		private:

			Node* _node;
		};

		////////////////////////
		///   Constructors   ///
	public:

		List()
		{
			this->_first = nullptr;
			this->_last = nullptr;
			_count = 0;
		}
		List(const List& copy)
		{
			this->_first = nullptr;
			this->_last = nullptr;
			this->_count = 0;

			*this = copy;
		}
		List(List&& other)
		{
			this->_first = other._first;
			this->_last = other._last;
			this->_count = other._count;

			other._first = nullptr;
			other._last = nullptr;
			other._count = 0;
		}
		~List()
		{
			this->Clear();
		}

		///////////////////
		///   Methods   ///
	public:

		uint32 Size() const
		{
			return _count;
		}
		bool IsEmpty() const
		{
			return this->Size() == 0;
		}
		bool HasElement(const T& item) const
		{
			for (const auto& i : *this)
			{
				if (i == item)
				{
					return true;
				}
			}

			return false;
		}
		void Add(T item)
		{
			if (_count == 0)
			{
				_first = new Node(item);
				_last = _first;
			}
			else
			{
				_last->Next = new Node(std::move(item), _last);
				_last = _last->Next;
			}
			_count++;
		}
		T& First()
		{
			assert(_first);
			return _first->Value;
		}
		const T& First() const
		{
			assert(_first);
			return _first->Value;
		}
		T& Last()
		{
			assert(_last);
			return _last->Value;
		}
		const T& Last() const
		{
			assert(_last);
			return _last->Value;
		}
		List<uint32> OccurrencesOf(const T& value) const
		{
			List<uint32> occurrences;

			for (uint32 i = 0; i < this->Size(); i++)
			{
				if ((*this)[i] == value)
				{
					occurrences.Add(i);
				}
			}

			return occurrences;
		}
		void RemoveAt(uint32 index)
		{
			// If this index doesn't exist
			if (index >= this->Size())
			{
				return;
			}

			Node* current = _first;
			for (uint32 i = 0; i < index; i++)
			{
				current = current->Next;
			}

			if (current->Prev)
			{
				current->Prev->Next = current->Next;
			}
			if (current->Next)
			{
				current->Next->Prev = current->Prev;
			}
			if (current == _first)
			{
				_first = current->Next;
			}
			if (current == _last)
			{
				_last = current->Prev;
			}

			delete current;
			_count--;
		}
		void RemoveAll(const T& value)
		{
			uint32 i = 0;
			while (i < this->Size())
			{
				if ((*this)[i] == value)
				{
					this->RemoveAt(i);
				}
				else
				{
					++i;
				}
			}
		}
		void Clear()
		{
			Node* next = _first;
			while (next)
			{
				Node* current = next;
				next = current->Next;
				delete current;
			}

			_first = nullptr;
			_last = nullptr;
			_count = 0;
		}

		/* Iteration methods */
		Iterator begin()
		{
			return Iterator(_first);
		}
		ConstIterator begin() const
		{
			return ConstIterator(_first);
		}
		Iterator end()
		{
			return Iterator(nullptr);
		}
		ConstIterator end() const
		{
			return ConstIterator(nullptr);
		}

		/////////////////////
		///   Operators   ///
	public:

		List<T>& operator=(const List<T>& rhs)
		{
			if (this != &rhs)
			{
				this->Clear();

				for (const auto& i : rhs)
				{
					this->Add(i);
				}
			}

			return *this;
		}
		List<T>& operator=(List<T>&& other)
		{
			if (this != &other)
			{
				this->Clear();

				_first = other._first;
				_last = other._last;
				_count = other._count;

				other._first = nullptr;
				other._last = nullptr;
				other._count = 0;
			}

			return *this;
		}
		T& operator[](uint32 index)
		{
			assert(index < this->Size());

			Node* target = _first;
			for (uint32 i = 0; i < index; i++)
			{
				target = target->Next;
			}

			return target->Value;
		}
		const T& operator[](uint32 index) const
		{
			assert(index < this->Size());

			Node* target = _first;
			for (uint32 i = 0; i < index; i++)
			{
				target = target->Next;
			}

			return target->Value;
		}
		friend bool operator==(const List<T>& lhs, const List<T>& rhs)
		{
			if (lhs.Size() != rhs.Size())
			{
				return false;
			}

			for (uint32 i = 0; i < lhs.Size(); i++)
			{
				if (lhs[i] != rhs[i])
				{
					return false;
				}
			}

			return true;
		}
		friend bool operator!=(const List<T>& lhs, const List<T>& rhs)
		{
			return !(lhs == rhs);
		}

		////////////////
		///   Data   ///
	private:

		Node* _first;
		Node* _last;
		uint32 _count;
	};
}