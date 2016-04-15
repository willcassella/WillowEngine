// FPSCharacter.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Components/Rendering/CameraComponent.h>
#include <Engine/Components/Physics/CapsuleColliderComponent.h>
#include <Engine/Components/Gameplay/CharacterControllerComponent.h>
#include "config.h"

namespace ExampleGame
{
	class EXAMPLEGAME_API FPSCharacter : public willow::Entity
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(willow::Entity)

		//////////////////////
		///   Components   ///
	public:

		willow::Handle<willow::CameraComponent> View;
		willow::Handle<willow::CapsuleColliderComponent> Capsule;
		willow::Handle<willow::CharacterControllerComponent> CharacterMovement;

		///////////////////
		///   Methods   ///
	protected:

		void on_initialize() override;

		void on_spawn() override;

		///////////////////
		///   Actions   ///
	public:

		void Move(Vec2 direction);
		void Look(Vec2 direction);
		void Fire();
		void Jump();
	};
}
