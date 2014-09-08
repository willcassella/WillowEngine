// Scene.cpp

#include "..\include\Core\Scene.h"
using namespace Willow;

// @TODO: this needs some rethinking
void Scene::update(float timeInterval)
{
	for (uint i = 0; i < objects.size(); i++)
	{
		objects[i]->tick(timeInterval * timeDilation);
	}

	for (uint i = 0; i < cameras.size(); i++)
	{
		cameras[i]->tick(timeInterval * timeDilation);
	}
}

void Scene::render() const
{
	for (uint i = 0; i < objects.size(); i++)
	{
		Prop* object = objects[i];
		Math::Mat4 model = object->transform.getModel();

		// WARNING: This assumes there is at least one camera in the scene, I will fix this later
		Math::Mat4 view = this->cameras[0]->transform.getModel().inverse();
		Math::Mat4 proj = this->cameras[0]->getPerspective();

		object->mesh->render(model, view, proj);
	}
}