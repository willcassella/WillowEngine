// Scene.cpp

#include "..\include\Core\Scene.h"
using namespace Willow;

///////////////////
///   Methods   ///

// @TODO: this needs some rethinking
void Scene::Update(float timeInterval)
{
	for (uint32 i = 0; i < Objects.Size(); i++)
	{
		Objects[i]->Tick(timeInterval * TimeDilation);
	}

	for (uint32 i = 0; i < Cameras.Size(); i++)
	{
		Cameras[i]->Tick(timeInterval * TimeDilation);
	}
}

void Scene::Render() const
{
	for (uint32 i = 0; i < Objects.Size(); i++)
	{
		Prop* object = Objects[i];
		Mat4 model = object->Transform.GetTransfomationMatrix();

		// WARNING: This assumes there is at least one camera in the scene, I will fix this later
		Mat4 view = this->Cameras[0]->Transform.GetTransfomationMatrix().Inverse();
		Mat4 proj = this->Cameras[0]->GetPerspective();

		object->mesh->Render(model, view, proj);
	}
}