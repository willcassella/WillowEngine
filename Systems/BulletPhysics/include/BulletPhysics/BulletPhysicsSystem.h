// BulletPhysicsSystem.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <memory>
#include <Core/Memory/Buffers/TLinkedBuffer.h>
#include <Engine/Systems/PhysicsSystem.h>
#include <Engine/Containers/GTable.h>
#include "config.h"

////////////////////
///   Forwards   ///

/** Defined in a Bullet header. */
class btSphereShape;

/** Defined in a Bullet header. */
class btCapsuleShape;

/** Defined in a Bullet header. */
class btBvhTriangleMeshShape;

namespace Willow
{
	/** Defined in 'private/PhysicsWorld.h' */
	class PhysicsWorld;

	/** Defined in 'private/EntityPhysicsData.h' */
	class EntityPhysicsData;

	/** Defined in 'private/EntityCollider.h' */
	class EntityCollider;

	/** Defined in 'private/RigidBody.h' */
	class RigidBody;

	/** Defined in 'private/GhostBody.h' */
	class GhostBody;

	/** Defined in 'private/CharacterController.h' */
	class CharacterController;

	/** Defined in 'private/BulletTriangleMesh.h' */
	class BulletTriangleMesh;

	/////////////////
	///   Types   ///

	class BULLETPHYSICS_API BulletPhysicsSystem final : public PhysicsSystem
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(PhysicsSystem)

		////////////////////////
		///   Constructors   ///
	public:

		BulletPhysicsSystem();
		~BulletPhysicsSystem() override;

		///////////////////
		///   Methods   ///
	public:

		void Update(const World& world) override;

		void DebugDraw(RenderSystem& render) override;

		void CreateEntity(EntityHandle entity, EntityHandle parent, Transform& transform, Entity::PhysicsMode mode, Entity::PhysicsState state) override;

		void DestroyEntity(EntityHandle entity) override;

		void SetEntityParent(EntityHandle entity, EntityHandle parent) override;

		void UpdateEntityTransform(EntityHandle entity) override;

		void SetEntityPhysicsMode(EntityHandle entity, Entity::PhysicsMode mode) override;

		void SetEntityPhysicsState(EntityHandle entity, Entity::PhysicsState state) override;

		void GetEntityLinearVelocity(Vec3& outLinearVelocity, EntityHandle entity) override;

		void SetEntityLinearVelocity(EntityHandle entity, const Vec3& linearVelocity) override;

		void GetEntityAngularVelocity(Vec3& outAngularVelocity, EntityHandle entity) override;

		void SetEntityAngularVelocity(EntityHandle entity, const Vec3& angularVelocity) override;

		void ApplyForce(EntityHandle entity, const Vec3& force, const Vec3& offset) override;

		void ApplyImpulse(EntityHandle entity, const Vec3& impulse, const Vec3& offset) override;

		void ApplyTorque(EntityHandle entity, const Vec3& torque) override;

		void ApplyTorqueImpulse(EntityHandle entity, const Vec3& torque) override;

		void CreateCollider(GHandle<SphereColliderComponent> component, EntityHandle entity, const Transform& transform, SphereColliderComponent::Shape shape) override;

		void CreateCollider(GHandle<CapsuleColliderComponent> component, EntityHandle entity, const Transform& transform, CapsuleColliderComponent::Shape shape) override;

		void CreateCollider(GHandle<StaticMeshColliderComponent> component, EntityHandle entity, const Transform& transform, StaticMeshColliderComponent::Shape shape) override;

		void DestroyCollider(GHandle<SphereColliderComponent> component) override;

		void DestroyCollider(GHandle<CapsuleColliderComponent> component) override;

		void DestroyCollider(GHandle<StaticMeshColliderComponent> component) override;

		void SetColliderTransform(GHandle<SphereColliderComponent> component, const Transform& transform) override;

		void SetColliderTransform(GHandle<CapsuleColliderComponent> component, const Transform& transform) override;

		void SetColliderTransform(GHandle<StaticMeshColliderComponent> component, const Transform& transform) override;

		void SetColliderShape(GHandle<SphereColliderComponent> component, SphereColliderComponent::Shape shape) override;

		void SetColliderShape(GHandle<CapsuleColliderComponent> component, CapsuleColliderComponent::Shape shape) override;

		void SetColliderShape(GHandle<StaticMeshColliderComponent> component, StaticMeshColliderComponent::Shape shape) override;

		void CreateCharacterController(
			GHandle<CharacterControllerComponent> component,
			EntityHandle entity,
			GHandle<PrimitiveColliderComponent> collider,
			CharacterControllerComponent::Settings settings) override;

		void CharacterControllerJump(GHandle<CharacterControllerComponent> component) override;

		void CharacterControllerOnGround(GHandle<CharacterControllerComponent> component, bool& out) override;

		void CharacterControllerWalk(GHandle<CharacterControllerComponent> component, const Vec2& direction) override;

		////////////////
		///   Data   ///
	private:
		
		// Physics world and configuration
		std::unique_ptr<PhysicsWorld> _physicsWorld;
		
		// Entity physics objects
		TLinkedBuffer<EntityCollider> _entityColliders;
		TLinkedBuffer<RigidBody> _rigidBodies;
		TLinkedBuffer<GhostBody> _ghostBodies;

		// Entity data
		TLinkedBuffer<EntityPhysicsData> _entityPhysicsData;
		GTable<Entity, EntityPhysicsData*> _entityDataTable;

		// Character controllers
		TLinkedBuffer<CharacterController> _characterControllers;
		GTable<CharacterControllerComponent, CharacterController*> _characterControllerTable;

		// Sphere colliders
		TLinkedBuffer<btSphereShape> _sphereColliders;
		GTable<SphereColliderComponent, btSphereShape*> _sphereColliderTable;

		// Capsule colliders
		TLinkedBuffer<btCapsuleShape> _capsuleColliders;
		GTable<CapsuleColliderComponent, btCapsuleShape*> _capsuleColliderTable;

		// Static mesh colliders
		Table<AssetPtr<StaticMesh>, std::unique_ptr<BulletTriangleMesh>> _triangleMeshes;
		TLinkedBuffer<btBvhTriangleMeshShape> _staticMeshColliders;
		GTable<StaticMeshColliderComponent, btBvhTriangleMeshShape*> _staticMeshColliderTable;
	};
}
