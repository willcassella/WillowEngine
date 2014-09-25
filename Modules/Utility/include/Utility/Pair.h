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
		{
			First = first;
			Second = second;
		}

		/////////////////////
		///   Operators   ///
	public:

		bool operator==(const Pair<A, B>& rhs) const
		{
			return First == rhs.First && Second == rhs.Second;
		}
		bool operator!=(const Pair<A, B>& rhs) const
		{
			return First != rhs.First && Second != rhs.Second;
		}
	};
}