#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Transform.h"
#include "Mesh.h"

class GameObject
{
public:

	GameObject();
	~GameObject();
	
	Transform transform;
	Mesh *mesh;
	void Update();
};

#endif