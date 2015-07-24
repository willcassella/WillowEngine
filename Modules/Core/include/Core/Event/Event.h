// Event.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Memory/OwnerPtr.h"
#include "../String.h"
#include "../Reflection/Variant.h"

/** Abstract base for events */
struct CORE_API Event final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT;

	////////////////////////
	///   Constructors   ///
public:

	/** Constructs an Event that has no value. */
	Event(const String& name);

	Event(const Event& copy) = delete;
	Event(Event&& move) = default;

	template <typename T>
	Event(const String& name, T&& value)
		: _name(name), _argType(TypeOf<T>())
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
		return _argType;
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
	Event& operator=(Event&& move) = delete;

	////////////////
	///   Data   ///
private:

	String _name;
	TypeIndex _argType;
	OwnerPtr<void> _value;
};
