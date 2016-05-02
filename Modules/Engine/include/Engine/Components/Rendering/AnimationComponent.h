// AnimationComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Resource/ResourceHandle.h>
#include "../../Resources/Animation.h"
#include "../../Component.h"

namespace willow
{
	class ENGINE_API AnimationComponent final : public Component
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Component)

		/////////////////
		///   Types   ///
	public:

		enum class BlendMode : byte
		{
			/** The animation is treated as the absolute local position of the object. */
			Set,
			
			/** The animation works additively on the objects current position. */
			Add
		};

		//////////////////
		///   Fields   ///
	public:

		/** The currently playing animation. */
		ResourceHandle<Animation> animation;

		/** The current frame of the animation. */
		float current_frame = 0.f;

		/** The speed at which this animation plays. */
		float play_speed = 1.f;

		/** The clip mode this animation should use. */
		Animation::ClipMode clip_mode = Animation::ClipMode::Stop;

		/** The blending mode this animation should use. */
		BlendMode blend_mode = BlendMode::Add;

		///////////////////
		///   Methods   ///
	public:

		void ToArchive(ArchiveWriter& writer) const override;

		void FromArchive(const ArchiveReader& reader) override;
	};
}

REFLECTABLE_ENUM(ENGINE_API, willow::AnimationComponent::BlendMode)
