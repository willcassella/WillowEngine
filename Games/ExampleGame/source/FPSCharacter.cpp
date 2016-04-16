// FPSCharacter.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Engine/World.h>
#include <Engine/Components/Rendering/StaticMeshComponent.h>
#include <Engine/Components/Physics/SphereColliderComponent.h>
#include "../include/ExampleGame/FPSCharacter.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(example_game::FPSCharacter)
.Field("view", &FPSCharacter::view)
.Field("character_movement", &FPSCharacter::character_movement);

namespace example_game
{
	///////////////////
	///   Methods   ///

	void FPSCharacter::on_initialize()
	{
		this->Base::on_initialize();

		this->get_world().events.Bind("move", *this, &FPSCharacter::on_move);
		this->get_world().events.Bind("look", *this, &FPSCharacter::on_look);
		this->get_world().events.Bind("fire", *this, &FPSCharacter::on_fire);
		this->get_world().events.Bind("jump", *this, &FPSCharacter::on_jump);
	}

	void FPSCharacter::on_spawn()
	{
		// TODO
	}

	///////////////////
	///   Actions   ///

	void FPSCharacter::on_move(Vec2 direction)
	{
		Vec3 dir = Mat4::Rotate(this->get_world().get_object(this->view)->get_world_rotation()) * Vec3 { direction.X, 0, -direction.Y };
		this->get_world().get_object(this->character_movement)->walk(Vec2{ dir.X, dir.Z } / 5);
	}

	void FPSCharacter::on_look(Vec2 direction)
	{
		auto view = get_world().get_object(this->view);
		view->rotate_global(Vec3::Up, direction.X);
		view->rotate(Vec3::Right, direction.Y);
	}

	void FPSCharacter::on_fire()
	{
		auto& projectile = this->get_world().spawn<StaticMeshComponent>("projectile");
		projectile.mesh = "Content/Models/monkey.wmesh"_p;
		projectile.material = "Content/Materials/Sponza.mat";
		projectile.instance_params["diffuse"] = ResourceHandle<Texture>("Content/Textures/monkey.png");

		auto view = this->get_world().get_object(this->view);
		projectile.set_world_location(view->get_world_location() + Vec3{ 3, 0, 0 });
		projectile.set_world_rotation(view->get_world_rotation());
		projectile.translate({ 0, 0, -1 });
		
		auto& sphere = projectile.get_entity().connect<SphereColliderComponent>();
		projectile.get_entity().set_physics_mode(PhysicsMode::Dynamic);
		sphere.set_radius(0.7f);
	}

	void FPSCharacter::on_jump()
	{
		this->get_world().get_object(this->character_movement)->jump();
	}
}
