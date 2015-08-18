// Scene.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Containers/Queue.h>
#include "GameObject.h"

/* Scene class contains all game objects and scene information */
class ENGINE_API Scene final : public Object
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(Object)

	//////////////////
	///   Fields   ///
public:

	EventManager Events;
	float TimeDilation = 1.f;
	float TimeStep = 1.f / 60;

	///////////////////
	///   Methods   ///
public:

	void Update();

	/** Spawns a new GameObject of the given type at the start of the next frame */
	template <class GameObjectClass, typename ... Args>
	GameObjectClass& Spawn(Args&& ... args)
	{
		UniquePtr<GameObjectClass> object = New<GameObjectClass>(self, std::forward<Args>(args)...);
		_freshObjects.Push(object.Transfer());
		return *object;
	}

	////////////////
	///   Data   ///
private:

	Array<UniquePtr<GameObject>> _objects;
	Queue<UniquePtr<GameObject>> _freshObjects;
};