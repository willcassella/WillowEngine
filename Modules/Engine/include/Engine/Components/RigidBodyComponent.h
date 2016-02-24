// CameraComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "PhysicalComponent.h"

namespace Willow
{
	class ENGINE_API RigidBodyComponent final : public PhysicalComponent
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Component)

		///////////////////
		///   Methods   ///
	protected:

		void OnSpawn() override;
	};
}
