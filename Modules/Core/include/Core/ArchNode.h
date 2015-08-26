// ArchNode.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "String.h"
#include "Object.h"

/////////////////
///   Types   ///

/** Type representing a node in an archive (assumes tree structure). */
class CORE_API ArchNode : public Object
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(Object)

	////////////////////////
	///   Constructors   ///
public:

	ArchNode(String name)
		: _name(std::move(name))
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns the name of this node. */
	FORCEINLINE const String& GetName() const
	{
		return _name;
	}

	/** Adds a subnode to this node. */
	virtual ArchNode& AddNode(String name) = 0;

	/** Sets the value of this node. Once the value has been set, you may not add subnodes to this node. */
	virtual void SetValue(String value) = 0;

	////////////////
	///   Data   ///
private:

	String _name;
};
