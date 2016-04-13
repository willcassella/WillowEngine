// FPSCharacter.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Components/Rendering/CameraComponent.h>
#include <Engine/Components/Physics/CapsuleColliderComponent.h>
#include <Engine/Components/Gameplay/CharacterControllerComponent.h>
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

		Willow::Handle<Willow::CameraComponent> View;
		Willow::Handle<Willow::CapsuleColliderComponent> Capsule;
		Willow::Handle<Willow::CharacterControllerComponent> CharacterMovement;

		///////////////////
		///   Methods   ///
	protected:

		void OnInitialize() override;

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
