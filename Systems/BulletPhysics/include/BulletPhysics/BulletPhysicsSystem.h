// BulletPhysicsSystem.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <memory>
#include <Core/Memory/Buffers/TLinkedBuffer.h>
#include <Engine/Systems/PhysicsSystem.h>
#include <Engine/Containers/GTable.h>
#include "config.h"
#include "Forwards.h"

namespace willow
{
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

		void update(World& world) override;

		void debug_draw(RenderSystem& render) override;

		void create_entity(Handle<Entity> entity, Handle<Entity> parent, Transform& transform, Entity::PhysicsMode mode, Entity::PhysicsState state) override;

		void destroy_entity(Handle<Entity> entity) override;

		void set_entity_parent(Handle<Entity> entity, Handle<Entity> parent) override;

		void update_entity_transform(Handle<Entity> entity) override;

		void set_entity_physics_mode(Handle<Entity> entity, Entity::PhysicsMode mode) override;

		void set_entity_physics_state(Handle<Entity> entity, Entity::PhysicsState state) override;

		void get_entity_linear_velocity(Vec3& outLinearVelocity, Handle<Entity> entity) override;

		void set_entity_linear_velocity(Handle<Entity> entity, const Vec3& linearVelocity) override;

		void get_entity_angular_velocity(Vec3& outAngularVelocity, Handle<Entity> entity) override;

		void set_entity_angular_velocity(Handle<Entity> entity, const Vec3& angularVelocity) override;

		void apply_force(Handle<Entity> entity, const Vec3& force, const Vec3& offset) override;

		void apply_impulse(Handle<Entity> entity, const Vec3& impulse, const Vec3& offset) override;

		void apply_torque(Handle<Entity> entity, const Vec3& torque) override;

		void apply_torque_impulse(Handle<Entity> entity, const Vec3& torque) override;

		void create_collider(Handle<SphereColliderComponent> component, Handle<Entity> entity, const Transform& transform, SphereColliderComponent::Shape shape) override;

		void create_collider(Handle<CapsuleColliderComponent> component, Handle<Entity> entity, const Transform& transform, CapsuleColliderComponent::Shape shape) override;

		void create_collider(Handle<StaticMeshColliderComponent> component, Handle<Entity> entity, const Transform& transform, StaticMeshColliderComponent::Shape shape) override;

		void destroy_collider(Handle<SphereColliderComponent> component) override;

		void destroy_collider(Handle<CapsuleColliderComponent> component) override;

		void destroy_collider(Handle<StaticMeshColliderComponent> component) override;

		void set_collider_transform(Handle<SphereColliderComponent> component, const Transform& transform) override;

		void set_collider_transform(Handle<CapsuleColliderComponent> component, const Transform& transform) override;

		void set_collider_transform(Handle<StaticMeshColliderComponent> component, const Transform& transform) override;

		void set_collider_shape(Handle<SphereColliderComponent> component, SphereColliderComponent::Shape shape) override;

		void set_collider_shape(Handle<CapsuleColliderComponent> component, CapsuleColliderComponent::Shape shape) override;

		void set_collider_shape(Handle<StaticMeshColliderComponent> component, StaticMeshColliderComponent::Shape shape) override;

		void create_character_controller(
			Handle<CharacterControllerComponent> component,
			Handle<Entity> entity,
			Handle<PrimitiveColliderComponent> collider,
			CharacterControllerComponent::Settings settings) override;

		void set_character_controller_collider(Handle<CharacterControllerComponent> component, Handle<PrimitiveColliderComponent> collider) override;

		void character_controller_jump(Handle<CharacterControllerComponent> component) override;

		void character_controller_on_ground(Handle<CharacterControllerComponent> component, bool& out) override;

		void character_controller_walk(Handle<CharacterControllerComponent> component, const Vec2& direction) override;

		////////////////
		///   Data   ///
	private:
		
		// Physics world and configuration
		std::unique_ptr<PhysicsWorld> _physics_world;
		
		// Entity physics objects
		TLinkedBuffer<EntityCollider> _entity_colliders;
		TLinkedBuffer<RigidBody> _rigid_bodies;
		TLinkedBuffer<GhostBody> _ghost_bodies;

		// Entity data
		TLinkedBuffer<EntityPhysicsData> _entity_physics_data;
		GTable<Entity, EntityPhysicsData*> _entity_data_table;

		// Character controllers
		TLinkedBuffer<CharacterController> _character_controllers;
		GTable<CharacterControllerComponent, CharacterController*> _character_controller_table;

		// Sphere colliders
		TLinkedBuffer<btSphereShape> _sphere_colliders;
		GTable<SphereColliderComponent, btSphereShape*> _sphere_collider_table;

		// Capsule colliders
		TLinkedBuffer<btCapsuleShape> _capsule_colliders;
		GTable<CapsuleColliderComponent, btCapsuleShape*> _capsule_collider_table;

		// Static mesh colliders
		Table<ResourceHandle<StaticMesh>, std::unique_ptr<TriangleMesh>> _triangle_meshes;
		TLinkedBuffer<btBvhTriangleMeshShape> _static_mesh_colliders;
		GTable<StaticMeshColliderComponent, btBvhTriangleMeshShape*> _static_mesh_collider_table;
	};
}
