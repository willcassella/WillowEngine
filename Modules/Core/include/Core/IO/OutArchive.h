// OutArchive.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../config.h"
#include "../Forwards/Containers.h"
#include "../Functional/FunctionView.h"

/////////////////
///   Types   ///

/** Represents an archive that may have data set or pushed into it. */
class CORE_API OutArchive
{
	////////////////////////
	///   Constructors   ///
public:

	virtual ~OutArchive() = default;

	///////////////////
	///   Methods   ///
public:

	/** Sets the value of this Archive as the given boolean value. */
	virtual void Set(bool value) = 0;

	/** Sets the value of this Archive as the given char value. */
	virtual void Set(char value) = 0;

	/** Sets the value of this Archive as the given byte value. */
	virtual void Set(byte value) = 0;

	/** Sets the value of this Archive as the given int16 value. */
	virtual void Set(int16 value) = 0;

	/** Sets the value of this Archive as the given uint16 value. */
	virtual void Set(uint16 value) = 0;

	/** Sets the value of this Archive as the given int32 value.s */
	virtual void Set(int32 value) = 0;

	/** Sets the value of this Archive as the given uint32 value. */
	virtual void Set(uint32 value) = 0;

	/** Sets the value of this Archive as the given int64 value. */
	virtual void Set(int64 value) = 0;

	/** Sets the value of this Archive as the given int64 value. */
	virtual void Set(uint64 value) = 0;

	/** Sets the value of this Archive as the given float value. */
	virtual void Set(float value) = 0;

	/** Sets the value of this Archive as the given double value. */
	virtual void Set(double value) = 0;

	/** Sets the value of this Archive as the given long double value. */
	virtual void Set(long double value) = 0;

	/** Sets the value of this Archive as the given String value. */
	virtual void Set(const String& value) = 0;

	/** Pushes a new sub-archive with the given name into this Archive, and sets its value as the given bool value. */
	virtual void Push(bool value, const String& name) = 0;

	/** Pushes a new sub-archive with the given name into this Archive, and sets its value as the given char value. */
	virtual void Push(char value, const String& name) = 0;
	
	/** Pushes a new sub-archive with the given name into this Archive, and sets its value as the given byte value. */
	virtual void Push(byte value, const String& name) = 0;

	/** Pushes a new sub-archive with the given name into this Archive, and sets its value as the given int16 value. */
	virtual void Push(int16 value, const String& name) = 0;

	/** Pushes a new sub-archive with the given name into this Archive, and sets its value as the given uint16 value. */
	virtual void Push(uint16 value, const String& name) = 0;

	/** Pushes a new sub-archive with the given name into this Archive, and sets its value as the given int32 value. */
	virtual void Push(int32 value, const String& name) = 0;

	/** Pushes a new sub-archive with the given name into this Archive, and sets its value as the given uint32 value. */
	virtual void Push(uint32 value, const String& name) = 0;

	/** Pushes a new sub-archive with the given name into this Archive, and sets its value as the given int64 value. */
	virtual void Push(int64 value, const String& name) = 0;

	/** Pushes a new sub-archive with the given name into this Archive, and sets its value as the given uint64 value. */
	virtual void Push(uint64 value, const String& name) = 0;

	/** Pushes a new sub-archive with the given name into this Archive, and sets its value as the given float value. */
	virtual void Push(float value, const String& name) = 0;

	/** Pushes a new sub-archive with the given name into this Archive, and sets its value as the given double value. */
	virtual void Push(double value, const String& name) = 0;

	/** Pushes a new sub-archive with the given name into this Archive, and sets its value as the given long double value. */
	virtual void Push(long double value, const String& name) = 0;

	/** Pushes a new sub-archive with the given name into this Archive, and sets its value as the given String value. */
	virtual void Push(const String& value, const String& name) = 0;

	/** Pushes a new sub-archive with the given name into this Archive, and runs the given handler on that archive. */
	virtual void PushHandler(FunctionView<void, OutArchive&> func, const String& name) = 0;

	/** Pushes a new sub-archive with the given name into this Archive, and sets its value as the given bool value. */
	template <typename T>
	void Push(const T& value, const String& name)
	{
		this->PushHandler([&value](OutArchive& archive) { ToArchive(value, archive); }, name);
	}
};
