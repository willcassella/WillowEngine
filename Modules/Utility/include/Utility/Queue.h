// Queue.h
#pragma once

#include <cassert>
#include <utility>
#include "Reflection\Reflection.h"

namespace Willow
{
	template <typename T>
	class Queue : public object
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE
		EXTENDS(object)

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

			This = copy;
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
			this->Clear();
		}

		///////////////////
		///   Methods   ///
	public:

		/** Returns the number of elements in this queue */
		uint32 Size() const
		{
			return _count;
		}

		/** Returns whether there are no elements in this queue */
		bool IsEmpty() const
		{
			return this->Size() == 0;
		}

		/** Returns a const reference to the first item in this queue
		* WARNING: Check IsEmpty() first */
		const T& Peek() const
		{
			assert(_first);
			return _first->Value;
		}

		/** Adds a new item to the end of this queue */
		void Push(T item)
		{
			if (_count == 0)
			{
				_first = new Node(std::move(item));
				_last = _first;
			}
			else
			{
				_last->Next = new Node(std::move(item));
				_last = _last->Next;
			}

			++_count;
		}

		/** Removes the first item in this queue
		WARNING: Check IsEmpty() first */
		T Pop()
		{
			assert(_first);

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

		/** Removes all elements in this queue */
		void Clear()
		{
			while (_first)
			{
				Node* temp = _first;
				_first = _first->Next;
				delete temp;
				--_count;
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
				this->Clear();

				Node* next = copy._first;
				while (next)
				{
					this->Push(next->Value);
					next = next->Next;
				}
			}
			
			return This;
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

			return This;
		}
		friend bool operator==(const Queue<T>& lhs, const Queue<T>& rhs)
		{
			if (lhs.Size() != rhs.Size())
			{
				return false;
			}

			Node* lhsNext = lhs._first;
			Node* rhsNext = rhs._first;

			while (lhsNext && rhsNext)
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

	BEGIN_TEMPLATE_INFO(Willow::Queue, typename T)
	HAS_FACTORY
	END_REFLECTION_INFO
}