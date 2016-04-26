// Entity.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "GameObject.h"
#include "Transform.h"

namespace willow
{
	/////////////////
	///   Types   ///

	/** Behavior for handling the transform of a GameObject upon setting the parent.
	* Used by the 'set_parent' member function. */
	enum SetParentOffsetMode
	{
		/** When this GameObjects's parent is set, its location of moved to the Origin of the new parent (world center for 'null'). */
		SP_Move_To_Origin,

		/** The transform is set relative to the new parent as it was to the old parent. */
		SP_Keep_Local_Offset,

		/** The transform is set in such a way that the object does not move at all (in world space) when the parent is set. */
		SP_Keep_World_Offset
	};

	/** An 'Entity' is a collection of Components that should be together thought of as a single object.
	* Components can be added and removed ("connected" and "disconnected") from an Entity, but they cannot be moved between Entities.
	* Components are always connected to a single Entity.
	* Entities can be parented to one-another via 'attach', or 'set_parent'.
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
			float mass = 1.f;

			Vec3 linear_motion_factor = { 1.f, 1.f, 1.f };

			Vec3 angular_motion_factor = { 1.f, 1.f, 1.f, };

			float friction = 0.5f;

			float rolling_friction = 0.f;
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

		Vec3 get_location() const final override;

		Vec3 get_world_location() const final override;

		void set_location(const Vec3& location) final override;

		void set_world_location(const Vec3& location) final override;

		void translate(const Vec3& vec) final override;

		void translate_global(const Vec3& vec) final override;

		Quat get_rotation() const final override;

		Quat get_world_rotation() const final override;

		void set_rotation(const Quat& rot) final override;

		void set_world_rotation(const Quat& rot) final override;

		void rotate(const Vec3& axis, Angle angle) final override;

		void rotate_global(const Vec3& axis, Angle angle) final override;

		Vec3 get_scale() const final override;

		void set_scale(const Vec3& scale) final override;

		void scale(const Vec3& vec) final override;

		Mat4 get_transformation_matrix() const final override;

		const Transform& get_transform() const
		{
			return this->_transform;
		}

		FORCEINLINE Entity* get_parent() final override
		{
			return this->_parent;
		}

		FORCEINLINE const Entity* get_parent() const final override
		{
			return this->_parent;
		}

		/** Returns the name of this Entity. */
		FORCEINLINE const String& get_name() const /*&*/
		{
			return this->_name;
		}

		/** Returns whether this Entity is an Actor.
		* An 'Actor' is any class that extends 'Entity'. */
		bool is_actor() const;

		/** Returns the Actor that this Entity is directly (or indirectly) parented to.
		* NOTE: If this Entity is itself an Actor, returns a pointer to itself.
		* NOTE: If this Entity is not attached to an Actor, returns 'null'. */
		Entity* get_actor();

		/** Returns the Actor that this Entity is directly (or indirectly) attached to.
		* NOTE: If this Entity is itself an Actor, returns a pointer to itself.
		* NOTE: If this Entity is not attached to an Actor, returns 'null'. */
		const Entity* get_actor() const;

		/** Returns whether this Entity is parented to the given Entity (directly or indirectly). */
		bool is_parented_to(const Entity& entity) const;

		/** Sets the parent of this Entity as the given Entity.
		* parent: The Entity being parented to. Use 'nullptr' for no parent. */
		void set_parent(Entity* parent, SetParentOffsetMode mode = SP_Keep_World_Offset);

		/** Connects a new instance of the given Component type to this Entity. */
		template <class T>
		T& connect();

		/** Parents a new instance of the given type to this Entity.
		* Returns a reference to the new object. */
		template <class T>
		auto attach() -> std::enable_if_t<std::is_base_of<Component, T>::value, T&>;

		/** Parents a new instance of the given type to this Entity.
		* Returns a reference to the new object. */
		template <class T>
		auto attach() -> std::enable_if_t<std::is_base_of<Entity, T>::value, T&>;

		/** Parents a new instance of the given type to this Entity.
		* Returns a reference to the new object.
		* Sets the name of the spawned Entity to the given name. */
		template <class T>
		auto attach(String name) -> std::enable_if_t<std::is_base_of<Component, T>::value, T&>;
		
		/** Parents a new instance of the given type to this Entity.
		* Returns a reference to the new object.
		* Sets the name of the spawned Entity to the given name. */
		template <class T>
		auto attach(String name) -> std::enable_if_t<std::is_base_of<Entity, T>::value, T&>;

