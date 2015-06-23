// EventHandler.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <functional>
#include "Event.h"

struct EventHandler final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT;

	////////////////////////
	///   Constructors   ///
public:

	/** Creates an event handler with one argument, to a mutable object */
	template <class OwnerType, typename ReturnType, typename ArgType>
	EventHandler(OwnerType* object, ReturnType (OwnerType::*handler)(ArgType))
		: _argType(TypeOf<ArgType>())
	{
		using DecayedArgType = std::decay_t<ArgType>;
		static_assert(!std::is_same<DecayedArgType&, ArgType>::value, "You cannot create an event handler which accepts a non-const reference");

		_handler = [object, handler](const Event& event)-> void
		{
			auto pEvent = static_cast<const TEvent<DecayedArgType>*>(&event);
			(object->*handler)(pEvent->GetValue());
		};
	}

	/** Creates a const event handler with one argument, to an immutable object */
	template <class OwnerType, typename ReturnType, typename ArgType>
	EventHandler(const OwnerType* object, ReturnType(OwnerType::*handler)(ArgType) const)
		: _argType(TypeOf<ArgType>())
	{
		using DecayedArgType = typename std::decay_t<ArgType>;
		static_assert(!std::is_same<DecayedArgType&, ArgType>::value, "You cannot create an event handler which accepts a non-const reference");

		_handler = [object, handler](const Event& event)-> void
		{
			auto pEvent = static_cast<const TEvent<DecayedArgType>*>(&event);
			(object->*handler)(pEvent->GetValue());
		};
	}

	/** Creates an event handler with no arguments, to a mutable object */
	template <class OwnerType, typename ReturnType>
	EventHandler(OwnerType* object, ReturnType(OwnerType::*handler)())
		: _argType(TypeOf<void>())
	{
		_handler = [object, handler](const Event& /*event*/)
			-> void
		{
			(object->*handler)();
		};
	}

	/** Creates a const event handler with no arguments, to an immutable object */
	template <class OwnerType, typename ReturnType>
	EventHandler(const OwnerType* object, ReturnType(OwnerType::*handler)() const)
		: _argType(TypeOf<void>())
	{
		_handler = [object, handler](const Event& /*event*/)-> void
		{
			(object->*handler)();
		};
	}

	/** Creates an event handler to a field */
	template <class OwnerType, typename FieldType>
	EventHandler(OwnerType* object, FieldType OwnerType::*field)
		: _argType(TypeOf<FieldType>())
	{
		static_assert(std::is_copy_assignable<FieldType>::value, "You cannot create a field handler to a non copy-assignable field");

		_handler = [object, field](const Event& event)-> void
		{
			auto pEvent = static_cast<const TEvent<FieldType>*>(&event);
			(object->*field) = pEvent->GetValue();
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

	/** Attempts to handle the given event. */
	void Handle(const Event& event) const
	{
		if (event.GetArgType().IsCastableTo(_argType))
		{
			_handler(event);
		}
	}

	////////////////
	///   Data   ///
private:

	TypeIndex _argType;
	const CompoundInfo* _ownerType;
	std::function<void(const Event&)> _handler;
};
