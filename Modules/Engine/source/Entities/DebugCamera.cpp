// DebugCamera.cpp

#include "../../include/Engine/Entities/DebugCamera.h"
#include "../../include/Engine/Components/Rendering/CameraComponent.h"
#include "../../include/Engine/World.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::DebugCamera);

///////////////////
///   Methods   ///

namespace willow
{
	void DebugCamera::on_initialize()
	{
		this->Base::on_initialize();
		this->get_world().events.Bind("move", *this, &DebugCamera::on_move);
		this->get_world().events.Bind("look", *this, &DebugCamera::on_look);
	}

	void DebugCamera::on_spawn()
	{
		this->Base::on_spawn();
		this->get_world().spawn<CameraComponent>(*this);
	}

	void DebugCamera::on_move(Vec2 dir)
	{
		this->translate(Vec3{ dir.X, 0, -dir.Y } / 10);
	}

	void DebugCamera::on_look(Vec2 dir)
	{
		this->rotate_global(Vec3::Up, dir.X);
		this->rotate(Vec3::Right, dir.Y);
	}
}
