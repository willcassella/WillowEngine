// EventHandler.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <functional>
#include "../Reflection/VoidInfo.h"

struct CORE_API EventHandler final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT

	////////////////////////
	///   Constructors   ///
public:

	/** Creates an event handler with one argument, to a mutable object */
	template <class OwnerT, typename ReturnT, typename ArgT>
	EventHandler(ReturnT (OwnerT::*handler)(ArgT))
		: _arg_type{ &TypeOf<ArgT>() }, _owner_type{ &TypeOf<OwnerT>() }
	{
		EventHandler::constructor_asserts<ArgT>();

		this->_handler = [handler](void* object, const void* value)-> void
		{
			auto* pObject = static_cast<OwnerT*>(object);
			auto* pValue = static_cast<const ArgT*>(value);
			(pObject->*handler)(*pValue);
		};
	}

	/** Creates a const event handler with one argument, to an immutable object */
	template <class OwnerT, typename ReturnT, typename ArgT>
	EventHandler(ReturnT(OwnerT::*handler)(ArgT) const)
		: _arg_type{ &TypeOf<ArgT>() }, _owner_type{ &TypeOf<OwnerT>() }
	{
		EventHandler::constructor_asserts<ArgT>();

		this->_handler = [handler](void* object, const void* value)-> void
		{
			auto* pObject = static_cast<const OwnerT*>(object);
			auto* pValue = static_cast<const ArgT*>(value);
			(pObject->*handler)(*pValue);
		};
	}

	/** Creates an event handler with no arguments, to a mutable object */
	template <class OwnerT, typename ReturnT>
	EventHandler(ReturnT(OwnerT::*handler)())
		: _arg_type{ nullptr }, _owner_type{ &TypeOf<OwnerT>() }
	{
		this->_handler = [handler](void* object, const void* /*value*/)-> void
		{
			auto* pObject = static_cast<OwnerT*>(object);
			(pObject->*handler)();
		};
	}

	/** Creates a const event handler with no arguments, to an immutable object */
	template <class OwnerT, typename ReturnT>
	EventHandler(ReturnT(OwnerT::*handler)() const)
		: _arg_type{ nullptr }, _owner_type{ &TypeOf<OwnerT>() }
	{
		this->_handler = [handler](void* object, const void* /*value*/)-> void
		{
			auto* pObject = static_cast<const OwnerT*>(object);
			(pObject->*handler)();
		};
	}

	/** Creates an event handler to a field */
	template <class OwnerT, typename FieldT, WHERE(!std::is_function<FieldT>::value)>
	EventHandler(FieldT OwnerT::*field)
		: _arg_type{ TypeOf<FieldT>() }, _owner_type{ TypeOf<OwnerT>() }
	{
		EventHandler::constructor_asserts<FieldT>();

		this->_handler = [field](void* object, const void* value)-> void
		{
			auto* pObject = static_cast<OwnerT*>(object);
			auto* pValue = static_cast<const FieldT*>(value);
			(pObject->*field) = *pValue;
		};
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns whether this EventHandler accepts an argument.  */
	FORCEINLINE bool accepts_argument() const
	{
		return this->_arg_type != nullptr;
	}

	/** Returns the type information for the type of argument this handler accepts.
	* NOTE: If this EventHandler does not take an argument, this returns 'TypeOf<void>()'. */
	FORCEINLINE const TypeInfo& get_arg_type() const
	{
		if (this->_arg_type)
		{
			return *this->_arg_type;
		}
		else
		{
			return TypeOf<void>();
		}
	}

	/** Returns the type information for the class that owns this handler. */
	FORCEINLINE const CompoundInfo& get_owner_type() const
	{
		return *this->_owner_type;
	}

	/** Invokes this EventHandler.
	* NOTE: It is the caller's responsibility to ensure that 'object' and 'value' are of the proper type. */
	void invoke(void* object, const void* value) const;

private:

	template <typename ArgT>
	static constexpr void constructor_asserts()
	{
		static_assert(!stde::is_reference_to_mutable<ArgT>::value, 
			"You cannot create an event handler which accepts a non-const reference");

		static_assert(Operations::CopyConstruct<ArgT>::Supported,
			"Uncopyable types may not be used as event arguments.");

		static_assert(Operations::MoveConstruct<ArgT>::Supported,
			"Unmoveable types may not be used as event arguments.");
	}

	////////////////
	///   Data   ///
private:

	const TypeInfo* _arg_type;
	const CompoundInfo* _owner_type;
	std::function<void(void*, const void*)> _handler;
};
