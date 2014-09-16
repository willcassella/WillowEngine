// GameObject.h
#pragma once

#include <Utility\String.h>
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