// FPSCharacter.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Memory/Pointers/Weak.h>
#include <Engine/Components/Rendering/CameraComponent.h>
#include <Engine/Components/Physics/CapsuleColliderComponent.h>
#include "config.h"

namespace ExampleGame
{
	class EXAMPLEGAME_API FPSCharacter : public Willow::Entity
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Willow::Entity)

		//////////////////////
		///   Components   ///
	public:

		Weak<Willow::CameraComponent> View;
		Weak<Willow::CapsuleColliderComponent> Capsule;

		///////////////////
		///   Methods   ///
	protected:

		void OnSpawn() override;

		///////////////////
		///   Actions   ///
	public:

		void Move(Vec2 direction);
		void Look(Vec2 direction);
		void Fire();
		void Jump();
	};
}
