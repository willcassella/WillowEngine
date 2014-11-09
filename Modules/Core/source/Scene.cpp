// Scene.cpp

#include "..\include\Core\Scene.h"
using namespace Willow;

//////////////////////
///   Reflection   ///

BEGIN_CLASS_INFO(Willow::Scene)
HAS_FACTORY
FIELD(TimeDilation)
FIELD(TimeStep)
END_REFLECTION_INFO

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

		// Update the object
		object->Update(TimeDilation);
		
		// Update its components
		for (auto& component : object->GetComponents())
		{
			component->Update(TimeDilation);
		}
	}

	// Remove stale objects
	while (!_staleObjects.IsEmpty())
	{
		GameObject* object = _staleObjects.Pop();
		_objects.RemoveAll(object);
		delete object;
	}

	// Add new objects
	while (!_freshObjects.IsEmpty())
	{
		_objects.Add(_freshObjects.Pop());
	}
}

void Scene::DispatchEvent(const String& eventName, float value)
{
	for (auto& object : _objects)
	{
		object->EventManager.DispatchInputEvent(eventName, value);
	}
}

// @TODO: This needs work
void Scene::Render() const
{
	Mat4 view = Cameras[0]->Transform.GetTransfomationMatrix().Inverse();
	Mat4 proj = Cameras[0]->GetPerspective();

	for (auto& object : _objects)
	{
		for (auto& component : object->GetComponents())
		{
			component->Render(view, proj);
		}
	}
}