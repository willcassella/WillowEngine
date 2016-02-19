// Test.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <chrono>
#include "../Operations/ToString.h"
#include "../Reflection/Reflection.h"

namespace WTest
{
	/////////////////
	///   Types   ///

	/** Test context object. */
	struct CORE_API Context final
	{
		///////////////////////
		///   Inner Types   ///
	public:

		using TimePoint = std::chrono::time_point<std::chrono::system_clock>;

		////////////////////////
		///   Constructors   ///
	public:

		Context(TimePoint& endTime)
			: _endTime(endTime)
		{
			// All done
		}
		Context(const Context& copy) = delete;
		Context(Context&& move) = delete;
		~Context() = default;

		///////////////////
		///   Methods   ///
	public:

		/** Asserts that the given values are equal. */
		template <typename E, typename R>
		void AssertEquals(const E& expected, const R& result)
		{
			if (expected == result)
			{
				return;
			}
			else
			{
				this->AssertionFailure("AssertEquals", ToString(expected), ToString(result));
			}
		}

		/** Asserts that the given values are equal, with tolerance. */
		template <typename E, typename R, typename T>
		void AssertEquals(const E& expected, const R& result, const T& tolerance)
		{
			if (result + tolerance >= expected && result - tolerance <= expected)
			{
				return;
			}
			else
			{
				this->AssertionFailure("AssertEquals", Format("(@) == @, (+- @)", TypeOf(result), expected, tolerance), ToString(result));
			}
		}

		/** Assertts that the given values are inequal. */
		template <typename A, typename B>
		void AssertInequal(const A& a, const B& b)
		{
			if (a != b)
			{
				return;
			}
			else
			{
				this->AssertionFailure("AssertInequals", Format("anything but @", a), ToString(b));
			}
		}

		/** Checks if the given value passes equality comparison to 'true'. */
		template <typename T>
		void AssertTrue(const T& value)
		{
			if (value == true)
			{
				return;
			}
			else
			{
				this->AssertionFailure("AssertTrue", Format("(@) == true", TypeOf(value)), ToString(value));
			}
		}

		/** Checks if the given value passes equality comparison to 'false'. */
		template <typename T>
		void AssertFalse(const T& value)
		{
			if (value == false)
			{
				return;
			}
			else
			{
				this->AssertionFailure("AssertFalse", Format("(@) == false", TypeOf(value)), ToString(value));
			}
		}

		/** Checks if the given value passes inequality comparison to 'true'. */
		template <typename T>
		void AssertNotTrue(const T& value)
		{
			if (value != true)
			{
				return;
			}
			else
			{
				this->AssertionFailure("AssertNotTrue", Format("(@) != true", TypeOf(value)), ToString(value));
			}
		}

		/** Checks if the given value passes inequality comparion to 'false'. */
		template <typename T>
		void AssertNotFalse(const T& value)
		{
			if (value != false)
			{
				return;
			}
			else
			{
				this->AssertionFailure("AssertNotFalse", Format("(@) != false", TypeOf(value)), ToString(value));
			}
		}

		/** Checks if the given value passes equality comparison to 'nullptr'. */
		template <typename T>
		void AssertNull(const T& value)
		{
			if (value == nullptr)
			{
				return;
			}
			else
			{
				this->AssertionFailure("AssertNull", Format("(@) == nullptr", TypeOf(value)), ToString(value));
			}
		}

		template <typename T>
		void AssertNotNull(const T& value)
		{
			if (value != nullptr)
			{
				return;
			}
			else
			{
				this->AssertionFailure("AssertNotNull", Format("(@) != nullptr", TypeOf(value)), ToString(value));
			}
		}

	private:

		void AssertionFailure(CString assertion, const String& expected, const String& result);

		////////////////
		///   Data   ///
	private:

		TimePoint& _endTime;
	};

	/** Function signature for a Test. */
	using Test = void(Context&);

	/////////////////////
	///   Functions   ///

	/** Runs the given test. */
	void CORE_API RunTest(Test test, CString name);
}

//////////////////
///   Macros   ///

/** Runs the given test. */
#define RUN_TEST(T) ::WTest::RunTest(T, #T)
