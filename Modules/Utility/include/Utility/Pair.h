// Pair.h
#pragma once

namespace Willow
{
	template <typename A, typename B>
	class Pair
	{
		//////////////////
		///   Fields   ///
	public:

		A First;
		B Second;

		////////////////////////
		///   Constructors   ///
	public:

		Pair(A first = A(), B second = B())
			: First(first), Second(second)
		{
			// All done
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
}