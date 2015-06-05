// Scene.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Engine/Scene.h"

//////////////////////
///   Reflection   ///

STRUCT_REFLECTION(Scene)
.AddField("TimeDilation", &Scene::TimeDilation)
.AddField("TimeStep", &Scene::TimeStep);

////////////////////////
///   Constructors   ///

Scene::~Scene()
{
	// Delete all objects
	for (auto& object : _objects)
	{
		delete object;
	}
}

///////////////////
///   Methods   ///

void Scene::Update()
{
	// Update all objects
	for (auto& object : _objects)
	{
		// If the object is stale
		if (object->IsDestroyed())
		{
			_staleObjects.Push(object);
			continue;
		}
	}

	// Remove stale objects
	while (!_staleObjects.IsEmpty())
	{
		GameObject* object = _staleObjects.Pop();
		_objects.DeleteAll(object);
		delete object;
	}

	// Add new objects
	while (!_freshObjects.IsEmpty())
	{
		GameObject* freshObject = _freshObjects.Pop();
		
		// Activate all the object's components
		for (auto component : freshObject->GetComponents())
		{
			component->Enable();
		}

		// Call the freshObjects OnSpawn() function
		freshObject->OnSpawn();

		_objects.Add(freshObject);
	}
}