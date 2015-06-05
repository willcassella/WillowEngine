// Scene.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Containers/Queue.h>
#include "GameObject.h"
#include "Camera.h"

/* Scene class contains all game objects and scene information */
struct ENGINE_API Scene final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT;

	////////////////////////
	///   Constructors   ///
public:

	Scene() = default;
	Scene(const Scene& copy) = delete;
	Scene(Scene&& move) = delete;
	~Scene();

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
	template <class GameObjectClass, typename ... ArgTypes>
	GameObjectClass& Spawn(ArgTypes&& ... args)
	{
		GameObjectClass* object = new GameObjectClass(This, args...);
		_freshObjects.Push(object);
		return *object;
	}

	/////////////////////
	///   Operators   ///
public:

	Scene& operator=(const Scene& copy) = delete;
	Scene& operator=(Scene&& move) = delete;

	////////////////
	///   Data   ///
private:

	List<GameObject*> _objects;
	Queue<GameObject*> _freshObjects;
	Queue<GameObject*> _staleObjects;
};