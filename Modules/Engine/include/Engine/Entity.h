// Entity.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "GameObject.h"
#include "Transform.h"

namespace Willow
{
	/////////////////
	///   Types   ///

	enum SetPhysicsModeMode
	{
		/** This Entity's physics state will be destroyed  */
		SPM_DestroyPhysicsState,
		SPM_ResetPhysicsState,
		SPM_KeepPhysicsState,
	};

	/** An 'Entity' is a collection of Components that should be together thought of as a single object.
	* Components can be added and removed ("connected" and "disconnected") from an Entity, but they cannot be moved between Entities.
	* Components are always connected to a single Entity.
	* Entities can be parented to one-another via 'Attach', or 'SetParent'.
	* The Entity class may be extended, creating an 'Actor'. */
	class ENGINE_API Entity : public GameObject
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(GameObject)
		friend class World;
		friend class Component;

		/////////////////
		///   Types   ///
	public:

		/** The different physics modes an Entity can be in. */
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

		struct PhysicsState final
		{
			float Mass = 1.f;

			Vec3 LinearMotionFactor = { 1.f, 1.f, 1.f };

			Vec3 AngularMotionFactor = { 1.f, 1.f, 1.f, };

			float Friction = 0.5f;

			float RollingFriction = 0.f;
		};

		////////////////////////
		///   Constructors   ///
	public:

		Entity();
		~Entity() override;

		///////////////////
		///   Methods   ///
	public:

		void ToArchive(ArchiveWriter& writer) const override;

		void FromArchive(const ArchiveReader& reader) override;

		Vec3 GetLocation() const final override;

		Vec3 GetWorldLocation() const final override;

		void SetLocation(const Vec3& location) final override;

		void SetWorldLocation(const Vec3& location) final override;

		void Translate(const Vec3& vec) final override;

		void TranslateGlobal(const Vec3& vec) final override;

		Quat GetRotation() const final override;

		Quat GetWorldRotation() const final override;

		void SetRotation(const Quat& rot) final override;

		void SetWorldRotation(const Quat& rot) final override;

		void Rotate(const Vec3& axis, Angle angle) final override;

		void RotateGlobal(const Vec3& axis, Angle angle) final override;

		Vec3 GetScale() const final override;

		void SetScale(const Vec3& scale) final override;

		void Scale(const Vec3& vec) final override;

		Mat4 GetTransformationMatrix() const final override;

		const Transform& GetTransform() const
		{
			return _transform;
		}

		FORCEINLINE Entity* GetParent() final override
		{
			return _parent;
		}

		FORCEINLINE const Entity* GetParent() const final override
		{
			return _parent;
		}

		/** Returns the name of this Entity. */
		FORCEINLINE const String& GetName() const /*&*/
		{
			return _name;
		}

		/** Returns whether this Entity is an Actor.
		* An 'Actor' is any class that extends 'Entity'. */
		bool IsActor() const;

		/** Returns the Actor that this Entity is directly (or indirectly) parented to.
		* NOTE: If this Entity is itself an Actor, returns a pointer to itself.
		* NOTE: If this Entity is not attached to an Actor, returns 'null'. */
		Entity* GetActor();

		/** Returns the Actor that this Entity is directly (or indirectly) attached to.
		* NOTE: If this Entity is itself an Actor, returns a pointer to itself.
		* NOTE: If this Entity is not attached to an Actor, returns 'null'. */
		const Entity* GetActor() const;

		/** Returns whether this Entity is parented to the given Entity (directly or indirectly). */
		bool IsParentedTo(const Entity& entity) const;

		/** Sets the parent of this Entity as the given Entity.
		* parent: The Entity being parented to. Use 'nullptr' for no parent. */
		void SetParent(Entity* parent, SetParentOffsetMode mode = SP_KeepWorldOffset);

		/** Connects a new instance of the given Component type to this Entity. */
		template <class T>
		T& Connect();

		/** Parents a new instance of the given type to this Entity.
		* Returns a reference to the new object. */
		template <class T>
		T& Attach();

		/** Parents a new instance of the given type to this Entity.
		* Returns a reference to the new object.
		* Sets the name of the spawned Entity to the given name. */
		template <class T>
		T& Attach(String name);

		/** Enumerates all components of the given type connected to this Entity. */
		template <class T = Component>
		auto EnumerateConnected()
		{
			Array<T*> result;

			for (auto& component : _components)
			{
				if (auto c = Cast<T>(*component))
				{
					result.Add(c);
				}
			}

			return result;
		}

		/** Enumerates all components of the given type connected to this Entity. */
		template <class T = Component>
		auto EnumerateConnected() const
		{
			Array<const T*> result;

			for (const auto& component : _components)
			{
				if (auto c = Cast<T>(*component))
				{
					result.Add(c);
				}
			}

			return result;
		}

