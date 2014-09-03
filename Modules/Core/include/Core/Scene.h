// Scene.h
#pragma once

#include <vector>
#include "Prop.h"
#include "Camera.h"

namespace Willow
{
	// Scene class contains all game objects and scene information
	class CORE_API Scene
	{
		//////////////////
		///   Fields   ///
	public:

		std::vector<Prop*> objects;
		std::vector<Camera*> cameras;

		///////////////////
		///   Methods   ///
	public:

		void update(float timeInterval);
		void render() const;
	};
}