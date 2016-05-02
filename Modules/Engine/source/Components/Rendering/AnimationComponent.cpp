// AnimationComponent.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Resource/ResourceManager.h>
#include "../../../include/Engine/Components/Rendering/AnimationComponent.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::AnimationComponent)
.Field("animation", &AnimationComponent::animation)
.Field("current_frame", &AnimationComponent::current_frame)
.Field("play_speed", &AnimationComponent::play_speed);
//.Field("clip_mode", &AnimationComponent::clip_mode)
//.Field("blend_mode", &AnimationComponent::blend_mode);

BUILD_ENUM_REFLECTION(willow::AnimationComponent::BlendMode)
.Value("Set", willow::AnimationComponent::BlendMode::Set)
.Value("Add", willow::AnimationComponent::BlendMode::Add);

namespace willow
{
	///////////////////
	///   Methods   ///

	void AnimationComponent::ToArchive(ArchiveWriter& writer) const
	{
		this->Base::ToArchive(writer);

		switch (this->clip_mode)
		{
		case Animation::ClipMode::Stop:
			writer.PushValue("clip_mode", "Stop");
			break;

		case Animation::ClipMode::Loop:
			writer.PushValue("clip_mode", "Loop");
			break;

		case Animation::ClipMode::Ping_Pong:
			writer.PushValue("clip_mode", "Ping_Pong");
			break;
		}

		switch (this->blend_mode)
		{
		case BlendMode::Set:
			writer.PushValue("blend_mode", "Set");
			break;

		case BlendMode::Add:
			writer.PushValue("blend_mode", "Add");
			break;
		}
	}

	void AnimationComponent::FromArchive(const ArchiveReader& reader)
	{
		this->Base::FromArchive(reader);

		reader.GetChild("clip_mode", [this](const ArchiveReader& child)
		{
			String value;
			child.GetValue(value);

			if (value == "Stop")
			{
				this->clip_mode = Animation::ClipMode::Stop;
			}
			else if (value == "Loop")
			{
				this->clip_mode = Animation::ClipMode::Loop;
			}
			else if (value == "Ping_Pong")
			{
				this->clip_mode = Animation::ClipMode::Ping_Pong;
			}
		});

		reader.GetChild("blend_mode", [this](const ArchiveReader& child)
		{
			String value;
			child.GetValue(value);

			if (value == "Set")
			{
				this->blend_mode = BlendMode::Set;
			}
			else if (value == "Add")
			{
				this->blend_mode = BlendMode::Add;
			}
		});
	}
}
