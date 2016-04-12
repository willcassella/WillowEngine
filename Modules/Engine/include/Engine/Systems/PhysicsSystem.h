// PhysicsSystem.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Forwards/Systems.h"
#include "../System.h"
#include "../Entity.h"
#include "../GHandle.h"
#include "../Components/Physics/SphereColliderComponent.h"
#include "../Components/Physics/CapsuleColliderComponent.h"
#include "../Components/Physics/StaticMeshColliderComponent.h"
#include "../Components/Gameplay/CharacterControllerComponent.h"

namespace Willow
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
		virtual void DebugDraw(RenderSystem& render) = 0;

		/** Creates a new Entity in this PhysicsSystem. */
		virtual void CreateEntity(
			EntityHandle entity, 
			EntityHandle parent, 
			Transform& transform, 
			Entity::PhysicsMode mode, 
			Entity::PhysicsState state) = 0;

		/** Destroys an Entity in this PhysicsSystem. */
		virtual void DestroyEntity(EntityHandle entity) = 0;

		/** Sets the Entity that the given Entity is parented to. */
		virtual void SetEntityParent(EntityHandle entity, EntityHandle parent) = 0;

		/** Sets the Transform of the given Entity. */
		virtual void UpdateEntityTransform(EntityHandle entity) = 0;

		/** Sets the PhysicsMode for the given Entity. */
		virtual void SetEntityPhysicsMode(EntityHandle entity, Entity::PhysicsMode mode) = 0;
		
		/** Sets the PhysicsState of the given Entity. */
		virtual void SetEntityPhysicsState(EntityHandle entity, Entity::PhysicsState state) = 0;

		/** Retreives the linear velocity of the given entity. */
		virtual void GetEntityLinearVelocity(Vec3& outLinearVelocity, EntityHandle entity) = 0;

		/** Sets the linear velocity of the given Entity. */
		virtual void SetEntityLinearVelocity(EntityHandle entity, const Vec3& linearVelocity) = 0;

		/** Retreives the angular velocity of the given entity. */
		virtual void GetEntityAngularVelocity(Vec3& outAngularVelocity, EntityHandle entity) = 0;

		/** Sets the angular velocity of the given entity. */
		virtual void SetEntityAngularVelocity(EntityHandle entity, const Vec3& angularVelocity) = 0;

		/** Applys the given force to this Entity. */
		virtual void ApplyForce(EntityHandle entity, const Vec3& force, const Vec3& offset) = 0;

		/** Applys the given impulse to this Entity. */
		virtual void ApplyImpulse(EntityHandle entity, const Vec3& impulse, const Vec3& offset) = 0;

		/** Applys the given torque to this Entity. */
		virtual void ApplyTorque(EntityHandle entity, const Vec3& torque) = 0;

		/** Applys the given torque impulse to this Entity. */
		virtual void ApplyTorqueImpulse(EntityHandle entity, const Vec3& torque) = 0;

		/** Creates a SphereCollider for the given component. */
		virtual void CreateCollider(
			GHandle<SphereColliderComponent> component, 
			EntityHandle entity, 
			const Transform& transform, 
			SphereColliderComponent::Shape shape) = 0;

		/** Creates a CapsuleCollider for the given component. */
		virtual void CreateCollider(
			GHandle<CapsuleColliderComponent> component, 
			EntityHandle entity, 
			const Transform& transform, 
			CapsuleColliderComponent::Shape shape) = 0;

		/** Creates a StaticMeshCollider for the given component. */
		virtual void CreateCollider(
			GHandle<StaticMeshColliderComponent> component, 
			EntityHandle entity, 
			const Transform& transform, 
			StaticMeshColliderComponent::Shape shape) = 0;

		/** Destroys the SphereCollider for the given component. */
		virtual void DestroyCollider(GHandle<SphereColliderComponent> component) = 0;

		/** Destroys the CapsuleCollider for the given component. */
		virtual void DestroyCollider(GHandle<CapsuleColliderComponent> component) = 0;

		/** Destroys the StaticMeshCollider for the given component. */
		virtual void DestroyCollider(GHandle<StaticMeshColliderComponent> component) = 0;

		/** Sets the transform for the given component. */
		virtual void SetColliderTransform(GHandle<SphereColliderComponent> component, const Transform& transform) = 0;

		/** Sets the transform for the given component. */
		virtual void SetColliderTransform(GHandle<CapsuleColliderComponent> component, const Transform& transform) = 0;

		/** Sets the transform for the given component. */
		virtual void SetColliderTransform(GHandle<StaticMeshColliderComponent> component, const Transform& transform) = 0;

		/** Sets the shape for the given component. */
		virtual void SetColliderShape(GHandle<SphereColliderComponent> component, SphereColliderComponent::Shape shape) = 0;

		/** Sets the shape for the given component. */
		virtual void SetColliderShape(GHandle<CapsuleColliderComponent> component, CapsuleColliderComponent::Shape shape) = 0;

		/** Sets the shape for the given component. */
		virtual void SetColliderShape(GHandle<StaticMeshColliderComponent> component, StaticMeshColliderComponent::Shape shape) = 0;

		virtual void CreateCharacterController(
			GHandle<CharacterControllerComponent> component, 
			EntityHandle entity, 
			GHandle<PrimitiveColliderComponent> collider, 
			CharacterControllerComponent::Settings settings) = 0;

		virtual void CharacterControllerJump(GHandle<CharacterControllerComponent> component) = 0;

		virtual void CharacterControllerOnGround(GHandle<CharacterControllerComponent> component, bool& out) = 0;

		virtual void CharacterControllerWalk(GHandle<CharacterControllerComponent> component, const Vec2& direction) = 0;
	};
}
