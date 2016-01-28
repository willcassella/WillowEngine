// ArchiveReader.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../config.h"
#include "../Forwards/Containers.h"
#include "../Functional/EnumeratorView.h"

/** Represents access to a node in an Archive that may have data read from it. */
class CORE_API ArchiveReader
{
	////////////////////////
	///   Constructors   ///
public:

	virtual ~ArchiveReader() = default;

	///////////////////
	///   Methods   ///
public:

	/** Returns the name of this node.
	* NOTE: Returns an empty String if this node has no name. */
	virtual String GetName() const = 0;

	/** Attempts to get a boolean value out of this node, returning whether it succeeded. */
	virtual bool GetValue(bool& value) const = 0;

	/** Attempts to get a char value out of this node, returning whether it succeeded. */
	virtual bool GetValue(char& value) const = 0;

	/** Attempts to get a byte value out of this node, returning whether it succeeded. */
	virtual bool GetValue(byte& value) const = 0;

	/** Attempts to get an int16 value out of this node, returning whether it succeeded. */
	virtual bool GetValue(int16& value) const = 0;

	/** Attempts to get a uint16 value out of this node, returning whether it succeeded. */
	virtual bool GetValue(uint16& value) const = 0;

	/** Attempts to get an int32 value out of this node, returning whether it succeeded. */
	virtual bool GetValue(int32& value) const = 0;

	/** Attempts to get a uint32 value out of this node, returning whether it succeeded. */
	virtual bool GetValue(uint32& value) const = 0;

	/** Attempts to get an int64 value out of this node, returning whether it succeeded. */
	virtual bool GetValue(int64& value) const = 0;

	/** Attempts to get a uint64 value out of this node, returning whether it succeeded. */
	virtual bool GetValue(uint64& value) const = 0;

	/** Attempts to get a float value out of this node, returning whether it succeeded. */
	virtual bool GetValue(float& value) const = 0;

	/** Attempts to get a double value out of this node, returning whether it succeeded. */
	virtual bool GetValue(double& value) const = 0;

	/** Attempts to get a long double value out of this node, returning whether it succeeded. */
	virtual bool GetValue(long double& value) const = 0;

	/** Attempts to get a String value out of this node, returning whether it succeeded. */
	virtual bool GetValue(String& value) const = 0;

	/** Iterates over all child nodes of this node. */
	virtual void EnumerateChildren(EnumeratorView<const ArchiveReader&> enumerator) const = 0;
};
