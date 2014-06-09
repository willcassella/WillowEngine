#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string>
#include "object.h"
#include "Transform.h"
#include "StaticMesh.h"

class GameObject : public object
{
	REGISTER(GameObject);

	////////////////////////
	///   Constructors   ///

	GameObject( const std::string& _name = "" );
	
	//////////////////
	///   Fields   ///

	std::string name;
	Transform transform;
	StaticMesh *mesh;

	///////////////////
	///   Methods   ///

	void tick(float timeInterval);
};

#endif