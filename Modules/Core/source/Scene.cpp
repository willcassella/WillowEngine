// Scene.cpp

#include "..\include\Core\Scene.h"
using namespace Willow;

///////////////////
///   Methods   ///

// @TODO: this needs some rethinking
void Scene::Update(float timeInterval)
{
	for (auto& object : Objects)
	{
		object->Tick(timeInterval * TimeDilation);
	}

	for (auto& cam : Cameras)
	{
		cam->Tick(timeInterval * TimeDilation);
	}
}

void Scene::DispatchEvent(const String& eventName, float value)
{
	for (auto& cam : Cameras)
	{
		cam->EventManager.DispatchInputEvent(eventName, value);
	}
}

void Scene::Render() const
{
	for (auto& prop : Objects)
	{
		Mat4 model = prop->Transform.GetTransfomationMatrix();

		// WARNING: This assumes there is at least one camera in the scene, I will fix this later
		Mat4 view = this->Cameras[0]->Transform.GetTransfomationMatrix().Inverse();
		Mat4 proj = this->Cameras[0]->GetPerspective();

		prop->mesh->Render(model, view, proj);
	}
}