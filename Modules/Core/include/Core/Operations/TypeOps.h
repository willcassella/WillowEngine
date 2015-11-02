// TypeOps.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../STDExt/TypeTraits.h"
#include "../Forwards/Operations.h"
#include "../config.h"

namespace Operations
{
	/** Conditionally constructs a type, if a constructor accepting the given arguments is supported. */
	template <typename T, typename ... Args>
	struct Construct final
	{
	private:

		/** Case for if the type IS constructible with the given arguments. */
		template <typename F>
		FORCEINLINE static void Impl(std::true_type, byte* location, Args&& ... args)
		{
			new(location) F(std::forward<Args>(args)...);
		}

		/** Case for if the type IS NOT constructible with the given arguments. */
		template <typename F>
		FORCEINLINE static void Impl(std::false_type, byte* /*location*/, Args&& ... /*args*/)
		{
			// Do nothing
		}

	public:

		/** Conditionally executes the constructor. */
		FORCEINLINE static void Function(byte* location, Args ... args)
		{
			// Determine which implementation to use.
			// Unfortunatly, I can't use 'stdEXT::conditionally_execute', because the type being constructed cannot be deduced from 'Args' alone.
			Impl<T>(stdEXT::bool_constant<Supported>{}, location, std::forward<Args>(args)...);
		}

		/** Whether the type supports being constructed with these arguments. */
		static constexpr bool Supported = std::is_constructible<T, Args...>::value;
	};

	/** Conditionally copy-constructs a type, if the copy-constructor is supported. */
	template <typename T>
	struct Construct < T, const T& > final
	{
	private:

		/** This allows the type to explicitly declare whether it is copy-constructible (for cases where 'std::is_copy_constructible' fails).
		* Simply use the static boolean constant 'CopyConstructorSupported' on your class, and this will detect it. */
		template <typename F>
		static constexpr auto HasSupport(Implementation::Preferred) -> decltype(F::CopyConstructorSupported)
		{
			static_assert(std::is_same<const bool, decltype(F::CopyConstructorSupported)>::value,
				"The 'CopyConstructorSupported' class tag must be a boolean constant.");

			return F::CopyConstructorSupported;
		}

		/** If the type has not explicitly declared support for the copy-constructor, then this falls back to 'std::is_copy_constructible'. */
		template <typename F>
		static constexpr auto HasSupport(Implementation::Fallback) -> bool
		{
			return std::is_copy_constructible<F>::value;
		}

	public:

		/** Conditionally executes the copy-constructor. */
		FORCEINLINE static void Function(byte* location, const T& copy)
		{
			auto function = [location](const auto& c)
			{
				using F = std::decay_t<decltype(c)>;
				new(location) F(c);
			};

			stdEXT::conditionally_execute<Supported>(function, copy);
		}

		/** Whether this type supports the copy-constructor. */
		static constexpr bool Supported = HasSupport<T>(0);
	};

	/** Conditionally move-constructs a type, if the move-constructor is supported. */
	template <typename T>
	struct Construct < T, T&& > final
	{
	private:

		/** This allows the type to explicitly declare whether it is move-constructible (for cases where 'std::is_move_constructible' fails).
		* Simply use the static boolean constant 'MoveConstructorSupported' on your class, and this will detect it. */
		template <typename F>
		static constexpr auto HasSupport(Implementation::Preferred) -> decltype(F::MoveConstructorSupported)
		{
			static_assert(std::is_same<const bool, decltype(F::MoveConstructorSupported)>::value,
				"The 'MoveConstructorSupported' class tag must be a boolean constant.");

			return F::MoveConstructorSupported;
		}

		/** If the type has not explicitly declared support for the move-constructor, then this falls back to 'std::is_move_constructible'. */
		template <typename F>
		static constexpr auto HasSupport(Implementation::Fallback) -> bool
		{
			return std::is_move_constructible<F>::value;
		}

	public:

		/** Conditionally executes the move-constructor. */
		FORCEINLINE static void Function(byte* location, T&& move)
		{
			auto function = [location](auto&& m)
			{
				using F = std::decay_t<decltype(m)>;
				new (location) F(std::move(m));
			};

			stdEXT::conditionally_execute<Supported>(function, std::move(move));
		}

