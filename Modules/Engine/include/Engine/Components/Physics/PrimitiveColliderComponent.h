// PrimitiveColliderComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "ColliderComponent.h"

namespace Willow
{
	/** Type mechanism for distinguishing primitive collider shapes (Capsules, Cubes, Spheres, etc) 
	* from complex ones (Static Meshes, height fields). */
	class ENGINE_API PrimitiveColliderComponent : public ColliderComponent
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(ColliderComponent)
	};
}
