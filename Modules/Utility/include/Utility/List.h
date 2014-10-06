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
				return This;
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
				return This;
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

			This = copy;
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

		/** Returns the number of elements in this list */
		uint32 Size() const
		{
			return _count;
		}

		/** Returns whether this list has any elements */
		bool IsEmpty() const
		{
			return this->Size() == 0;
		}

		/** Returns whether a copy of item exists in this list */
		bool HasElement(const T& item) const
		{
			for (const auto& i : This)
			{
				if (i == item)
				{
					return true;
				}
			}

			return false;
		}

		/** Appends a new item to the end of this list */
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

		/** Returns a reference to the first element in this list 
		* WARNING: Check IsEmpty() before calling this */
		T& First()
		{
			assert(_first);
			return _first->Value;
		}

		/** Returns a reference to the first element in this list
		* WARNING: Check IsEmpty() before calling this */
		const T& First() const
		{
			assert(_first);
			return _first->Value;
		}

		/** Returns a reference to the last element in this list
		* WARNING: Check IsEmpty() before calling this */
		T& Last()
		{
			assert(_last);
			return _last->Value;
		}

		/** Returns a reference to the last element in this list
		* WARNING: Check IsEmpty() before calling this */
		const T& Last() const
		{
			assert(_last);
			return _last->Value;
		}

		/** Returns the indices at which a copy of value occurs in this list */
		List<uint32> OccurrencesOf(const T& value) const
		{
			List<uint32> occurrences;

			for (uint32 i = 0; i < this->Size(); i++)
			{
				if (This[i] == value)
				{
					occurrences.Add(i);
				}
			}

			return occurrences;
		}

		/** Deletes the value stored at the specified index in this list
		* WARNING: This offsets the index of every proceeding element by -1 */
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

		/** Deletes all instances of the specified value in this list
		* WARNING: This offsets the index of every proceeding element */
		void RemoveAll(const T& value)
		{
			uint32 i = 0;
			while (i < this->Size())
			{
				if (This[i] == value)
				{
					this->RemoveAt(i);
				}
				else
				{
					++i;
				}
			}
		}

		/** Deletes all values in this list */
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

			return This;
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

			return This;
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