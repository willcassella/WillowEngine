// Animation.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Core/Reflection/EnumInfo.h>
#include <Resource/Resources/BinaryData.h>
#include "../../include/Engine/Resources/Animation.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::Animation);

BUILD_ENUM_REFLECTION(willow::Animation::ClipMode)
.Value("Stop", willow::Animation::ClipMode::Stop)
.Value("Loop", willow::Animation::ClipMode::Loop)
.Value("Ping_Pong", willow::Animation::ClipMode::Ping_Pong);

namespace willow
{
	////////////////////////
	///   Constructors   ///

	Animation::Animation(const Path& path)
	{
		BinaryData data{ path };
		auto* cursor = data.get_data();
		
		// Get the number of frames in this animation
		this->num_frames = *reinterpret_cast<uint32*>(cursor);
		cursor += sizeof(uint32);

		// Load x position frames
		bool hasXFrames = static_cast<bool>(*cursor);
		cursor += 1;
		if (hasXFrames)
		{
			this->pos_x_frames = Array<float>(reinterpret_cast<float*>(cursor), num_frames);
			cursor += sizeof(float) * num_frames;
		}

		// Load y position frames
		bool hasYFrames = static_cast<bool>(*cursor);
		cursor += 1;
		if (hasYFrames)
		{
			this->pos_y_frames = Array<float>(reinterpret_cast<float*>(cursor), num_frames);
			cursor += sizeof(float) * num_frames;
		}

		// Load z position frames
		bool hasZFrames = static_cast<bool>(*cursor);
		cursor += 1;
		if (hasZFrames)
		{
			this->pos_z_frames = Array<float>(reinterpret_cast<float*>(cursor), num_frames);
			cursor += sizeof(float) * num_frames;
		}
	}

	///////////////////
	///   Methods   ///

	uint32 Animation::clip_frame(int32 frame, ClipMode mode) const
	{
		switch (mode)
		{
		case ClipMode::Stop:
			return std::max<uint32>(0, std::min<uint32>(frame, num_frames));
			
		case ClipMode::Loop:
			return frame % num_frames;

		case ClipMode::Ping_Pong:
			auto div = std::div(frame, num_frames); // Gives quotient and remainder
			int32 mult = (int32)std::pow(-1, div.quot); // Alternates between '1' and '-1'

			if (mult == -1)
			{
				return num_frames - div.rem - 1;
			}
			else
			{
				return div.rem;
			}
		}

		// Not sure how else to handle case where 'mode' isn't valid
		return 0;
	}

	Vec3 Animation::sample_pos(int32 frame, ClipMode clip) const
	{
		Vec3 result;
		auto clippedFrame = this->clip_frame(frame, clip);

		if (!this->pos_x_frames.IsEmpty())
		{
			result.X = this->pos_x_frames[clippedFrame];
		}

		if (!this->pos_y_frames.IsEmpty())
		{
			result.Y = this->pos_y_frames[clippedFrame];
		}

		if (!this->pos_z_frames.IsEmpty())
		{
			result.Z = this->pos_z_frames[clippedFrame];
		}

		return result;
	}

	Vec3 Animation::add_pos(int32 frame, ClipMode clip, const Vec3& pos) const
	{
		auto anim = this->sample_pos(frame, clip);
		return pos + anim;
	}

	Vec3 Animation::blend_pos(int32 frame, ClipMode clip, Vec3 pos, float influence) const
	{
		auto anim = this->sample_pos(frame, clip);
		influence = std::min(0.f, std::max(influence, 1.f));

		// Calculate influence
		anim *= influence;
		pos *= 1.f - influence;

		return pos + anim;
	}

	Quat Animation::sample_rot(int32 frame, ClipMode clip) const
	{
		auto clippedFrame = this->clip_frame(frame, clip);

		if (!this->rot_frames.IsEmpty())
		{
			return rot_frames[clippedFrame];
		}
		else
		{
			return Quat();
		}
	}

	Vec3 Animation::sample_scale(int32 frame, ClipMode clip) const
	{
		auto clippedFrame = this->clip_frame(frame, clip);
		Vec3 result;

		if (!this->scale_x_frames.IsEmpty())
		{
			result.X = scale_x_frames[clippedFrame];
		}
		
		if (!this->scale_y_frames.IsEmpty())
		{
			result.Y = scale_y_frames[clippedFrame];
		}

		if (!this->scale_z_frames.IsEmpty())
		{
			result.Z = scale_z_frames[clippedFrame];
		}

		return result;
	}
}
