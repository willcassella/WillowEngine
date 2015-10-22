// Scene.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Engine/Scene.h"
#include "../include/Engine/ServiceInterfaces/IRenderer.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Scene)
//.Data("Objects", &Scene::_objects)
//.Data("FreshObjects", &Scene::_freshObjects)
.Field("TimeDilation", &Scene::TimeDilation, "The time dilation of the scene. Default is 1.")
.Field("TimeStep", &Scene::TimeStep, "The amount of time (ms) that each update of the scene represents.");

///////////////////
///   Methods   ///

void Scene::Update()
{
	Queue<UniquePtr<GameObject>*> staleObjects;

	Events.DispatchEvent("Update", 1.f);
	Events.Flush();

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
		UniquePtr<GameObject>* object = staleObjects.Pop();
		_objects.DeleteAll(*object);
	}

	// Add new objects
	while (!_freshObjects.IsEmpty())
	{
		UniquePtr<GameObject> freshObject = _freshObjects.Pop();
		
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
