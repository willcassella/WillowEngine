// Prop.h
#pragma once

#include <Render\StaticMesh.h>
#include "GameObject.h"

namespace Engine
{
	class ENGINE_API Prop : public GameObject
	{
		///////////////////////
		///   Information   ///
	public:

		typedef GameObject Base;

		//////////////////
		///   Fields   ///
	public:

		Render::StaticMesh* mesh;

		////////////////////////
		///   Constructors   ///
	public:

		Prop(const Willow::String& _name);

		///////////////////
		///   Methods   ///
	public:

		void tick(float timeInterval) override;
	};
}