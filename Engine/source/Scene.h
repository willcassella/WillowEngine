#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include "GameObject.h"
#include "Camera.h"

// Scene class contains all game objects and scene information
// This is going to need a massive overhaul once XML IO is functional
class Scene
{
	////////////////
	///   Data   ///
	////////////////

public:

	std::vector< GameObject* >	objects;
	std::vector< Camera* >		cameras;
};

#endif