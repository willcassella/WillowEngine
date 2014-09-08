// Scene.h
#pragma once

#include "Prop.h"
#include "Camera.h"

namespace Willow
{
	template class CORE_API Array < Prop* > ;
	template class CORE_API Array < Camera* > ;
	template class CORE_API Array < int > ;

	// Scene class contains all game objects and scene information
	class CORE_API Scene
	{
		//////////////////
		///   Fields   ///
	public:

		float timeDilation = 1.0f;
		Array<Prop*> objects;
		Array<Camera*> cameras;

		///////////////////
		///   Methods   ///
	public:

		void update(float timeInterval);
		void render() const;
	};
}