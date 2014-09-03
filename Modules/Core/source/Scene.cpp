// Scene.cpp

#include "..\include\Core\Scene.h"
using namespace Willow;

// @TODO: this needs some rethinking
void Scene::update(float timeInterval)
{
	for (Prop* object : this->objects)
	{
		object->tick(timeInterval);
	}

	for (Camera* cam : this->cameras)
	{
		cam->tick(timeInterval);
	}
}

void Scene::render() const
{
	for (Prop* object : this->objects)
	{
		Math::Mat4 model = object->transform.getModel();

		// WARNING: This assumes there is at least one camera in the scene, I will fix this later
		Math::Mat4 view = this->cameras[0]->transform.getModel().inverse();
		Math::Mat4 proj = this->cameras[0]->getPerspective();

		object->mesh->render(model, view, proj);
	}
}