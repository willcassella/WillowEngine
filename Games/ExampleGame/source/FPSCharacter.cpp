// FPSCharacter.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Engine/World.h>
#include <Engine/Components/Rendering/StaticMeshComponent.h>
#include <Engine/Components/Physics/SphereColliderComponent.h>
#include "../include/ExampleGame/FPSCharacter.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(ExampleGame::FPSCharacter)
.Field("View", &FPSCharacter::View)
.Field("Capsule", &FPSCharacter::Capsule)
.Field("CharacterMovement", &FPSCharacter::CharacterMovement);

namespace ExampleGame
{
	///////////////////
	///   Methods   ///

	void FPSCharacter::on_initialize()
	{
		this->Base::on_initialize();

		this->get_world().events.Bind("move", *this, &FPSCharacter::Move);
		this->get_world().events.Bind("look", *this, &FPSCharacter::Look);
		this->get_world().events.Bind("fire", *this, &FPSCharacter::Fire);
		this->get_world().events.Bind("jump", *this, &FPSCharacter::Jump);
	}

	void FPSCharacter::on_spawn()
	{
		// TODO
	}

	///////////////////
	///   Actions   ///

	void FPSCharacter::Move(Vec2 direction)
	{
		Vec3 dir = Mat4::Rotate(get_world().get(View)->get_world_rotation()) * Vec3 { direction.X, 0, -direction.Y };
		get_world().get(CharacterMovement)->walk(Vec2{ dir.X, dir.Z } / 5);
	}

	void FPSCharacter::Look(Vec2 direction)
	{
		auto view = get_world().get(View);
		view->rotate_global(Vec3::Up, direction.X);
		view->rotate(Vec3::Right, direction.Y);
	}

	void FPSCharacter::Fire()
	{
		auto& projectile = this->get_world().spawn<willow::StaticMeshComponent>("projectile");
		projectile.mesh = "Content/Models/monkey.wmesh"_p;
		projectile.material = "Content/Materials/Sponza.mat";
		projectile.instance_params["diffuse"] = willow::ResourceHandle<willow::Texture>("Content/Textures/monkey.png");

		auto view = get_world().get(View);
		projectile.set_world_location(view->get_world_location() + Vec3{ 3, 0, 0 });
		projectile.set_world_rotation(view->get_world_rotation());
		projectile.translate({ 0, 0, -1 });
		
		auto& sphere = projectile.get_entity().connect<willow::SphereColliderComponent>();
		projectile.get_entity().set_physics_mode(PhysicsMode::Dynamic);
		sphere.set_radius(0.7f);
	}

	void FPSCharacter::Jump()
	{
		this->get_world().get(CharacterMovement)->jump();
	}
}
