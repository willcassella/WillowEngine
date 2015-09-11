// Event.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../String.h"
#include "../Memory/UniquePtr.h"
#include "../Reflection/Variant.h"

/** Abstract base for events */
struct CORE_API Event final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT

	////////////////////////
	///   Constructors   ///
public:

	/** Constructs an Event that has no value. */
	Event(String name);

	Event(const Event& copy) = delete;
	Event(Event&& move) = default;

	/** Constructs an Event that has the given value. */
	template <typename T>
	Event(String name, T&& value)
		: _name(std::move(name))
	{
		_value = New<std::decay_t<T>>(std::forward<T>(value));
	}

	///////////////////
	///   Methods   ///
public:

	/** Gets the name of this Event */
	FORCEINLINE const String& GetName() const
	{
		return _name;
	}

	/** Returns the type of argument that this Event was created with. */
	FORCEINLINE const TypeInfo& GetArgType() const
	{
		return (*_value).GetType();
	}

	/** Returns the value of this event. */
	FORCEINLINE ImmutableVariant GetValue() const
	{
		return *_value;
	}

	/////////////////////
	///   Operators   ///
public:

	Event& operator=(const Event& copy) = delete;
	Event& operator=(Event&& move) = default;

	////////////////
	///   Data   ///
private:

	String _name;
	UniquePtr<void> _value;
};
