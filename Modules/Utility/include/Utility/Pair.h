// Pair.h
#pragma once

#include "String.h"

namespace Willow
{
	template <typename A, typename B>
	class Pair : public object
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE
		EXTENDS(object)

		//////////////////
		///   Fields   ///
	public:

		A First;
		B Second;

		////////////////////////
		///   Constructors   ///
	public:

		Pair(const A& first = A(), const B& second = B())
			: First(first), Second(second)
		{
			// All done
		}

		///////////////////
		///   Methods   ///
	public:

		/** Returns the state of this pair as a string */
		String ToString() const override
		{
			return String::Format("{@, @}", ValueToString(First), ValueToString(Second));
		}

		/////////////////////
		///   Operators   ///
	public:

		friend bool operator==(const Pair<A, B>& lhs, const Pair<A, B>& rhs)
		{
			return lhs.First == rhs.First && lhs.Second == rhs.Second;
		}
		friend bool operator!=(const Pair<A, B>& lhs, const Pair<A, B>& rhs)
		{
			return !(lhs == rhs);
		}
	};

	BEGIN_TEMPLATE_INFO(Willow::Pair, typename A, typename B)
	HAS_FACTORY
	END_REFLECTION_INFO
}