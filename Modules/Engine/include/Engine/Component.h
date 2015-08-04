// Component.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Memory/Ptr.h>
#include "config.h"

////////////////////////////////
///   Forward-declarations   ///

/** Defined in 'GameObject.h' */
class GameObject;

/** Defined in 'Scene.h' */
class Scene;

/////////////////
///   Types   ///

class ENGINE_API Component : public Object
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(Object)
	friend Scene;

	////////////////////////
	///   Constructors   ///
public:

	Component(GameObject& owner);

	///////////////////
	///   Methods   ///
public:

	/** Returns whether this component is enabled on the GameObject that owns it. */
	FORCEINLINE bool IsEnabled() const
	{
		return _isEnabled;
	}

	/** Enables this component, if it is currently disabled. */
	void Enable();

	/** Disable the component, if it is currently enabled. */
	void Disable();

	/** Returns the GameObject that this component is attached to. */
	GameObject& GetOwner();

	/** Returns the GameObject that this component is attached to. */
	const GameObject& GetOwner() const;

protected:

	/** Function called when this component is disabled. */
	virtual void OnDisabled();

	/** Function called when this component is enabled. */
	virtual void OnEnabled();

	////////////////
	///   Data   ///
private:

	Ptr<GameObject> _owner;
	bool _isEnabled;
};