// MotionState.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Transform.h>
#include "Common.h"

namespace Willow
{
	class MotionState final : public btMotionState
	{
		////////////////////////
		///   Constructors   ///
	public:

		MotionState(Transform& transform)
			: _transform{ &transform }
		{
			// All done
		}
		MotionState(const MotionState& copy) = delete;
		MotionState(MotionState&& move) = delete;

		///////////////////
		///   Methods   ///
	public:

		void getWorldTransform(btTransform& worldTrans) const override
		{
			worldTrans.setOrigin(ConvertToBullet(_transform->Location));
			worldTrans.setRotation(ConvertToBullet(_transform->Rotation));
		}

		void setWorldTransform(const btTransform& worldTrans) override
		{
			// Use temporaries, makes debugging easier
			const auto newLocation = ConvertFromBullet(worldTrans.getOrigin());
			const auto newRotation = ConvertFromBullet(worldTrans.getRotation());

			_transform->Location = newLocation;
			_transform->Rotation = newRotation;
		}

		////////////////
		///   Data   ///
	private:

		Transform* _transform;
	};
}
