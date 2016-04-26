// PhysicsSystem.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Forwards/Systems.h"
#include "../System.h"
#include "../Entity.h"
#include "../Handle.h"
#include "../Components/Physics/SphereColliderComponent.h"
#include "../Components/Physics/CapsuleColliderComponent.h"
#include "../Components/Physics/StaticMeshColliderComponent.h"
#include "../Components/Gameplay/CharacterControllerComponent.h"

namespace willow
{
	/** Defines the interface for a PhysicsSystem. */
	class ENGINE_API PhysicsSystem : public System
	{
		///////////////////////
		///   Information   ///
	public:
		
		REFLECTABLE_CLASS
		EXTENDS(System)

		///////////////////
		///   Methods   ///
	public:

		/** Debug draws the current state of the physics world. */
		virtual void debug_draw(RenderSystem& render) = 0;

		/** Creates a new Entity in this PhysicsSystem. */
		virtual void create_entity(
			Handle<Entity> entity, 
			Handle<Entity> parent, 
			Transform& transform, 
			Entity::PhysicsMode mode, 
			Entity::PhysicsState state) = 0;

		/** Destroys an Entity in this PhysicsSystem. */
		virtual void destroy_entity(Handle<Entity> entity) = 0;

		/** Sets the Entity that the given Entity is parented to. */
		virtual void set_entity_parent(Handle<Entity> entity, Handle<Entity> parent) = 0;

		/** Sets the Transform of the given Entity. */
		virtual void update_entity_transform(Handle<Entity> entity) = 0;

		/** Sets the PhysicsMode for the given Entity. */
		virtual void set_entity_physics_mode(Handle<Entity> entity, Entity::PhysicsMode mode) = 0;
		
		/** Sets the PhysicsState of the given Entity. */
		virtual void set_entity_physics_state(Handle<Entity> entity, Entity::PhysicsState state) = 0;

		/** Retreives the linear velocity of the given entity. */
		virtual void get_entity_linear_velocity(Vec3& outLinearVelocity, Handle<Entity> entity) = 0;

		/** Sets the linear velocity of the given Entity. */
		virtual void set_entity_linear_velocity(Handle<Entity> entity, const Vec3& linearVelocity) = 0;

		/** Retreives the angular velocity of the given entity. */
		virtual void get_entity_angular_velocity(Vec3& outAngularVelocity, Handle<Entity> entity) = 0;

		/** Sets the angular velocity of the given entity. */
		virtual void set_entity_angular_velocity(Handle<Entity> entity, const Vec3& angularVelocity) = 0;

		/** Applys the given force to this Entity. */
		virtual void apply_force(Handle<Entity> entity, const Vec3& force, const Vec3& offset) = 0;

		/** Applys the given impulse to this Entity. */
		virtual void apply_impulse(Handle<Entity> entity, const Vec3& impulse, const Vec3& offset) = 0;

		/** Applys the given torque to this Entity. */
		virtual void apply_torque(Handle<Entity> entity, const Vec3& torque) = 0;

		/** Applys the given torque impulse to this Entity. */
		virtual void apply_torque_impulse(Handle<Entity> entity, const Vec3& torque) = 0;

		/** Creates a SphereCollider for the given component. */
		virtual void create_collider(
			Handle<SphereColliderComponent> component, 
			Handle<Entity> entity,
			const Transform& transform, 
			SphereColliderComponent::Shape shape) = 0;

		/** Creates a CapsuleCollider for the given component. */
		virtual void create_collider(
			Handle<CapsuleColliderComponent> component, 
			Handle<Entity> entity,
			const Transform& transform, 
			CapsuleColliderComponent::Shape shape) = 0;

		/** Creates a StaticMeshCollider for the given component. */
		virtual void create_collider(
			Handle<StaticMeshColliderComponent> component, 
			Handle<Entity> entity,
			const Transform& transform, 
			StaticMeshColliderComponent::Shape shape) = 0;

		/** Destroys the SphereCollider for the given component. */
		virtual void destroy_collider(Handle<SphereColliderComponent> component) = 0;

		/** Destroys the CapsuleCollider for the given component. */
		virtual void destroy_collider(Handle<CapsuleColliderComponent> component) = 0;

		/** Destroys the StaticMeshCollider for the given component. */
		virtual void destroy_collider(Handle<StaticMeshColliderComponent> component) = 0;

		/** Sets the transform for the given component. */
		virtual void set_collider_transform(Handle<SphereColliderComponent> component, const Transform& transform) = 0;

		/** Sets the transform for the given component. */
		virtual void set_collider_transform(Handle<CapsuleColliderComponent> component, const Transform& transform) = 0;

		/** Sets the transform for the given component. */
		virtual void set_collider_transform(Handle<StaticMeshColliderComponent> component, const Transform& transform) = 0;

		/** Sets the shape for the given component. */
		virtual void set_collider_shape(Handle<SphereColliderComponent> component, SphereColliderComponent::Shape shape) = 0;

		/** Sets the shape for the given component. */
		virtual void set_collider_shape(Handle<CapsuleColliderComponent> component, CapsuleColliderComponent::Shape shape) = 0;

		/** Sets the shape for the given component. */
		virtual void set_collider_shape(Handle<StaticMeshColliderComponent> component, StaticMeshColliderComponent::Shape shape) = 0;

		virtual void create_character_controller(
			Handle<CharacterControllerComponent> component, 
			Handle<Entity> entity,
			Handle<PrimitiveColliderComponent> collider, 
			CharacterControllerComponent::Settings settings) = 0;

		virtual void destroy_character_controller(Handle<CharacterControllerComponent> component) = 0;

		virtual void set_character_controller_collider(Handle<CharacterControllerComponent> component, Handle<PrimitiveColliderComponent> collider) = 0;

		virtual void character_controller_jump(Handle<CharacterControllerComponent> component) = 0;

		virtual void character_controller_on_ground(Handle<CharacterControllerComponent> component, bool& out) = 0;

		virtual void character_controller_walk(Handle<CharacterControllerComponent> component, const Vec2& direction) = 0;
	};
}