		/** Enumerates all Entities attached to this Entity (children). */
		template <class T = Entity>
		auto EnumerateChildren()
		{
			Array<T*> result;

			for (auto& child : _children)
			{
				if (auto c = Cast<T>(*child))
				{
					result.Add(c);
				}
			}

			return result;
		}

		/** Enumerates all Entities attached to this Entity (children). */
		template <class T = Entity>
		auto EnumerateChildren() const
		{
			Array<const T*> result;

			for (const auto& child : _children)
			{
				if (auto c = Cast<T>(*child))
				{
					result.Add(c);
				}
			}

			return result;
		}

		/** Returns the current PhysicsMode of this Entity. */
		FORCEINLINE PhysicsMode GetPhysicsMode() const
		{
			return _physicsMode;
		}

		/** Sets the current PhysicsMode of this Entity. */
		void SetPhysicsMode(PhysicsMode mode);

		/** Returns whether this Entity is physically dynamic. */
		FORCEINLINE bool IsDynamic() const
		{
			return this->GetPhysicsMode() == PhysicsMode::Dynamic;
		}

		/** Returns the mass of this Entity. */
		FORCEINLINE float GetMass() const
		{
			return _physicsState.Mass;
		}

		/** Sets the mass of this Entity. */
		void SetMass(float mass);

		/** Gets the linear motion factor for this Entity.
		* NOTE: This property is only relevant for Dynamic entities. */
		FORCEINLINE Vec3 GetLinearMotionFactor() const
		{
			return _physicsState.LinearMotionFactor;
		}

		/** Sets the linear motion factor for this Entity.
		* NOTE: This property is only relevant for Dynamic entities. */
		void SetLinearMotionFactor(const Vec3& factor);

		/** Gets the angular motion factor for this Entity.
		* NOTE: This property is only relevant for Dynamic entities. */
		FORCEINLINE Vec3 GetAngularMotionFactor() const
		{
			return _physicsState.AngularMotionFactor;
		}

		/** Sets the angular motion factor for this Entity.
		* NOTE: This property is only relevant for Dynamic entities. */
		void SetAngularMotionFactor(const Vec3& factor);

		/** Gets the friction for this Entity. */
		FORCEINLINE float GetFriction() const
		{
			return _physicsState.Friction;
		}

		/** Sets the friction for this Entity. */
		void SetFriction(float friction);

		/** Gets the rolling friction for this Entity. */
		FORCEINLINE float GetRollingFriction() const
		{
			return _physicsState.RollingFriction;
		}

		/** Sets the rolling friction for this Entity. */
		void SetRollingFriction(float rollingFriction);

		/** Gets the linear velocity of this Entity.
		* NOTE: For non-dynamic Entities, this will be zero. */
		Vec3 GetLinearVelocity() const;

		/** Sets the linear velocity of this Entity.
		* NOTE: For non-dynamic Entities, this will have no effect. */
		void SetLinearVelocity(const Vec3& linearVelocity);

		/** Gets the angular velocity of this Entity.
		* NOTE: For non-dynamic Entities, this will be zero. */
		Vec3 GetAngularVelocity() const;

		/** Sets the angular velocity of this Entity.
		* NOTE: For non-dynamic Entities, this will have no effect. */
		void SetAngularVelocity(const Vec3& angularVelocity);

		/** Applys the given force to this Entity. 
		* NOTE: If this Entity's physics mode is not 'PhysicsMode::Dynamic', this does nothing. */
		void ApplyForce(const Vec3& force, const Vec3& offset = Vec3::Zero);

		/** Applys the given impulse to this Entity.
		* NOTE: If this Entity's physics mode is not 'PhysicsMode::Dynamic', this does nothing. */
		void ApplyImpulse(const Vec3& impulse, const Vec3& offset = Vec3::Zero);

		/** Applys the given torque to this Entity.
		* NOTE: If this Entity's physics mode is not 'PhysicsMode::Dynamic', this does nothing. */
		void ApplyTorque(const Vec3& torque);

		/** Applys the given torque impulse to this Entity.
		* NOTE: If this Entity's physics mode is not 'PhysicsMode::Dynamic', this does nothing. */
		void ApplyTorqueImpulse(const Vec3& torque);

	protected:

		void OnInitialize() override;

		void OnDestroy() override;

	private:

		void EDITOR_SetName(String name);

		void UpdatePhysicsMode();

		void UpdatePhysicsState();

		void UpdatePhysicsTransform();

		////////////////
		///   Data   ///
	private:

		/** Entity data */
		String _name;
		Array<Component*> _components;

		/** Spatial data */
		Transform _transform;
		Entity* _parent;
		Array<Entity*> _children;

		/** Physics data */
		PhysicsState _physicsState;
		PhysicsMode _physicsMode;
	};
}

REFLECTABLE_ENUM(ENGINE_API, Willow::Entity::PhysicsMode)
