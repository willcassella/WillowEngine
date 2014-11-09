// Stack.h
#pragma once

#include <cassert>
#include <utility>
#include "Reflection\Reflection.h"

namespace Willow
{
	template <typename T>
	class Stack : public object
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
				// All done
			}
		};

		////////////////////////
		///   Constructors   ///
	public:

		Stack()
		{
			this->_first = nullptr;
			this->_last = nullptr;
			this->_count = 0;
		}
		Stack(const Stack<T>& copy)
		{
			this->_first = nullptr;
			this->_last = nullptr;
			this->_count = 0;

			This = copy;
		}
		Stack(Stack<T>&& other)
		{
			this->_first = other._first;
			this->_last = other._last;
			this->_count = other._count;

			other._first = nullptr;
			other._last = nullptr;
			other._count = 0;
		}
		~Stack()
		{
			this->Clear();
		}

		///////////////////
		///   Methods   ///
	public:

		/** Returns the number of elements in this stack */
		uint32 Size() const
		{
			return _count;
		}

		/** Returns whether there are no elements in this stack */
		bool IsEmpty() const
		{
			return this->Size() == 0;
		}

		/** Returns a const reference to the first item in this stack
		* WARNING: Check IsEmpty() first */
		const T& Peek() const
		{
			assert(_first);
			return _first->Value;
		}

		/** Adds a new item to the end of this stack */
		void Push(T item)
		{
			if (_count == 0)
			{
				_first = new Node(std::move(item));
				_last = _first;
			}
			else
			{
				Node* next = _first;
				_first = new Node(std::move(item));
				_first->Next = next;
			}

			++_count;
		}

		/** Removes the first item in this stack
		WARNING: Check IsEmpty() first */
		T Pop()
		{
			assert(_first);

			T value = std::move(_first->Value);

			Node* temp = _first;
			_first = _first->Next;
			delete temp;
			--_count;

			if (_count == 0)
			{
				_last = nullptr;
			}

			return value;
		}

		/** Removes all elements in this stack */
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

		Stack<T>& operator=(const Stack<T>& copy)
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
		Stack<T>& operator=(Stack<T>&& other)
		{
			if (this != &other)
			{
				this->Clear();

				this->_first = other._first;
				this->_last = other._last;
				this->_count = other._count;

				other._first = nullptr;
				other._last = nullptr;
				other._count = 0;
			}

			return This;
		}
		friend bool operator==(const Stack<T>& lhs, const Stack<T>& rhs)
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
		friend inline bool operator!=(const Stack<T>& lhs, const Stack<T>& rhs)
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

	BEGIN_TEMPLATE_INFO(Willow::Stack, typename T)
	HAS_FACTORY
	END_REFLECTION_INFO
}