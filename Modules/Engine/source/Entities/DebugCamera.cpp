// DebugCamera.cpp

#include "../../include/Engine/Entities/DebugCamera.h"
#include "../../include/Engine/Components/Rendering/CameraComponent.h"
#include "../../include/Engine/World.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::DebugCamera);

///////////////////
///   Methods   ///

namespace Willow
{
	void DebugCamera::OnSpawn()
	{
		this->GetWorld().Events.Bind("Move", *this, &DebugCamera::Move);
		this->GetWorld().Events.Bind("Look", *this, &DebugCamera::Look);
	}

	void DebugCamera::Move(Vec2 dir)
	{
		this->Translate(Vec3{ dir.X, 0, -dir.Y } / 10);
	}

	void DebugCamera::Look(Vec2 dir)
	{
		this->RotateGlobal(Vec3::Up, dir.X);
		this->Rotate(Vec3::Right, dir.Y);
	}
}
