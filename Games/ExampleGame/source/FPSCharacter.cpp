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

	void FPSCharacter::OnInitialize()
	{
		this->Base::OnInitialize();

		this->GetWorld().Events.Bind("Move", *this, &FPSCharacter::Move);
		this->GetWorld().Events.Bind("Look", *this, &FPSCharacter::Look);
		this->GetWorld().Events.Bind("Fire", *this, &FPSCharacter::Fire);
		this->GetWorld().Events.Bind("Jump", *this, &FPSCharacter::Jump);
	}

	void FPSCharacter::OnSpawn()
	{
		// TODO
	}

	///////////////////
	///   Actions   ///

	void FPSCharacter::Move(Vec2 direction)
	{
		Vec3 dir = Mat4::Rotate(GetWorld().Get(View)->GetWorldRotation()) * Vec3 { direction.X, 0, -direction.Y };
		GetWorld().Get(CharacterMovement)->Walk(Vec2{ dir.X, dir.Z } / 5);
	}

	void FPSCharacter::Look(Vec2 direction)
	{
		auto view = GetWorld().Get(View);
		view->RotateGlobal(Vec3::Up, direction.X);
		view->Rotate(Vec3::Right, direction.Y);
	}

	void FPSCharacter::Fire()
	{
		auto& projectile = this->GetWorld().Spawn<Willow::StaticMeshComponent>("projectile");
		projectile.Mesh = "Content/Models/monkey.wmesh"_p;
		projectile.Material = "Content/Materials/Sponza.mat";
		projectile.InstanceParams["diffuse"] = Willow::AssetPtr<Willow::Texture>("Content/Textures/monkey.png");

		auto view = GetWorld().Get(View);
		projectile.SetWorldLocation(view->GetWorldLocation() + Vec3{ 3, 0, 0 });
		projectile.SetWorldRotation(view->GetWorldRotation());
		projectile.Translate({ 0, 0, -1 });
		
		auto& sphere = projectile.GetEntity().Connect<Willow::SphereColliderComponent>();
		projectile.GetEntity().SetPhysicsMode(PhysicsMode::Dynamic);
		sphere.SetRadius(0.7f);
	}

	void FPSCharacter::Jump()
	{
		GetWorld().Get(CharacterMovement)->Jump();
	}
}
