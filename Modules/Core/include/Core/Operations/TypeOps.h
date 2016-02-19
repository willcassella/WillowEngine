// TypeOps.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <type_traits>
#include "../Forwards/Operations.h"
#include "../env.h"

/** This type soley exists for types that aren't default-constructible, but still wish to be constructible for serialization porposes.
* Just implement a constructor that accepts an object of this type, and it may be serialized.
* Think of it like this:
* - A constructor configures and initializes the object all at once.
* - A constructor accepting 'DynamicInitializer' indicates that the object will be configured and initialized post-construction.
* Note that this means that you shouldn't invoke the 'DynamicInitializer' constructor directly, unless you know what you're doing. */
struct DynamicInitializer final
{
	// Nothing here
};

namespace Operations
{
	/** Constructs a type with the given arguments. */
	template <typename T, typename ... Args>
	struct Construct final
	{
		/** Executes the constructor. */
		static void Function(byte* location, Args ... args)
		{
			new(location) T(std::forward<Args>(args)...);
		}

		/** Whether the type supports being constructed with these arguments. */
		static constexpr bool Supported = std::is_constructible<T, Args...>::value;
	};

	/** Copy-constructs a type. */
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

		/** Executes the copy-constructor. */
		static void Function(byte* location, const T& copy)
		{
			new(location) T(copy);
		}

		/** Whether this type supports the copy-constructor. */
		static constexpr bool Supported = HasSupport<T>(0);
	};

	/** Move-constructs a type. */
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

		/** Executes the move-constructor. */
		static void Function(byte* location, T&& move)
		{
			new (location) T(std::move(move));
		}

		/** Whether this type supports the move-constructor. */
		static constexpr bool Supported = HasSupport<T>(0);
	};

	/** Assigns a value to the given argument. */
	template <typename T, typename Arg>
	struct Assign final
	{
		/** Executes the assignment operator. */
		static void Function(T& value, Arg arg)
		{
			value = std::forward<Arg>(arg);
		}

		/** Whether an assignment operator accepting the given arguments is supported. */
		static constexpr bool Supported = std::is_assignable<std::add_lvalue_reference_t<T>, Arg>::value;
	};

	/** Copy-assigns a value. */
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

		/** Executes the copy-assignment operator. */
		static void Function(T& value, const T& copy)
		{
			value = copy;
		}

		/** Whether this type supports the copy-assignment operator. */
		static constexpr bool Supported = HasSupport<T>(0);
	};

	/** Move-assigns a value. */
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

		/** Executes the move-assignment operator. */
		static void Function(T& value, T&& move)
		{
			value = std::move(move);
		}

		/** Whether this type supports the move-assignment operator. */
		static constexpr bool Supported = HasSupport<T>(0);
	};

	/** Destroys a value. */
	template <typename T>
	struct Destroy final
	{
		/** Executes the destructor. */
		static void Function(T& value)
		{
			value.~T();
		}

		/** Whether the destructor is supported. */
		static constexpr bool Supported = std::is_destructible<T>::value;
	};

	/** Aliases the default constructor operation. */
	template <typename T>
	using DefaultConstruct = Construct<T>;

	/** Aliases the dynamic initialization operator. */
	template <typename T>
	using DynamicInitialize = Construct<T, DynamicInitializer>;

	/** Aliases the copy constructor operation. */
	template <typename T>
	using CopyConstruct = Construct<T, const T&>;

	/** Aliases the move constructor operation. */
	template <typename T>
	using MoveConstruct = Construct<T, T&&>;

	/** Aliases the copy assignment operation. */
	template <typename T>
	using CopyAssign = Assign<T, const T&>;

	/** Aliases the move assignment operation. */
	template <typename T>
	using MoveAssign = Assign<T, T&&>;
}
