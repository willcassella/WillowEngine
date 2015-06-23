// Event.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../String.h"
#include "../Reflection/TypeIndex.h"
#include "../Reflection/ClassInfo.h"
#include "../Reflection/StructInfo.h"
#include "../Reflection/VoidInfo.h"

/** Abstract base for events */
class CORE_API Event : public Object
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(Object);

	////////////////////////
	///   Constructors   ///
public:

	Event(const String& name, const TypeInfo& argType)
		: _name(name), _argType(argType)
	{
		// All done
	}
	Event(const Event& copy) = delete;
	Event(Event&& move) = delete;
	~Event() = 0;

	///////////////////
	///   Methods   ///
public:

	/** Gets the name of this Event */
	FORCEINLINE const String& GetName() const &
	{
		return _name;
	}

	/** Gets the name of this Event */
	FORCEINLINE String GetName() const &&
	{
		return _name;
	}

	/** Returns the type of argument that this Event was created with */
	FORCEINLINE const TypeInfo& GetArgType() const
	{
		return _argType;
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
};

/** Force 'Event' to be abstract */
inline Event::~Event() {};

/** Template for events that have one parameter */
template <typename ArgType>
class TEvent final : public Event
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(Event);

	////////////////////////
	///   Constructors   ///
public:

	TEvent(const String& name, const ArgType& value)
		: Event(name, TypeOf(value)), _value(Copy(value))
	{
		// All done
	}
	~TEvent()
	{
		delete _value;
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns the value that this event holds */
	const ArgType& GetValue() const
	{
		return *_value;
	}

	////////////////
	///   Data   ///
private:

	ArgType* _value;
};

/** Template for events that have no parameters */
template <>
class CORE_API TEvent < void > final : public Event
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(Event);

	////////////////////////
	///   Constructors   ///
public:

	TEvent(const String& name)
		: Event(name, TypeOf<void>())
	{
		// All done
	}
};

//////////////////////
///   Reflection   ///

template <typename ArgType>
TEMPLATE_CLASS_REFLECTION(TEvent, ArgType)
.AddProperty("Value", "", &TEvent::GetValue, nullptr);
