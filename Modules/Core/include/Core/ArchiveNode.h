// ArchiveNode.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Forwards/Core.h"
#include "Forwards/Containers.h"

/////////////////
///   Types   ///

/** Type representing a node in an archive (assumes tree structure). */
class CORE_API ArchiveNode
{
	////////////////////////
	///   Constructors   ///
public:

	virtual ~ArchiveNode() = default;

	///////////////////
	///   Methods   ///
public:

	/** Returns the name of this node. */
	virtual String GetName() const = 0;

	/** Returns whether this node is a value node. */
	virtual bool IsValueNode() const = 0;

	/** Adds a child node to this node. */
	virtual ArchiveNode* AddChild(const String& name) = 0;

	/** Returns an array of all child nodes of this node. */
	virtual Array<const ArchiveNode*> GetChildren() const = 0;

	/** Sets the value of this node. Once the value has been set, you may not add child nodes to this node. */
	virtual void SetValue(const String& value) = 0;

	/** Gets the value of this node. Nodes that have children may not have values. */
	virtual String GetValue() const = 0;
};
