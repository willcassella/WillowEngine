// ArchiveWriter.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../config.h"
#include "../Forwards/Operations.h"
#include "../Functional/FunctionView.h"
#include "../Containers/String.h"

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

	/** Sets the ref ID of this node to the value of the given pointer. */
	virtual void SetRefID(const void* refID) = 0;

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

	/** Sets the value of this node as the given c-style string value. */
	virtual void SetValue(const char* value) = 0;

	/** Sets the value of this node as the given c-style string value. */
	void SetValue(char* value)
	{
		this->SetValue(static_cast<const char*>(value));
	}

	/** Sets the value of this node as the given String value. */
	void SetValue(const String& value)
	{
		this->SetValue(value.Cstr());
	}

	/** Sets the value of this node to null. */
	virtual void SetValue(std::nullptr_t) = 0;

	/** Sets the value of this node as the given pointer. */
	virtual void SetValue(const void* value) = 0;

	/** Adds a new node with the given name as a child of this node, and runs the given function on that node. */
	virtual void AddChild(const String& name, FunctionView<void, ArchiveWriter&> function) = 0;

	/** Pushes a new node with the given name into this Archive, and serializes the given value to that node. */
	template <typename T>
	void PushValue(const String& name, const T& value)
	{
		this->AddChild(name, [&](auto& writer)
		{
			ToArchive(value, writer);
		});
	}

	/** Pushes a new node with the given name into this Archive, and sets its RefID to the address of the given value, as well as serializes
	* the given value to that node. */
	template <typename T>
	void PushReferencedValue(const String& name, const T& value)
	{
		this->AddChild(name, [&](auto& writer)
		{
			ToArchive(value, writer);
			writer.SetRefID(&value);
		});
	}
};
