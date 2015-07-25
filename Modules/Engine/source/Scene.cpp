// Scene.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Engine/Scene.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(Scene)
.AddProperty("TimeDilation", "The time dilation of the scene. Default is 1.", &Scene::TimeDilation)
.AddProperty("TimeStep", "The amount of time (ms) that each update of the scene represents.", &Scene::TimeStep);

///////////////////
///   Methods   ///

void Scene::Update()
{
	Queue<OwnerPtr<GameObject>*> staleObjects;

	// Update all objects
	for (auto& object : _objects)
	{
		// If the object is stale
		if (object->IsDestroyed())
		{
			staleObjects.Push(&object);
			continue;
		}
	}

	// Remove stale objects
	while (!staleObjects.IsEmpty())
	{
		OwnerPtr<GameObject>* object = staleObjects.Pop();
		_objects.DeleteAll(*object);
	}

	// Add new objects
	while (!_freshObjects.IsEmpty())
	{
		OwnerPtr<GameObject> freshObject = _freshObjects.Pop();
		
		// Activate all the object's components
		for (auto component : freshObject->GetComponents())
		{
			component->Enable();
		}

		// Call the freshObjects OnSpawn() function
		freshObject->OnSpawn();

		_objects.Add(freshObject.Transfer());
	}
}