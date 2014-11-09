// SlideComponent.h
#pragma once

#include <Core\GameObject.h>
#include "config.h"

namespace ExampleGame
{
	class EXAMPLEGAME_API SlideComponent : public Willow::Component
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE
		EXTENDS(Willow::Component)

		////////////////////////
		///   Constructors   ///
	public:

		SlideComponent(Willow::GameObject& owner);
		~SlideComponent() override = default;

		///////////////////
		///   Methods   ///
	protected:

		void Update(float timeInterval) override;
	};
}