// CharacterControllerComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Memory/Pointers/Weak.h>
#include "../Physics/PrimitiveColliderComponent.h"
#include "../../Handle.h"

namespace Willow
{
	/** Character movement controller.
	* NOTE: If the Entity this Component is attached to is in the 'Transient' or 'Dynamic' physics modes, this will not work. */
	class ENGINE_API CharacterControllerComponent final : public Component
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Component)

		/////////////////
		///   Types   ///
	public:

		struct Settings final
		{
			float StepHeight = 1.f;
			Angle MaxSlope;
			float MaxJumpHeight;
			float JumpSpeed;
			float FallSpeed;
		};

		///////////////////
		///   Methods   ///
	public:

		bool OnGround() const;
		
		void Jump();

		void Walk(const Vec2& direction);

		/** Returns the collider this CharacterController is using. */
		FORCEINLINE Handle<PrimitiveColliderComponent> GetCollider() const
		{
			return _collider;
		}

		/** Sets the collider for this CharacterController.
		* NOTE: The given collider must be connected to the same Entity as this. */
		void SetCollider(PrimitiveColliderComponent* collider);

	protected:

		void OnInitialize() override;

	private:

		void Create();

		////////////////
		///   Data   ///
	private:

		Handle<PrimitiveColliderComponent> _collider;
		Settings _settings;
	};
}
