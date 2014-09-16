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

		float TimeDilation = 1.0f;
		Array<Prop*> Objects;
		Array<Camera*> Cameras;

		///////////////////
		///   Methods   ///
	public:

		void Update(float timeInterval);
		void Render() const;
	};
}