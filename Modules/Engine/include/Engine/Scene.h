// Scene.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Containers/Queue.h>
#include "GameObject.h"
#include "Camera.h"

/* Scene class contains all game objects and scene information */
class ENGINE_API Scene : public Object
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(Object);

	//////////////////
	///   Fields   ///
public:

	float TimeDilation = 1.f;
	float TimeStep = 1.f / 60;

	////////////////////////
	///   Constructors   ///
public:

	// @TODO: Rule of 5
	~Scene();

	///////////////////
	///   Methods   ///
public:

	void Update();
	void DispatchEvent(const String& eventName, float value);

	template <class GameObjectClass, typename ... ParamTypes>
	GameObjectClass& AddObject(const String& name, const ParamTypes& ... params)
	{
		GameObjectClass* object = new GameObjectClass(name, params);
		_freshObjects.Push(object);
		return *object;
	}

	////////////////
	///   Data   ///
private:

	List<GameObject*> _objects;
	Queue<GameObject*> _freshObjects;
	Queue<GameObject*> _staleObjects;
};