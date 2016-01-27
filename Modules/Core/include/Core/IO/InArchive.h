// InArchive.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../config.h"
#include "../Forwards/Containers.h"
#include "../Functional/EnumeratorView.h"

/** Represents an Archive that may have data retrieved from it. */
class CORE_API InArchive
{
	////////////////////////
	///   Constructors   ///
public:

	virtual ~InArchive() = default;

	///////////////////
	///   Methods   ///
public:

	/** Returns the name of this Archive.
	* NOTE: Returns an empty String if this Archive has no name. */
	virtual String GetName() const = 0;

	/** Attempts to get a boolean value out of this Archive, returning whether it succeeded. */
	virtual bool Get(bool& value) const = 0;

	/** Attempts to get a char value out of this Archive, returning whether it succeeded. */
	virtual bool Get(char& value) const = 0;

	/** Attempts to get a byte value out of this Archive, returning whether it succeeded. */
	virtual bool Get(byte& value) const = 0;

	/** Attempts to get an int16 value out of this Archive, returning whether it succeeded. */
	virtual bool Get(int16& value) const = 0;

	/** Attempts to get a uint16 value out of this Archive, returning whether it succeeded. */
	virtual bool Get(uint16& value) const = 0;

	/** Attempts to get an int32 value out of this Archive, returning whether it succeeded. */
	virtual bool Get(int32& value) const = 0;

	/** Attempts to get a uint32 value out of this Archive, returning whether it succeeded. */
	virtual bool Get(uint32& value) const = 0;

	/** Attempts to get an int64 value out of this Archive, returning whether it succeeded. */
	virtual bool Get(int64& value) const = 0;

	/** Attempts to get a uint64 value out of this Archive, returning whether it succeeded. */
	virtual bool Get(uint64& value) const = 0;

	/** Attempts to get a float value out of this Archive, returning whether it succeeded. */
	virtual bool Get(float& value) const = 0;

	/** Attempts to get a double value out of this Archive, returning whether it succeeded. */
	virtual bool Get(double& value) const = 0;

	/** Attempts to get a long double value out of this Archive, returning whether it succeeded. */
	virtual bool Get(long double& value) const = 0;

	/** Attempts to get a String value out of this Archive, returning whether it succeeded. */
	virtual bool Get(String& value) const = 0;

	/** Iterates over all child archives in the archive. */
	virtual void EnumerateChildren(EnumeratorView<const InArchive&> enumerator) const = 0;
};
