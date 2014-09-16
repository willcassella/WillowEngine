// Prop.h
#pragma once

#include <Render\StaticMesh.h>
#include "GameObject.h"

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

		ResourcePtr<StaticMesh> mesh;

		////////////////////////
		///   Constructors   ///
	public:

		Prop(const String& name);

		///////////////////
		///   Methods   ///
	public:

		void Tick(float timeInterval) override;
	};
}