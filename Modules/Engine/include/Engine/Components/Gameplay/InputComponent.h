// InputComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Event/EventManager.h>
#include "../../Component.h"

namespace willow
{
	class ENGINE_API InputComponent final : public Component
	{
		//////////////////
		///   Fields   ///
	public:

		EventManager events;

		///////////////////
		///   Methods   ///
	private:


	};
}
