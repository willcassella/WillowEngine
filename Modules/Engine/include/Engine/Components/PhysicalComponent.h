// PhysicalComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <memory>
#include "../Forwards/Physics.h"
#include "../Component.h"

/////////////////
///   Types   ///

namespace Willow
{
	enum class PhysicsMode : byte
	{
		/* This object does not participate in the physics simulation at all. */
		Transient,

		/** This object can detect collisions, but does not otherwise participate in the physics simulation. */
		Ghost,

		/* This object affects the physics simulation, but is not affected by it. */
		Kinematic,

		/* This object both affects, and is affected by the physics simulation. */
		Dynamic
	};

	class ENGINE_API PhysicalComponent : public Component
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Component)

		////////////////////////
		///   Constructors   ///
	public:

		PhysicalComponent();
		~PhysicalComponent() override;

		///////////////////
		///   Methods   ///
	public:

		/** Returns the mass of this PhysicalComponent. */
		FORCEINLINE Scalar GetMass() const
		{
			return _mass;
		}

		/** Sets the mass of this PhysicalComponent. */
		void SetMass(Scalar value);

		/** Returns the physics mode of this PhysicalComponent. */
		FORCEINLINE PhysicsMode GetPhysicsMode() const
		{
			return _physicsMode;
		}

		/** Sets the physics mode of this PhysicalComponent. */
		void SetPhysicsMode(PhysicsMode mode);

	protected:

		virtual btCollisionShape* GetShape() = 0;

		void OnSpawn() override;

	private:

		void SetupPhysics();

		void DestroyPhysics();

		////////////////
		///   Data   ///
	private:

		std::unique_ptr<PhysicsState> _physicsState;
		PhysicsMode _physicsMode = PhysicsMode::Transient;
		Scalar _mass = 1;
	};
}

REFLECTABLE_ENUM(ENGINE_API, Willow::PhysicsMode)

