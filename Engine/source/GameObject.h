#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Transform.h"
#include "StaticMesh.h"

class GameObject
{
public:

	GameObject();
	~GameObject();
	
	Transform transform;
	StaticMesh *mesh;
	void Update();
};

#endif