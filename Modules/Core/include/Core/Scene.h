// Scene.h
#pragma once

#include "Prop.h"
#include "Camera.h"

namespace Willow
{
	// Scene class contains all game objects and scene information
	// @TODO: this needs some major reworking, but I'm saving that for later
	class CORE_API Scene
	{
		//////////////////
		///   Fields   ///
	public:

		float TimeDilation = 1.0f;
		List<Prop*> Objects;
		List<Camera*> Cameras;

		///////////////////
		///   Methods   ///
	public:

		void Update(float timeInterval);
		void DispatchEvent(const String& eventName, float value);
		void Render() const;
	};
}