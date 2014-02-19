#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string>
#include "Transform.h"
#include "StaticMesh.h"

class GameObject
{
public:

	GameObject( const std::string& _NAME );
	GameObject( const std::string& _NAME, const StaticMesh& _MESH );
	~GameObject();
	
	std::string name;
	Transform transform;
	StaticMesh *mesh;
	void Update();
};

#endif