// GameObject.h
#pragma once

#include <Utility\String.h>
#include <Utility\Math\Transform.h>
#include "config.h"

namespace Willow
{
	class CORE_API GameObject
	{
		//////////////////
		///   Fields   ///
	public:

		String name;
		Math::Transform transform;

		////////////////////////
		///   Constructors   ///
	public:

		GameObject(const String& _name = "");

		///////////////////
		///   Methods   ///
	public:

		virtual void tick(float timeInterval) = 0;
	};
}