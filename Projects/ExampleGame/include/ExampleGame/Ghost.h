// Ghost.h
#pragma once

#include <Core\GameObject.h>
#include <Core\StaticMeshComponent.h>
#include "SlideComponent.h"
#include "config.h"

namespace ExampleGame
{
	class EXAMPLEGAME_API Ghost : public Willow::GameObject
	{
		///////////////////////
		///   Information   ///
	public:

		typedef GameObject Super;

		/////////////////////////
		///   Constructors   ///
	public:

		Ghost(const Willow::String& name);
		~Ghost() override = default;

		//////////////////////
		///   Components   ///
	public:

		Willow::StaticMeshComponent MeshComponent;
		SlideComponent Slider;

		///////////////////
		///   Actions   ///
	public:

		void Disappear();

		////////////////
		///   Data   ///
	protected:

		bool hasDisappeared;
	};
}