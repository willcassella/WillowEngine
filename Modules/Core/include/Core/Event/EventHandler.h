// EventHandler.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <functional>
#include "../Reflection/VoidInfo.h"
#include "Event.h"

struct EventHandler final
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
	EventHandler(OwnerT& object, ReturnT (OwnerT::*handler)(ArgT))
		: _argType(TypeOf<ArgT>())
	{
		static_assert(std::is_base_of<Object, OwnerT>::value || std::is_base_of<Interface, OwnerT>::value,
			"Only 'Object' or 'Interface' types may have event handlers.");
		static_assert(!stde::is_non_const_reference<ArgT>::value,
			"You cannot create an event handler which accepts a non-const reference");

		_handler = [&object, handler](const Event& event)-> void
		{
			auto pValue = static_cast<const ArgT*>(event.GetValue().GetValue());
			(object.*handler)(*pValue);
		};
	}

	/** Creates a const event handler with one argument, to an immutable object */
	template <class OwnerT, typename ReturnT, typename ArgT>
	EventHandler(const OwnerT& object, ReturnT(OwnerT::*handler)(ArgT) const)
		: _argType(TypeOf<ArgT>())
	{
		static_assert(std::is_base_of<Object, OwnerT>::value || std::is_base_of<Interface, OwnerT>::value,
			"Only 'Object' or 'Interface' types may have event handlers.");
		static_assert(!stde::is_non_const_reference<ArgT>::value,
			"You cannot create an event handler which accepts a non-const reference");

		_handler = [&object, handler](const Event& event)-> void
		{
			auto pValue = static_cast<const ArgT*>(event.GetValue().GetValue());
			(object.*handler)(*pValue);
		};
	}

	/** Creates an event handler with no arguments, to a mutable object */
	template <class OwnerT, typename ReturnT>
	EventHandler(OwnerT& object, ReturnT(OwnerT::*handler)())
		: _argType(TypeOf<void>())
	{
		static_assert(std::is_base_of<Object, OwnerT>::value || std::is_base_of<Interface, OwnerT>::value,
			"Only 'Object' or 'Interface' types may have event handlers.");

		_handler = [&object, handler](const Event& /*event*/)-> void
		{
			(object.*handler)();
		};
	}

	/** Creates a const event handler with no arguments, to an immutable object */
	template <class OwnerT, typename ReturnT>
	EventHandler(const OwnerT& object, ReturnT(OwnerT::*handler)() const)
		: _argType(TypeOf<void>())
	{
		static_assert(std::is_base_of<Object, OwnerT>::value || std::is_base_of<Interface, OwnerT>::value,
			"Only 'Object' or 'Interface' types may have event handlers.");

		_handler = [&object, handler](const Event& /*event*/)-> void
		{
			(object.*handler)();
		};
	}

	/** Creates an event handler to a field */
	template <class OwnerT, typename FieldT, WHERE(!std::is_function<FieldT>::value)>
	EventHandler(OwnerT& object, FieldT OwnerT::*field)
		: _argType(TypeOf<FieldT>())
	{
		static_assert(std::is_base_of<Object, OwnerT>::value || std::is_base_of<Interface, OwnerT>::value,
			"Only 'Object' or 'Interface' types may have event handlers.");
		static_assert(std::is_copy_assignable<FieldT>::value, 
			"You cannot create a field handler to a non copy-assignable field");

		_handler = [&object, field](const Event& event)-> void
		{
			auto pValue = static_cast<const FieldT*>(event.GetValue().GetValue());
			(object.*field) = *pValue;
		};
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns the type information for the type of argument this handler accepts. */
	FORCEINLINE const TypeInfo& GetArgType() const
	{
		return _argType;
	}

	/** Returns the type information for the compound that owns this handler. */
	FORCEINLINE const CompoundInfo& GetOwnerType() const
	{
		return *_ownerType;
	}

	/** Attempts to handle the given event.
	* If the given event is not compatible with this handler, does nothing. */
	void TryHandle(const Event& event) const;

private:

	/** Handles the given event without verifying whether it is compatible first.
	* WARNING: Make sure you KNOW this handler is compatible with the given event before calling this. */
	FORCEINLINE void Handle(const Event& event) const
	{
		_handler(event);
	}

	////////////////
	///   Data   ///
private:

	TypePtr<> _argType;
	const CompoundInfo* _ownerType;
	std::function<void(const Event&)> _handler;
};
