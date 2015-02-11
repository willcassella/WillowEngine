// Component.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "config.h"

class ENGINE_API Component : public Object
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(Object);
	friend class Scene;

	////////////////////////
	///   Constructors   ///
public:

	Component(class GameObject& owner);

	///////////////////
	///   Methods   ///
public:

	/** Returns whether this component is enabled on the GameObject that owns it */
	bool IsEnabled() const;

	/** Enable this component, if it is disabled 
	* If the component is already enabled, this has no effect */
	void Enable();

	/** Disable the component, if it is enabled
	* If the component is already disabled, this has no effect */
	void Disable();

	/** Returns the GameObject that this component is attached to */
	GameObject& GetOwner();

	/** Returns the GameObject that this component is attached to */
	const GameObject& GetOwner() const;

protected:

	virtual void Update(float timeInterval);

	virtual void OnDisabled();

	virtual void OnEnabled();

	////////////////
	///   Data   ///
private:

	GameObject* _owner;
	bool _isEnabled;
};