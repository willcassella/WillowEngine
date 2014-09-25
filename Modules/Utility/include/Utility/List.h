// List.h
#pragma once

#include <cassert>
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
			{
				this->Value = value;
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

			bool operator!=(const Iterator& rhs) const
			{
				return _node != rhs._node;
			}
			Iterator& operator++()
			{
				_node = _node->Next;
				return *this;
			}
			T& operator*()
			{
				return _node->Value;
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

			ConstIterator(typename List<T>::Node* node)
			{
				this->_node = node;
			}

			/////////////////////
			///   Operators   ///
		public:

			bool operator!=(const ConstIterator& rhs) const
			{
				return _node != rhs._node;
			}
			ConstIterator& operator++()
			{
				_node = _node->Next;
				return *this;
			}
			const T& operator*() const
			{
				return _node->Value;
			}

			////////////////
			///   Data   ///
		private:

			typename List<T>::Node* _node;
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

			for (const auto& i : copy)
			{
				this->Add(i);
			}
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
			this->Destroy();
		}

		///////////////////
		///   Methods   ///
	public:

		size_t Size() const
		{
			return _count;
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
				_last->Next = new Node(item, _last);
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

		//  Iteration functions
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

	private:

		void Destroy()
		{
			Node* next = _first;
			while (next != nullptr)
			{
				Node* current = next;
				next = current->Next;
				delete current;
			}

			_first = nullptr;
			_last = nullptr;
			_count = 0;
		}

		/////////////////////
		///   Operators   ///
	public:

		List<T>& operator=(const List<T>& rhs)
		{
			this->Destroy();

			for (const auto& i : rhs)
			{
				this->Add(i);
			}

			return *this;
		}
		List<T>& operator=(List<T>&& other)
		{
			if (this != &other)
			{
				this->Destroy();

				this->_first = other._first;
				this->_last = other._last;
				this->_count = other._count;

				other._first = nullptr;
				other._last = nullptr;
				other._count = 0;
			}
			return *this;
		}
		T& operator[](uint32 index)
		{
			assert(index < _count);

			Node* target = _first;
			for (uint32 i = 0; i <= index; i++)
			{
				target = target->Next;
			}

			return target->Value;
		}
		const T& operator[](uint32 index) const
		{
			assert(index < _count);

			Node* target = _first;
			for (uint32 i = 0; i <= index; i++)
			{
				target = target->Next;
			}

			return target->Value;
		}

		////////////////
		///   Data   ///
	private:

		Node* _first;
		Node* _last;
		uint32 _count;
	};
}