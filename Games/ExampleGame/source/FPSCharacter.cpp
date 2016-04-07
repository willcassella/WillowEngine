// FPSCharacter.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Engine/World.h>
#include <Engine/Components/Rendering/StaticMeshComponent.h>
#include <Engine/Components/Physics/SphereColliderComponent.h>
#include "../include/ExampleGame/FPSCharacter.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(ExampleGame::FPSCharacter)
.Field("View", &FPSCharacter::View)
.Field("Capsule", &FPSCharacter::Capsule);

namespace ExampleGame
{
	///////////////////
	///   Methods   ///

	void FPSCharacter::OnSpawn()
	{
		Base::OnSpawn();
		
		this->GetWorld().Events.Bind("Move", *this, &FPSCharacter::Move);
		this->GetWorld().Events.Bind("Look", *this, &FPSCharacter::Look);
		this->GetWorld().Events.Bind("Fire", *this, &FPSCharacter::Fire);
		this->GetWorld().Events.Bind("Jump", *this, &FPSCharacter::Jump);
	}

	///////////////////
	///   Actions   ///

	void FPSCharacter::Move(Vec2 direction)
	{
		this->ApplyImpulse(Mat4::Rotate(View.Borrow()->GetWorldRotation()) * Vec3{ direction.X, 0, -direction.Y } * 10);
	}

	void FPSCharacter::Look(Vec2 direction)
	{
		auto view = this->View.Borrow();
		view->RotateGlobal(Vec3::Up, direction.X);
		view->Rotate(Vec3::Right, direction.Y);
	}

	void FPSCharacter::Fire()
	{
		auto& projectile = this->GetWorld().Spawn<Willow::StaticMeshComponent>("projectile");
		projectile.Mesh = "Content/Models/monkey.wmesh"_p;
		projectile.Material = "Content/Materials/Sponza.mat";
		projectile.InstanceParams["diffuse"] = Willow::AssetPtr<Willow::Texture>("Content/Textures/monkey.png");

		projectile.SetWorldLocation(this->GetWorldLocation() + Vec3{ 3, 0, 0 });
		auto& sphere = projectile.GetEntity().Connect<Willow::SphereColliderComponent>();
		projectile.GetEntity().SetPhysicsMode(PhysicsMode::Dynamic);
		sphere.SetRadius(0.7f);
	}

	void FPSCharacter::Jump()
	{
		this->ApplyImpulse({ 0, 100, 0 });
	}
}
