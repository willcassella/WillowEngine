// BulletPhysicsSystem.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Engine/World.h>
#include "../include/BulletPhysics/BulletPhysicsSystem.h"
#include "../private/DebugDrawer.h"
#include "../private/PhysicsWorld.h"
#include "../private/GhostBody.h"
#include "../private/RigidBody.h"
#include "../private/EntityPhysicsData.h"
#include "../private/CharacterController.h"
#include "../private/TriangleMesh.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::BulletPhysicsSystem);

namespace willow
{
	////////////////////////
	///   Constructors   ///

	BulletPhysicsSystem::BulletPhysicsSystem()
	{
		_physics_world = std::make_unique<PhysicsWorld>();
	}

	BulletPhysicsSystem::~BulletPhysicsSystem()
	{
		// Take all ghost objects out of world (keeps Bullet happy)
		_ghost_bodies.enumerate([this](GhostBody& body)
		{
			this->_physics_world->GetDynamicsWorld().removeCollisionObject(&body);
		});

		// _physics_world must be destroyed first
		_physics_world.release();
	}

	///////////////////
	///   Methods   ///

	void BulletPhysicsSystem::update(World& world)
	{
		// Update the physics world
		this->_physics_world->GetDynamicsWorld().stepSimulation(world.time_step, 1);

		Array<std::pair<Entity*, Entity*>> collisions;

		int numManifolds = _physics_world->GetDynamicsWorld().getDispatcher()->getNumManifolds();
		for (int i = 0; i < numManifolds; i++)
		{
			auto* contactManifold = _physics_world->GetDynamicsWorld().getDispatcher()->getManifoldByIndexInternal(i);
			auto* obA = contactManifold->getBody0();
			auto* obB = contactManifold->getBody1();

			int numContacts = contactManifold->getNumContacts();

			for (int j = 0; j < numContacts; j++)
			{
				btManifoldPoint& pt = contactManifold->getContactPoint(j);
				if (pt.getDistance() < 0.f)
				{
					const btVector3& ptA = pt.getPositionWorldOnA();
					const btVector3& ptB = pt.getPositionWorldOnB();
					const btVector3& normalOnB = pt.m_normalWorldOnB;

					auto* entityA = world.get_object(static_cast<EntityPhysicsData*>(obA->getUserPointer())->entity);
					auto* entityB = world.get_object(static_cast<EntityPhysicsData*>(obB->getUserPointer())->entity);
					
					// Add the collision
					collisions.Add(std::make_pair(entityA, entityB));
				}
			}
		}

		// Dispatch collisions
		for (auto collision : collisions)
		{
			collision.first->on_collision(*collision.second);
			collision.second->on_collision(*collision.first);
		}
	}

	void BulletPhysicsSystem::debug_draw(RenderSystem& render)
	{
		DebugDrawer drawer{ render };
		_physics_world->GetDynamicsWorld().setDebugDrawer(&drawer);
		_physics_world->GetDynamicsWorld().debugDrawWorld();
		_physics_world->GetDynamicsWorld().setDebugDrawer(nullptr);
	}