		/** Enumerates all components of the given type connected to this Entity. */
		template <class T = Component>
		auto enumerate_connected()
		{
			Array<T*> result;

			for (auto& component : this->_components)
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
		auto enumerate_connected() const
		{
			Array<const T*> result;

			for (const auto& component : this->_components)
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
		auto enumerate_children()
		{
			Array<T*> result;

			for (auto& child : this->_children)
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
		auto enumerate_children() const
		{
			Array<const T*> result;

			for (const auto& child : this->_children)
			{
				if (auto c = Cast<T>(*child))
				{
					result.Add(c);
				}
			}

			return result;
		}

		/** Returns the current PhysicsMode of this Entity. */
		FORCEINLINE PhysicsMode get_physics_mode() const
		{
			return this->_physics_mode;
		}

		/** Sets the current PhysicsMode of this Entity. */
		void set_physics_mode(PhysicsMode mode);

		/** Returns whether this Entity is physically dynamic. */
		FORCEINLINE bool is_dynamic() const
		{
			return this->get_physics_mode() == PhysicsMode::Dynamic;
		}

		/** Returns the mass of this Entity. */
		FORCEINLINE float get_mass() const
		{
			return this->_physics_state.mass;
		}

		/** Sets the mass of this Entity. */
		void set_mass(float mass);

		/** Gets the linear motion factor for this Entity.
		* NOTE: This property is only relevant for Dynamic entities. */
		FORCEINLINE Vec3 get_linear_motion_factor() const
		{
			return this->_physics_state.linear_motion_factor;
		}

		/** Sets the linear motion factor for this Entity.
		* NOTE: This property is only relevant for Dynamic entities. */
		void set_linear_motion_factor(const Vec3& factor);

		/** Gets the angular motion factor for this Entity.
		* NOTE: This property is only relevant for Dynamic entities. */
		FORCEINLINE Vec3 get_angular_motion_factor() const
		{
			return this->_physics_state.angular_motion_factor;
		}

		/** Sets the angular motion factor for this Entity.
		* NOTE: This property is only relevant for Dynamic entities. */
		void set_angular_motion_factor(const Vec3& factor);

		/** Gets the friction for this Entity. */
		FORCEINLINE float get_friction() const
		{
			return this->_physics_state.friction;
		}

		/** Sets the friction for this Entity. */
		void set_friction(float friction);

		/** Gets the rolling friction for this Entity. */
		FORCEINLINE float get_rolling_friction() const
		{
			return this->_physics_state.rolling_friction;
		}

		/** Sets the rolling friction for this Entity. */
		void set_rolling_friction(float rollingFriction);

		/** Gets the linear velocity of this Entity.
		* NOTE: For non-dynamic Entities, this will be zero. */
		Vec3 get_linear_velocity() const;

		/** Sets the linear velocity of this Entity.
		* NOTE: For non-dynamic Entities, this will have no effect. */
		void set_linear_velocity(const Vec3& linearVelocity);

		/** Gets the angular velocity of this Entity.
		* NOTE: For non-dynamic Entities, this will be zero. */
		Vec3 get_angular_velocity() const;

		/** Sets the angular velocity of this Entity.
		* NOTE: For non-dynamic Entities, this will have no effect. */
		void set_angular_velocity(const Vec3& angularVelocity);

		/** Applys the given force to this Entity. 
		* NOTE: If this Entity's physics mode is not 'PhysicsMode::Dynamic', this does nothing. */
		void apply_force(const Vec3& force, const Vec3& offset = Vec3::Zero);

		/** Applys the given impulse to this Entity.
		* NOTE: If this Entity's physics mode is not 'PhysicsMode::Dynamic', this does nothing. */
		void apply_impulse(const Vec3& impulse, const Vec3& offset = Vec3::Zero);

		/** Applys the given torque to this Entity.
		* NOTE: If this Entity's physics mode is not 'PhysicsMode::Dynamic', this does nothing. */
		void apply_torque(const Vec3& torque);

		/** Applys the given torque impulse to this Entity.
		* NOTE: If this Entity's physics mode is not 'PhysicsMode::Dynamic', this does nothing. */
		void apply_torque_impulse(const Vec3& torque);

		/** Called when this Entity (which is set as a 'Ghost' object) collides with another object. 
		* TODO: Make this protected */
		virtual void on_collision(Entity& collidee);

	protected:

		void on_initialize() override;

		void on_destroy() override;

	private:

		void EDITOR_set_name(String name);

		void update_physics_mode();

		void update_physics_state();

		void update_physics_transform();

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
		PhysicsState _physics_state;
		PhysicsMode _physics_mode;
	};
}

REFLECTABLE_ENUM(ENGINE_API, willow::Entity::PhysicsMode)
