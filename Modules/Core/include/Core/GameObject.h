// GameObject.h
#pragma once

#include "InputHandler.h"
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
		InputHandler InputHandler;

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