	void BulletPhysicsSystem::create_entity(
		Handle<Entity> entity, 
		Handle<Entity> parent,
		Transform& transform, 
		Entity::PhysicsMode mode, 
		Entity::PhysicsState state)
	{
		// Create the physics data for this Entity
		auto* data = _entity_physics_data.emplace_new(state, mode, entity, parent, transform);
		_entity_data_table[entity] = data;

		// If the entity is at least a ghost
		if (mode >= Entity::PhysicsMode::Ghost)
		{
			data->ghost_body = _ghost_bodies.emplace_new(*data);
			_physics_world->GetDynamicsWorld().addCollisionObject(data->ghost_body);
		}

		// If the entity is at least kinematic
		if (mode >= Entity::PhysicsMode::Kinematic)
		{
			data->rigid_body = _rigid_bodies.emplace_new(*data);
			_physics_world->GetDynamicsWorld().addRigidBody(data->rigid_body);

			// If the entity IS kinematic
			if (mode == Entity::PhysicsMode::Kinematic)
			{
				data->rigid_body->setMassProps(0, { 0, 0, 0 });
				data->rigid_body->setActivationState(DISABLE_DEACTIVATION);
				data->rigid_body->setCollisionFlags(data->rigid_body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
			}
		}
	}

	void BulletPhysicsSystem::destroy_entity(Handle<Entity> entity)
	{
		// NOTE: Assuming entity colliders have been destroyed
		auto* entityData = _entity_data_table[entity];
		
		// If the entity has a rigid body
		if (entityData->rigid_body)
		{
			_physics_world->GetDynamicsWorld().removeRigidBody(entityData->rigid_body);
		}

		// If the entity has a ghost body
		if (entityData->ghost_body)
		{
			_physics_world->GetDynamicsWorld().removeCollisionObject(entityData->ghost_body);
		}

		_entity_data_table.Remove(entity);
		_entity_physics_data.destroy(entityData);
	}

	void BulletPhysicsSystem::set_entity_parent(Handle<Entity> /*entity*/, Handle<Entity> /*parent*/)
	{
		// TODO
	}

	void BulletPhysicsSystem::update_entity_transform(Handle<Entity> entity)
	{
		_entity_data_table.Find(entity, [&](EntityPhysicsData* data)
		{
			data->collider.setLocalScaling(convert_to_bullet(data->transform->scale));
			btTransform transform{ convert_to_bullet(data->transform->rotation), convert_to_bullet(data->transform->location) };

			// If we have a GhostBody
			if (data->ghost_body)
			{
				data->ghost_body->setWorldTransform(transform);
			}

			// If we have a RigidBody
			if (data->rigid_body)
			{
				data->rigid_body->setWorldTransform(transform);
			}
		});
	}

	void BulletPhysicsSystem::set_entity_physics_mode(Handle<Entity> entity, Entity::PhysicsMode mode)
	{
		_entity_data_table.Find(entity, [=](EntityPhysicsData* data)
		{
			// Set the new mode
			data->mode = mode;

			// If we have a RigidBody
			if (data->rigid_body)
			{
				// If we don't want to have one
				if (mode < Entity::PhysicsMode::Kinematic)
				{
					// If we don't have any constraints
					if (data->rigid_body->getNumConstraintRefs() == 0)
					{
						// Destroy it
						_physics_world->GetDynamicsWorld().removeRigidBody(data->rigid_body);
						data->rigid_body->disable(*data);
						_rigid_bodies.destroy(data->rigid_body);
						data->rigid_body = nullptr;
					}
					else
					{
						// Set it up purely for constraints
						data->rigid_body->setCollisionShape(nullptr);
						data->rigid_body->setCollisionFlags(
							data->rigid_body->getCollisionFlags() |
							btCollisionObject::CF_KINEMATIC_OBJECT |
							btCollisionObject::CF_NO_CONTACT_RESPONSE);
					}
				}
			}
			else
			{
				// If we want to have one
				if (mode >= Entity::PhysicsMode::Kinematic)
				{
					// Create one
					data->rigid_body = _rigid_bodies.emplace_new(*data);
					_physics_world->GetDynamicsWorld().addRigidBody(data->rigid_body);
					
					if (mode == Entity::PhysicsMode::Kinematic)
					{
						data->rigid_body->setMassProps(0, { 0, 0, 0 });
						data->rigid_body->setActivationState(DISABLE_DEACTIVATION);
						data->rigid_body->setCollisionFlags(data->rigid_body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
					}
				}
			}

			// If we have a Ghost body
			if (data->ghost_body)
			{
				// If we don't want to have a ghost body
				if (mode == Entity::PhysicsMode::Transient)
				{
					// Destroy it
					_physics_world->GetDynamicsWorld().removeCollisionObject(data->ghost_body);
					_ghost_bodies.destroy(data->ghost_body);
					data->ghost_body = nullptr;
				}
			}
			else
			{
				// If we want to have a GhostBody
				if (mode >= Entity::PhysicsMode::Ghost)
				{
					auto* ghost = _ghost_bodies.emplace_new(*data);
					_physics_world->GetDynamicsWorld().addCollisionObject(data->ghost_body);
				}
			}
		});
	}

	void BulletPhysicsSystem::set_entity_physics_state(Handle<Entity> entity, Entity::PhysicsState state)
	{
		// If the PhysicsObject exists
		_entity_data_table.Find(entity, [&](EntityPhysicsData* data)
		{
			data->state = state;

			// If it's a Kinematic or Rigid body
			if (data->mode >= Entity::PhysicsMode::Kinematic)
			{
				data->rigid_body->setAngularFactor(convert_to_bullet(state.angular_motion_factor));
				data->rigid_body->setLinearFactor(convert_to_bullet(state.linear_motion_factor));
				data->rigid_body->setFriction(state.friction);
				data->rigid_body->setRollingFriction(state.rolling_friction);

				// If it's a rigid body
				if (data->mode == Entity::PhysicsMode::Dynamic)
				{
					btVector3 inertia;
					data->collider.calculateLocalInertia(state.mass, inertia);
					data->rigid_body->setMassProps(state.mass, inertia);
				}
			}
		});
	}

	void BulletPhysicsSystem::get_entity_linear_velocity(Vec3& outLinearVelocity, Handle<Entity> entity)
	{
		auto* entityData = _entity_data_table[entity];

		if (entityData->rigid_body)
		{
			outLinearVelocity = convert_from_bullet(entityData->rigid_body->getLinearVelocity());
		}
	}

	void BulletPhysicsSystem::set_entity_linear_velocity(Handle<Entity> entity, const Vec3& linearVelocity)
	{
		auto* entityData = _entity_data_table[entity];

		if (entityData->rigid_body)
		{
			entityData->rigid_body->setLinearVelocity(convert_to_bullet(linearVelocity));
		}
	}

	void BulletPhysicsSystem::get_entity_angular_velocity(Vec3& outAngularVelocity, Handle<Entity> entity)
	{
		auto* entityData = _entity_data_table[entity];

		if (entityData->rigid_body)
		{
			outAngularVelocity = convert_from_bullet(entityData->rigid_body->getAngularVelocity());
		}
	}

	void BulletPhysicsSystem::set_entity_angular_velocity(Handle<Entity> entity, const Vec3& angularVelocity)
	{
		auto* entityData = _entity_data_table[entity];

		if (entityData->rigid_body)
		{
			entityData->rigid_body->setAngularVelocity(convert_to_bullet(angularVelocity));
		}
	}

	void BulletPhysicsSystem::apply_force(Handle<Entity> entity, const Vec3& force, const Vec3& offset)
	{
		_entity_data_table.Find(entity, [&](EntityPhysicsData* data)
		{
			if (data->rigid_body)
			{
				data->rigid_body->applyForce(convert_to_bullet(force), convert_to_bullet(offset));
			}
		});
	}

	void BulletPhysicsSystem::apply_impulse(Handle<Entity> entity, const Vec3& force, const Vec3& offset)
	{
		_entity_data_table.Find(entity, [&](EntityPhysicsData* data)
		{
			if (data->rigid_body)
			{
				data->rigid_body->applyImpulse(convert_to_bullet(force), convert_to_bullet(offset));
			}
		});
	}

	void BulletPhysicsSystem::apply_torque(Handle<Entity> entity, const Vec3& torque)
	{
		_entity_data_table.Find(entity, [&](EntityPhysicsData* data)
		{
			if (data->rigid_body)
			{
				data->rigid_body->applyTorque(convert_to_bullet(torque));
			}
		});
	}

	void BulletPhysicsSystem::apply_torque_impulse(Handle<Entity> entity, const Vec3& torque)
	{
		_entity_data_table.Find(entity, [&](EntityPhysicsData* data)
		{
			if (data->rigid_body)
			{
				data->rigid_body->applyTorqueImpulse(convert_to_bullet(torque));
			}
		});
	}

	void BulletPhysicsSystem::create_collider(Handle<SphereColliderComponent> component, Handle<Entity> entity, const Transform& transform, SphereColliderComponent::Shape shape)
	{
		auto* entityData = _entity_data_table[entity];

		// Create the sphere collider
		auto* collider = _sphere_colliders.emplace_new(shape.radius);
		collider->setLocalScaling(convert_to_bullet(transform.scale));
		collider->setUserPointer(entityData);
		
		// Add it to the EntityCollider
		entityData->collider.add_child(*collider, transform.location, transform.rotation);
		entityData->update_inertia();

		// Add it to the table
		_sphere_collider_table[component] = collider;
	}

	void BulletPhysicsSystem::create_collider(Handle<CapsuleColliderComponent> component, Handle<Entity> entity, const Transform& transform, CapsuleColliderComponent::Shape shape)
	{
		auto* entityData = _entity_data_table[entity];

		// Create the capsule collider
		btCapsuleShape* collider = nullptr;
		switch (shape.axis)
		{
		case ColliderComponent::ShapeAxis::X:
			collider = _capsule_colliders.emplace_new<btCapsuleShapeX>(shape.radius, shape.height);
			break;
		case ColliderComponent::ShapeAxis::Y:
			collider = _capsule_colliders.emplace_new<btCapsuleShape>(shape.radius, shape.height);
			break;
		case ColliderComponent::ShapeAxis::Z:
			collider = _capsule_colliders.emplace_new<btCapsuleShapeZ>(shape.radius, shape.height);
			break;
		}
		collider->setLocalScaling(convert_to_bullet(transform.scale));
		collider->setUserPointer(entityData);

		// Add it to the entity collider
		entityData->collider.add_child(*collider, transform.location, transform.rotation);
		entityData->update_inertia();

		// Add it to the table
		_capsule_collider_table[component] = collider;
	}

	void BulletPhysicsSystem::create_collider(Handle<StaticMeshColliderComponent> component, Handle<Entity> entity, const Transform& transform, StaticMeshColliderComponent::Shape shape)
	{
		auto* entityData = _entity_data_table[entity];

		// Find or create a mesh for this collider
		auto& mesh = _triangle_meshes[shape.mesh];
		if (!mesh)
		{
			mesh = std::make_unique<TriangleMesh>(shape.mesh);
		}

		// Create the collider
		auto* collider = _static_mesh_colliders.emplace_new(mesh.get(), true);
		collider->setLocalScaling(convert_to_bullet(transform.scale));
		collider->setUserPointer(entityData);

		// Add it to the entity collider
		entityData->collider.add_child(*collider, transform.location, transform.rotation);
		entityData->update_inertia();

		// Add it to the table
		_static_mesh_collider_table[component] = collider;
	}

	void BulletPhysicsSystem::destroy_collider(Handle<SphereColliderComponent> component)
	{
		// Get the collider and its compound
		auto* collider = _sphere_collider_table[component];
		auto* entityData = static_cast<EntityPhysicsData*>(collider->getUserPointer());
		
		// Destroy it
		entityData->collider.remove_child(*collider);
		_sphere_colliders.destroy(collider);
		_sphere_collider_table.Remove(component);
	}

	void BulletPhysicsSystem::destroy_collider(Handle<CapsuleColliderComponent> component)
	{
		// Get the collider and its compound
		auto* collider = _capsule_collider_table[component];
		auto* entityData = static_cast<EntityPhysicsData*>(collider->getUserPointer());

		// Destroy it
		entityData->collider.remove_child(*collider);
		_capsule_collider_table.Remove(component);
		_capsule_colliders.destroy(collider);
	}

	void BulletPhysicsSystem::destroy_collider(Handle<StaticMeshColliderComponent> component)
	{
		// Get the collider and its compound
		auto* collider = _static_mesh_collider_table[component];
		auto* entityData = static_cast<EntityPhysicsData*>(collider->getUserPointer());

		// Destroy it
		entityData->collider.remove_child(*collider);
		_static_mesh_collider_table.Remove(component);
		_static_mesh_colliders.destroy(collider);
	}

	void BulletPhysicsSystem::set_collider_transform(Handle<SphereColliderComponent> component, const Transform& transform)
	{
		_sphere_collider_table.Find(component, [&](auto* collider)
		{
			collider->setLocalScaling(convert_to_bullet(transform.scale));
			auto* entityData = static_cast<EntityPhysicsData*>(collider->getUserPointer());
			entityData->collider.update_child_location_rotation(*collider, transform.location, transform.rotation);
		});
	}

	void BulletPhysicsSystem::set_collider_transform(Handle<CapsuleColliderComponent> component, const Transform& transform)
	{
		_capsule_collider_table.Find(component, [&](auto* collider)
		{
			collider->setLocalScaling(convert_to_bullet(transform.scale));
			auto* entityData = static_cast<EntityPhysicsData*>(collider->getUserPointer());
			entityData->collider.update_child_location_rotation(*collider, transform.location, transform.rotation);
		});
	}

	void BulletPhysicsSystem::set_collider_transform(Handle<StaticMeshColliderComponent> /*component*/, const Transform& /*transform*/)
	{
		// TODO
	}

	void BulletPhysicsSystem::set_collider_shape(Handle<SphereColliderComponent> component, SphereColliderComponent::Shape shape)
	{
		// Get the collider
		auto* collider = _sphere_collider_table[component];
		auto localScaling = collider->getLocalScaling();

		// Get the entity
		auto* entityData = static_cast<EntityPhysicsData*>(collider->getUserPointer());

		// Destroy the old sphere
		collider->~btSphereShape();

		// Rebuild it
		new (collider) btSphereShape(shape.radius);
		collider->setLocalScaling(localScaling);
		collider->setUserPointer(entityData);

		// Update entity
		entityData->update_inertia();
	}

	void BulletPhysicsSystem::set_collider_shape(Handle<CapsuleColliderComponent> component, CapsuleColliderComponent::Shape shape)
	{
		// Get the collider
		auto* collider = _capsule_collider_table[component];
		auto localScaling = collider->getLocalScaling();

		// Get the entity
		auto* entityData = static_cast<EntityPhysicsData*>(collider->getUserPointer());

		// Destroy the old collider
		collider->~btCapsuleShape();

		// Rebuild it
		switch (shape.axis)
		{
		case ColliderComponent::ShapeAxis::X:
			new (collider) btCapsuleShapeX{ shape.radius, shape.height };
			break;
		case ColliderComponent::ShapeAxis::Y:
			new (collider) btCapsuleShape{ shape.radius, shape.height };
			break;
		case ColliderComponent::ShapeAxis::Z:
			new (collider) btCapsuleShapeZ{ shape.radius, shape.height };
			break;
		}
		collider->setLocalScaling(localScaling);
		collider->setUserPointer(entityData);

		// Update entity
		entityData->update_inertia();
	}

	void BulletPhysicsSystem::set_collider_shape(Handle<StaticMeshColliderComponent> /*component*/, StaticMeshColliderComponent::Shape /*shape*/)
	{
		// TODO
	}

	void BulletPhysicsSystem::create_character_controller(
		Handle<CharacterControllerComponent> component, 
		Handle<Entity> entity,
		Handle<PrimitiveColliderComponent> collider, 
		CharacterControllerComponent::Settings settings)
	{
		auto* entityData = _entity_data_table[entity];

		// Find collider
		btConvexShape* bCollider = nullptr;
		_capsule_collider_table.Find(collider.cast_to<CapsuleColliderComponent>(), bCollider);
		_sphere_collider_table.Find(collider.cast_to<SphereColliderComponent>(), bCollider);

		// Create the controller
		auto* controller = _character_controllers.emplace_new(*entityData, *bCollider, settings);
		_character_controller_table[component] = controller;

		// Add it to the world
		_physics_world->GetDynamicsWorld().addAction(controller);
	}

	void BulletPhysicsSystem::destroy_character_controller(Handle<CharacterControllerComponent> component)
	{
		// Get the controller
		auto* controller = _character_controller_table[component];

		// Remove it from the world
		_physics_world->GetDynamicsWorld().removeAction(controller);

		// Destroy it
		_character_controller_table.Remove(component);
		_character_controllers.destroy(controller);
	}

	void BulletPhysicsSystem::set_character_controller_collider(Handle<CharacterControllerComponent> component, Handle<PrimitiveColliderComponent> collider)
	{
		auto* controller = _character_controller_table[component];
		btConvexShape* bCollider = nullptr;
		_capsule_collider_table.Find(collider.cast_to<CapsuleColliderComponent>(), bCollider);
		_sphere_collider_table.Find(collider.cast_to<SphereColliderComponent>(), bCollider);
		controller->set_collider(*bCollider);
	}

	void BulletPhysicsSystem::character_controller_jump(Handle<CharacterControllerComponent> component)
	{
		auto* controller = _character_controller_table[component];
		controller->jump();
	}

	void BulletPhysicsSystem::character_controller_on_ground(Handle<CharacterControllerComponent> component, bool& out)
	{
		auto* controller = _character_controller_table[component];
		out = controller->onGround();
	}

	void BulletPhysicsSystem::character_controller_walk(Handle<CharacterControllerComponent> component, const Vec2& direction)
	{
		auto* controller = _character_controller_table[component];
		controller->setWalkDirection(btVector3{ direction.X, 0, direction.Y });
	}
}
