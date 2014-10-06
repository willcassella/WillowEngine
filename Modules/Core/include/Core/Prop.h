// Prop.h
#pragma once

#include "GameObject.h"
#include "StaticMeshComponent.h"

namespace Willow
{
	class CORE_API Prop : public GameObject
	{
		///////////////////////
		///   Information   ///
	public:

		typedef GameObject Super;

		//////////////////
		///   Fields   ///
	public:

		StaticMeshComponent MeshComponent;

		////////////////////////
		///   Constructors   ///
	public:

		Prop(const String& name);
		~Prop() override = default;
	};
}