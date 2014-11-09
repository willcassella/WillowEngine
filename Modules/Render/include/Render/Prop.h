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

		//////////////////
		///   Fields   ///
	public:

		StaticMeshComponent MeshComponent;

		////////////////////////
		///   Constructors   ///
	public:

		Prop(const String& name = "");
	};
}