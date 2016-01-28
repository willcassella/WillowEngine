// ArchiveWriter.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../config.h"
#include "../Forwards/Containers.h"
#include "../Functional/FunctionView.h"

/////////////////
///   Types   ///

/** Represents access to an Archive node that may have data set or pushed into it. */
class CORE_API ArchiveWriter
{
	////////////////////////
	///   Constructors   ///
public:

	virtual ~ArchiveWriter() = default;

	///////////////////
	///   Methods   ///
public:

	/** Sets the value of this node as the given boolean value. */
	virtual void SetValue(bool value) = 0;

	/** Sets the value of this node as the given char value. */
	virtual void SetValue(char value) = 0;

	/** Sets the value of this node as the given byte value. */
	virtual void SetValue(byte value) = 0;

	/** Sets the value of this node as the given int16 value. */
	virtual void SetValue(int16 value) = 0;

	/** Sets the value of this node as the given uint16 value. */
	virtual void SetValue(uint16 value) = 0;

	/** Sets the value of this node as the given int32 value.s */
	virtual void SetValue(int32 value) = 0;

	/** Sets the value of this node as the given uint32 value. */
	virtual void SetValue(uint32 value) = 0;

	/** Sets the value of this node as the given int64 value. */
	virtual void SetValue(int64 value) = 0;

	/** Sets the value of this node as the given int64 value. */
	virtual void SetValue(uint64 value) = 0;

	/** Sets the value of this node as the given float value. */
	virtual void SetValue(float value) = 0;

	/** Sets the value of this node as the given double value. */
	virtual void SetValue(double value) = 0;

	/** Sets the value of this node as the given long double value. */
	virtual void SetValue(long double value) = 0;

	/** Sets the value of this node as the given String value. */
	virtual void SetValue(const String& value) = 0;

	/** Pushes a new node with the given name into this node, and runs the given handler on that node. */
	virtual void PushHandler(FunctionView<void, ArchiveWriter&> func, const String& name) = 0;

	/** Pushes a new node with the given name into this Archive, and sets its value as the given value. */
	template <typename T>
	void PushValue(const T& value, const String& name)
	{
		this->PushHandler([&value](ArchiveWriter& writer) { ::ToArchive(value, writer); }, name);
	}
};
