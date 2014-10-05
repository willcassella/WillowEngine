// Queue.h
#pragma once

#include <cassert>
#include <utility>
#include "config.h"

namespace Willow
{
	template <typename T>
	class Queue
	{
		//////////////////////
		///   Subclasses   ///
	private:

		class Node
		{
			//////////////////
			///   Fields   ///
		public:

			T Value;
			Node* Next;

			////////////////////////
			///   Constructors   ///
		public:

			Node(T value)
				: Value(value)
			{
				// Done
			}
		};

		////////////////////////
		///   Constructors   ///
	public:

		Queue()
		{
			_first = nullptr;
			_last = nullptr;
			_count = 0;
		}
		Queue(const Queue<T>& copy)
		{
			_first = nullptr;
			_last = nullptr;
			_count = 0;

			*this = copy;
		}
		Queue(Queue<T>&& other)
		{
			this->_first = other._first;
			this->_last = other._last;
			this->_count = other._count;

			other._first = nullptr;
			other._last = nullptr;
			other._count = 0;
		}
		~Queue()
		{
			this->Destroy();
		}

		///////////////////
		///   Methods   ///
	public:

		const T& Peek() const
		{
			assert(!this->IsEmpty());
			return _first->Value;
		}
		T Pop()
		{
			assert(!this->IsEmpty());

			T value = std::move(_first->Value);
			Node* temp = _first;
			_first = _first->Next;

			delete temp;
			_count--;

			if (_count == 0)
			{
				_last = nullptr;
			}

			return value;
		}
		void Push(T item)
		{
			if (_count == 0)
			{
				_first = new Node(std::move(item));
				_last = _first;
				_count++;
			}
			else
			{
				_last->Next = new Node(std::move(item));
				_last = _last->Next;
				_count++;
			}
		}
		uint32 Size() const
		{
			return _count;
		}
		bool IsEmpty() const
		{
			return _count == 0;
		}

	private:

		void Destroy()
		{
			while (_first)
			{
				Node* temp = _first;
				_first = _first->Next;
				delete temp;
				_count--;
			}

			_last = nullptr;
		}

		/////////////////////
		///   Operators   ///
	public:

		Queue<T>& operator=(const Queue<T>& copy)
		{
			if (this != &copy)
			{
				this->Destroy();

				Node* next = copy._first;
				while (next)
				{
					this->Push(next->Value);
					next = next->Next;
				}
			}
			return *this;
		}
		Queue<T>& operator=(Queue<T>&& other)
		{
			if (this != &other)
			{
				this->Destroy();
				_first = other._first;
				_last = other._last;
				_count = other._count;

				other._first = nullptr;
				other._last = nullptr;
				other._count = 0;
			}

			return *this;
		}
		friend bool operator==(const Queue<T>& lhs, const Queue<T>& rhs)
		{
			if (lhs.Size() != rhs.Size())
			{
				return false;
			}

			Node* lhsNext = lhs._first;
			Node* rhsNext = rhs._first;

			while (lhsNext)
			{
				if (lhsNext->Value != rhsNext->Value)
				{
					return false;
				}

				lhsNext = lhsNext->Next;
				rhsNext = rhsNext->Next;
			}

			return true;
		}
		friend bool operator!=(const Queue<T>& lhs, const Queue<T>& rhs)
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