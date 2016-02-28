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

	/** Maps the given ID to the given pointer. */
	virtual void MapID(std::uintptr_t, void* pointer) const = 0;

	/** Maps the ID of this node (if it has one) to the given pointer. */
	void MapID(void* pointer) const
	{
		auto id = this->GetID();

		if (id != 0)
		{
			this->MapID(id, pointer);
		}
	}

	/** Returns the ID of this node.
	* NOTE: If this node does not have an ID, this returns null.
	* NOTE: The returned pointer is identical to the pointer passed into 'SetID' when this node was written, so it may no longer be a valid pointer. */
	virtual std::uintptr_t GetID() const = 0;

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

	/** Gets a pointer value out of this node. */
	virtual void GetValue(void*& value) const = 0;

	/** Gets a typed pointer value out of this node. */
	template <typename T>
	void GetValue(T*& value) const
	{
		void* pointer = nullptr;
		this->GetValue(pointer);
		value = reinterpret_cast<T*>(pointer);
	}

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

	/** Pulls the given value from the first child node of this node with the given name. */
	template <typename T>
	bool PullValue(const String& name, T& value) const
	{
		return this->GetChild(name, [&](auto& child)
		{
			FromArchive(value, child);
		});
	}

	/** Pulls the given value from the first child node of this node with the given name, and maps its ID to the address of the given value. */
	template <typename T>
	bool PullValueWithID(const String& name, T& value) const
	{
		return this->GetChild(name, [&](auto& child)
		{
			FromArchive(child, value);
			child.MapID(&value);
		});
	}
};
