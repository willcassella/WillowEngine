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

		typedef Willow::Component Super;

		////////////////////////
		///   Constructors   ///
	public:

		SlideComponent(Willow::GameObject& owner);
		~SlideComponent() override = default;

		///////////////////
		///   Methods   ///
	protected:

		void OnSceneUpdate(float timeInterval) override;
	};
}