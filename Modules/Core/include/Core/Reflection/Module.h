// Module.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Object.h"
#include "../Containers/String.h"

/** Class holding a collection of Type information, associated with a .DLL/.SO */
class CORE_API Module final : public Object
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(Object)

	////////////////////////
	///   Constructors   ///
public:

	Module(const String& name);

	///////////////////
	///   Methods   ///
public:

	/** Returns the name of this Module */
	String GetName() const;

	/** Returns the author(s) of this module */
	String GetAuthors() const;

	/** Returns the time and date this module was built */
	String GetBuildTime() const;

	/** Returns the file name of this module */
	String GetFileName() const;

	/** Searches for the type with the given name in this module
	* NOTE: returns a null pointer if the type was not found */
	const TypeInfo* FindType(const String& name) const;

	////////////////
	///   Data   ///
private:

	String _name;
	String _authors;
};