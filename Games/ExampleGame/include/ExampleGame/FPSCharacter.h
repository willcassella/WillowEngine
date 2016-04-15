// FPSCharacter.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Components/Rendering/CameraComponent.h>
#include <Engine/Components/Physics/CapsuleColliderComponent.h>
#include <Engine/Components/Gameplay/CharacterControllerComponent.h>
#include "config.h"

namespace example_game
{
	using namespace willow;

	class EXAMPLEGAME_API FPSCharacter : public Entity
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Entity)

		//////////////////////
		///   Components   ///
	public:

		Handle<CameraComponent> view;
		Handle<CapsuleColliderComponent> capsule;
		Handle<CharacterControllerComponent> character_movement;

		///////////////////
		///   Methods   ///
	protected:

		void on_initialize() override;

		void on_spawn() override;

		///////////////////
		///   Actions   ///
	public:

		void on_move(Vec2 direction);
		void on_look(Vec2 direction);
		void on_fire();
		void on_jump();
	};
}
