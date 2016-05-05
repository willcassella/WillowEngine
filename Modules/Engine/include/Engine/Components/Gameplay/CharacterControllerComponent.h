// CharacterControllerComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Physics/PrimitiveColliderComponent.h"
#include "../../Handle.h"

namespace willow
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
			float step_height = 1.f;
			Angle max_slope;
			float jump_speed = 10.f;
			float fall_speed = 9.8f;
		};

		///////////////////
		///   Methods   ///
	public:

		bool on_ground() const;
		
		void jump();

		void walk(const Vec2& direction);

		/** Returns the collider this CharacterController is using. */
		FORCEINLINE Handle<PrimitiveColliderComponent> get_collider() const
		{
			return this->_collider;
		}

		/** Sets the collider for this CharacterController.
		* NOTE: The given collider must be connected to the same Entity as this. */
		void set_collider(PrimitiveColliderComponent* collider);

		float get_jump_speed()
		{
			return _settings.jump_speed;
		}

		void set_jump_speed(float speed)
		{
			_settings.jump_speed = speed;
			this->update_settings();
		}

	protected:

		void on_initialize() override;

		void on_destroy() override;

	private:

		void create();

		void update_settings();

		////////////////
		///   Data   ///
	private:

		Handle<PrimitiveColliderComponent> _collider;
		Settings _settings;
		bool _is_active = false;
	};
}