		/** Whether this type supports the move-constructor. */
		static constexpr bool Supported = HasSupport<T>(0);
	};

	/** Conditionally assigns to a value, if an assignment operator accepting the given argument is supported. */
	template <typename T, typename Arg>
	struct Assign final
	{
		/** Conditionally executes the assignment operator. */
		FORCEINLINE static void Function(T& value, Arg arg)
		{
			auto function = [](auto& v, Arg a)
			{
				v = std::forward<Arg>(a);
			};

			stdEXT::conditionally_execute<Supported>(function, value, std::forward<Arg>(arg));
		}

		/** Whether an assignment operator accepting the given arguments is supported. */
		static constexpr bool Supported = std::is_assignable<std::add_lvalue_reference_t<T>, Arg>::value;
	};

	/** Conditionally copy-assigns a value, if the copy-assignment operator is supported. */
	template <typename T>
	struct Assign < T, const T& > final
	{
	private:

		/** This allows the type to explicitly declare whether it is copy-assignable (for cases where 'std::is_copy_assignable' fails).
		* Simply use the static boolean constant 'CopyAssignmentSupported' on your class, and this will detect it. */
		template <typename F>
		static constexpr auto HasSupport(Implementation::Preferred) -> decltype(F::CopyAssignmentSupported)
		{
			static_assert(std::is_same<const bool, decltype(F::CopyAssignmentSupported)>::value,
				"The 'CopyAssignmentSupported' class tag must be a boolean constant.");

			return F::CopyAssignmentSupported;
		}

		/** If the type has not explicitly declared support for the copy-assignment operator, then this falls back to 'std::is_copy_assignable'. */
		template <typename F>
		static constexpr auto HasSupport(Implementation::Fallback) -> bool
		{
			return std::is_copy_assignable<F>::value;
		}

	public:

		/** Conditionally executes the copy-assignment operator. */
		FORCEINLINE static void Function(T& value, const T& copy)
		{
			auto function = [&value](const auto& c)
			{
				value = c;
			};

			stdEXT::conditionally_execute<Supported>(function, copy);
		}

		/** Whether this type supports the copy-assignment operator. */
		static constexpr bool Supported = HasSupport<T>(0);
	};

	/** Conditionally move-assigns a value, if the move-assignment operator is supported. */
	template <typename T>
	struct Assign < T, T&& > final
	{
	private:

		/** This allows the type to explicitly declare whether it is move-assignable (for cases where 'std::is_move_assignable' fails).
		* Simply use the static boolean constant 'MoveAssignmentSupported' on your class, and this will detect it. */
		template <typename F>
		static constexpr auto HasSupport(Implementation::Preferred) -> decltype(F::MoveAssignmentSupported)
		{
			static_assert(std::is_same<const bool, decltype(F::MoveAssignmentSupported)>::value,
				"The 'MoveAssignmentSupported' class tag must be a boolean constant.");

			return F::MoveAssignmentSupported;
		}

		/** If the type has not explicitly declared support for the move-assignment operator, then this falls back to 'std::is_move_assignable'. */
		template <typename F>
		static constexpr auto HasSupport(Implementation::Fallback) -> bool
		{
			return std::is_move_assignable<F>::value;
		}

	public:

		/** Conditionally executes the move-assignment operator. */
		FORCEINLINE static void Function(T& value, T&& move)
		{
			auto function = [&value](auto&& m)
			{
				value = std::move(m);
			};

			stdEXT::conditionally_execute<Supported>(function, std::move(move));
		}

		/** Whether this type supports the move-assignment operator. */
		static constexpr bool Supported = HasSupport<T>(0);
	};

	/** Conditionally destroys a value, if the destructor is supported. */
	template <typename T>
	struct Destroy final
	{
		/** Conditionally executes the destructor. */
		FORCEINLINE static void Function(T& value)
		{
			auto function = [](auto& v)
			{
				using F = std::decay_t<decltype(v)>;
				v.~F();
			};

			stdEXT::conditionally_execute<Supported>(function, value);
		}

		/** Whether the destructor is supported. */
		static constexpr bool Supported = std::is_destructible<T>::value;
	};
}
