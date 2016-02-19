// ArchiveReader.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../config.h"
#include "../Forwards/Containers.h"
#include "../Functional/FunctionView.h"
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

	/** Returns the name of this node. */
	virtual String GetName() const = 0;

	/** Gets a boolean value out of this node. */
	virtual void GetValue(bool& value) const = 0;

	/** Gets a char value out of this node. */
	virtual void GetValue(char& value) const = 0;

	/** Gets a byte value out of this node. */
	virtual void GetValue(byte& value) const = 0;

	/** Gets an int16 value out of this node. */
	virtual void GetValue(int16& value) const = 0;

	/** Gets a uint16 value out of this node. */
	virtual void GetValue(uint16& value) const = 0;

	/** Gets an int32 value out of this node. */
	virtual void GetValue(int32& value) const = 0;

	/** Gets a uint32 value out of this node. */
	virtual void GetValue(uint32& value) const = 0;

	/** Gets a int64 value out of this node. */
	virtual void GetValue(int64& value) const = 0;

	/** Gets a uint64 value out of this node. */
	virtual void GetValue(uint64& value) const = 0;

	/** Gets a float value out of this node. */
	virtual void GetValue(float& value) const = 0;

	/** Gets a double value out of this node. */
	virtual void GetValue(double& value) const = 0;

	/** Gets a long double value out of this node. */
	virtual void GetValue(long double& value) const = 0;

	/** Gets a String value out of this node. */
	virtual void GetValue(String& value) const = 0;

	/** Returns whether the value of this node is null. */
	virtual bool IsNull() const = 0;

	/** Calls the given function on the first child of this node, if it exists.
	* Returns 'false' if this node does not have any children. 
	* NOTE: This is equivelant to calling "GetChild(0, function)". */
	virtual bool GetFirstChild(FunctionView<void, const ArchiveReader&> function) const = 0;

	/** Calls the given function on the zero-based index of the children of this node, if it exists.
	* Returns 'false' if the indexed node does not exists. */
	virtual bool GetChild(uint32 index, FunctionView<void, const ArchiveReader&> function) const = 0;

	/** Searches for the first child node of this node with the given name.
	* Calls the given function if the node was found, and returns 'true'.
	* Returns 'false' if the node was not found. */
	virtual bool GetChild(const String& name, FunctionView<void, const ArchiveReader&> function) const = 0;

	/** Iterates over all child nodes of this node. */
	virtual void EnumerateChildren(const EnumeratorView<const ArchiveReader&>& enumerator) const = 0;

	/** Iterates over all child nodes of this node with the given name. */
	virtual void EnumerateChildren(const String& name, const EnumeratorView<const ArchiveReader&>& reader) const = 0;
};
