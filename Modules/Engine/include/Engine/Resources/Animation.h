// Animation.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Math/Vec3.h>
#include <Core/Math/Quat.h>
#include <Resource/Path.h>
#include "../config.h"

namespace willow
{
	struct ENGINE_API Animation final
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_STRUCT

		/////////////////
		///   Types   ///
	public:

		/** Determines how sampling beyond the last frame is handled. */
		enum class ClipMode : byte
		{
			/** The value of the last frame in this animation will be returned. */
			Stop,

			/** The animation be looped. */
			Loop,

			/** The animation will alternate looping backwards and forwards. */
			Ping_Pong
		};

		////////////////////////
		///   Constructors   ///
	public:

		Animation(const Path& path);

		///////////////////
		///   Methods   ///
	public:

		/** Clips the given frame with the given mode. */
		uint32 clip_frame(int32 frame, ClipMode mode) const;

		/** Samples the value of this animation at the given frame. */
		Vec3 sample_pos(int32 frame, ClipMode clip) const;

		/** Adds the animated position vector at the given frame to the given Vector. */
		Vec3 add_pos(int32 frame, ClipMode clip, const Vec3& pos) const;

		/** Blends the animated position vector at the given frame to the given vector with the given influence.
		* 'influence' - The amount of influence the animation value has over the given value. '0': No influence. '1': 100% influence. */
		Vec3 blend_pos(int32 frame, ClipMode clip, Vec3 pos, float influence) const;

		/** Samples the value of this animation at the given frame. */
		Quat sample_rot(int32 frame, ClipMode clip) const;

		Vec3 sample_scale(int32 frame, ClipMode clip) const;

		//////////////////
		///   Fields   ///
	public:

		uint32 num_frames;
		
		// Position frames
		Array<float> pos_x_frames;
		Array<float> pos_y_frames;
		Array<float> pos_z_frames;
		
		// Rotation frames
		Array<Quat> rot_frames;
		
		// Scale frames
		Array<float> scale_x_frames;
		Array<float> scale_y_frames;
		Array<float> scale_z_frames;
	};
}

REFLECTABLE_ENUM(ENGINE_API, willow::Animation::ClipMode)
