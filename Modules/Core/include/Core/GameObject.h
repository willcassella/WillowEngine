// GameObject.h
#pragma once

#include "EventManager.h"
#include "Transform.h"

namespace Willow
{
	class CORE_API GameObject
	{
		//////////////////
		///   Fields   ///
	public:

		String Name;
		Transform Transform;
		EventManager EventManager;

		////////////////////////
		///   Constructors   ///
	public:

		GameObject(const String& name = "");
		virtual ~GameObject();

		///////////////////
		///   Methods   ///
	public:

		virtual void Tick(float timeInterval);
	};
}