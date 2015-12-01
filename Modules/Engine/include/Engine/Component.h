// Component.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Memory/UniquePtr.h>
#include "Forwards/Engine.h"
#include "Transform.h"

/////////////////
///   Types   ///

class ENGINE_API Component : public Object
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(Object)
	friend GameObject;
	friend Scene;

	///////////////////////
	///   Inner Types   ///
public:

	/** The type of ID for components. */
	using ID = uint64;

	////////////////////////
	///   Constructors   ///
public:

	Component();

	///////////////////
	///   Methods   ///
public:

	/** Returns a reference to the Transform for this Component. */
	FORCEINLINE Transform& GetTransform()
	{
		return *_transform;
	}

	/** Returns a reference to the Transform for this Component. */
	FORCEINLINE const Transform& GetTransform() const
	{
		return *_transform;
	}

	/** Returns a reference to the Scene that this Component is a part of. */
	FORCEINLINE Scene& GetScene()
	{
		return *_scene;
	}

	/** Returns a reference to the Scene that this Component is a part of. */
	FORCEINLINE const Scene& GetScene() const
	{
		return *_scene;
	}

	/** Returns the ID of this Component. */
	FORCEINLINE ID GetID() const
	{
		return _id;
	}

	/** Returns whether this Component is an orphan (has no owning GameObject). */
	FORCEINLINE bool IsOrphan() const
	{
		return _owner == nullptr;
	}

	/** Returns a pointer to the GameObject that owns this Component.
	* NOTE: Returns 'null' if this Component is orphaned. */
	FORCEINLINE GameObject* GetOwner()
	{
		return _owner;
	}

	/** Returns a pointer to the GameObject that owns this Component.
	* NOTE: Returns 'null' if this Component is orphaned. */
	FORCEINLINE const GameObject* GetOwner() const
	{
		return _owner;
	}

	////////////////
	///   Data   ///
private:

	UniquePtr<Transform> _transform;
	GameObject* _owner;
	Scene* _scene;
	ID _id;
};
