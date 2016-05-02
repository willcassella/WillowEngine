// AnimationSystem.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Core/Reflection/ClassInfo.h>
#include <Resource/ResourceManager.h>
#include "../../include/Engine/Systems/AnimationSystem.h"
#include "../../include/Engine/World.h"
#include "../../include/Engine/Components/Rendering/AnimationComponent.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::AnimationSystem);

namespace willow
{
	///////////////////
	///   Methods   ///

	void AnimationSystem::update(World& world)
	{
		auto animationComponents = world.enumerate_objects<AnimationComponent>();

		for (AnimationComponent* anim : animationComponents)
		{
			anim->get_entity().set_location(ResourceManager::get_resource(anim->animation)->sample_pos(static_cast<int32>(anim->current_frame), anim->clip_mode));
			anim->current_frame += anim->play_speed;
		}
	}
}
