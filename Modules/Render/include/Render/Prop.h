// Prop.h
#pragma once

#include <Core\GameObject.h>
#include "StaticMeshComponent.h"

namespace Willow
{
	class RENDER_API Prop : public GameObject
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE
		EXTENDS(GameObject)

		////////////////////////
		///   Constructors   ///
	public:

		Prop();

		//////////////////
		///   Fields   ///
	public:

		StaticMeshComponent MeshComponent;
	};
}