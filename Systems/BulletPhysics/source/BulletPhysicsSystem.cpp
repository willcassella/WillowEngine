// BulletPhysicsSystem.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <Engine/World.h>
#include "../include/BulletPhysics/BulletPhysicsSystem.h"
#include "../private/DebugDrawer.h"
#include "../private/PhysicsWorld.h"
#include "../private/RigidBody.h"
#include "../private/CharacterController.h"
#include "../private/BulletTriangleMesh.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::BulletPhysicsSystem);

namespace Willow
{
	////////////////////////
	///   Constructors   ///

	BulletPhysicsSystem::BulletPhysicsSystem()
	{
		_physicsWorld = std::make_unique<PhysicsWorld>();
	}

	BulletPhysicsSystem::~BulletPhysicsSystem()
	{
		// _physicsWorld must be destroyed first
		_physicsWorld.release();
	}

	///////////////////
	///   Methods   ///

	void BulletPhysicsSystem::Update(const World& world)
	{
		_physicsWorld->GetDynamicsWorld().stepSimulation(world.TimeStep, 1);
	}

	void BulletPhysicsSystem::DebugDraw(RenderSystem& render)
	{
		DebugDrawer drawer{ render };
		_physicsWorld->GetDynamicsWorld().setDebugDrawer(&drawer);
		_physicsWorld->GetDynamicsWorld().debugDrawWorld();
		_physicsWorld->GetDynamicsWorld().setDebugDrawer(nullptr);
	}

	void BulletPhysicsSystem::CreateEntity(
		EntityHandle entity, 
		EntityHandle parent, 
		Transform& transform, 
		Entity::PhysicsMode mode, 
		Entity::PhysicsState state)
	{
		// Create the physics data for this Entity
		auto* data = _entityPhysicsData.New(state, mode, parent, transform);
		_entityDataTable[entity] = data;

		// If the entity is at least a ghost
		if (mode >= Entity::PhysicsMode::Ghost)
		{
			data->GhostBody = _ghostBodies.New(*data);
			_physicsWorld->GetDynamicsWorld().addCollisionObject(data->GhostBody);
		}

		// If the entity is at least kinematic
		if (mode >= Entity::PhysicsMode::Kinematic)
		{
			data->RigidBody = _rigidBodies.New(*data);
			_physicsWorld->GetDynamicsWorld().addRigidBody(data->RigidBody);

			// If the entity IS kinematic
			if (mode == Entity::PhysicsMode::Kinematic)
			{
				data->RigidBody->setMassProps(0, { 0, 0, 0 });
				data->RigidBody->setActivationState(DISABLE_DEACTIVATION);
				data->RigidBody->setCollisionFlags(data->RigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
			}
		}
	}

	void BulletPhysicsSystem::DestroyEntity(EntityHandle /*entity*/)
	{
		// TODO
	}

	void BulletPhysicsSystem::SetEntityParent(EntityHandle /*entity*/, EntityHandle /*parent*/)
	{
		// TODO
	}

	void BulletPhysicsSystem::UpdateEntityTransform(EntityHandle entity)
	{
		_entityDataTable.Find(entity, [&](EntityPhysicsData* data)
		{
			data->Collider.setLocalScaling(ConvertToBullet(data->Transform->Scale));
			btTransform transform{ ConvertToBullet(data->Transform->Rotation), ConvertToBullet(data->Transform->Location) };

			// If we have a GhostBody
			if (data->GhostBody)
			{
				data->GhostBody->setWorldTransform(transform);
			}

			// If we have a RigidBody
			if (data->RigidBody)
			{
				data->RigidBody->setWorldTransform(transform);
			}
		});
	}

	void BulletPhysicsSystem::SetEntityPhysicsMode(EntityHandle entity, Entity::PhysicsMode mode)
	{
		_entityDataTable.Find(entity, [=](EntityPhysicsData* data)
		{
			// Set the new mode
			data->Mode = mode;

			// If we have a RigidBody
			if (data->RigidBody)
			{
				// If we don't want to have one
				if (mode < Entity::PhysicsMode::Kinematic)
				{
					// If we don't have any constraints
					if (data->RigidBody->getNumConstraintRefs() == 0)
					{
						// Destroy it
						_physicsWorld->GetDynamicsWorld().removeRigidBody(data->RigidBody);
						data->RigidBody->Disable(*data);
						_rigidBodies.Destroy(data->RigidBody);
						data->RigidBody = nullptr;
					}
					else
					{
						// Set it up purely for constraints
						data->RigidBody->setCollisionShape(nullptr);
						data->RigidBody->setCollisionFlags(
							data->RigidBody->getCollisionFlags() |
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
					data->RigidBody = _rigidBodies.New(*data);
					_physicsWorld->GetDynamicsWorld().addRigidBody(data->RigidBody);
					
					if (mode == Entity::PhysicsMode::Kinematic)
					{
						data->RigidBody->setMassProps(0, { 0, 0, 0 });
						data->RigidBody->setActivationState(DISABLE_DEACTIVATION);
						data->RigidBody->setCollisionFlags(data->RigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
					}
				}
			}

			// If we have a Ghost body
			if (data->GhostBody)
			{
				// If we don't want to have a ghost body
				if (mode == Entity::PhysicsMode::Transient)
				{
					// Destroy it
					_physicsWorld->GetDynamicsWorld().removeCollisionObject(data->GhostBody);
					_ghostBodies.Destroy(data->GhostBody);
					data->GhostBody = nullptr;
				}
			}
			else
			{
				// If we want to have a GhostBody
				if (mode >= Entity::PhysicsMode::Ghost)
				{
					auto* ghost = _ghostBodies.New(*data);
					_physicsWorld->GetDynamicsWorld().addCollisionObject(ghost);
				}
			}
		});
	}

	void BulletPhysicsSystem::SetEntityPhysicsState(EntityHandle entity, Entity::PhysicsState state)
	{
		// If the PhysicsObject exists
		_entityDataTable.Find(entity, [&](EntityPhysicsData* data)
		{
			data->State = state;

			// If it's a Kinematic or Rigid body
			if (data->Mode >= Entity::PhysicsMode::Kinematic)
			{
				data->RigidBody->setAngularFactor(ConvertToBullet(state.AngularMotionFactor));
				data->RigidBody->setLinearFactor(ConvertToBullet(state.LinearMotionFactor));
				data->RigidBody->setFriction(state.Friction);
				data->RigidBody->setRollingFriction(state.RollingFriction);

				// If it's a rigid body
				if (data->Mode == Entity::PhysicsMode::Dynamic)
				{
					btVector3 inertia;
					data->Collider.calculateLocalInertia(state.Mass, inertia);
					data->RigidBody->setMassProps(state.Mass, inertia);
				}
			}
		});
	}

	void BulletPhysicsSystem::GetEntityLinearVelocity(Vec3& outLinearVelocity, EntityHandle entity)
	{
		auto* entityData = _entityDataTable[entity];

		if (entityData->RigidBody)
		{
			outLinearVelocity = ConvertFromBullet(entityData->RigidBody->getLinearVelocity());
		}
	}

	void BulletPhysicsSystem::SetEntityLinearVelocity(EntityHandle entity, const Vec3& linearVelocity)
	{
		auto* entityData = _entityDataTable[entity];

		if (entityData->RigidBody)
		{
			entityData->RigidBody->setLinearVelocity(ConvertToBullet(linearVelocity));
		}
	}

	void BulletPhysicsSystem::GetEntityAngularVelocity(Vec3& outAngularVelocity, EntityHandle entity)
	{
		auto* entityData = _entityDataTable[entity];

		if (entityData->RigidBody)
		{
			outAngularVelocity = ConvertFromBullet(entityData->RigidBody->getAngularVelocity());
		}
	}

	void BulletPhysicsSystem::SetEntityAngularVelocity(EntityHandle entity, const Vec3& angularVelocity)
	{
		auto* entityData = _entityDataTable[entity];

		if (entityData->RigidBody)
		{
			entityData->RigidBody->setAngularVelocity(ConvertToBullet(angularVelocity));
		}
	}

	void BulletPhysicsSystem::ApplyForce(EntityHandle entity, const Vec3& force, const Vec3& offset)
	{
		_entityDataTable.Find(entity, [&](EntityPhysicsData* data)
		{
			if (data->RigidBody)
			{
				data->RigidBody->applyForce(ConvertToBullet(force), ConvertToBullet(offset));
			}
		});
	}

	void BulletPhysicsSystem::ApplyImpulse(EntityHandle entity, const Vec3& force, const Vec3& offset)
	{
		_entityDataTable.Find(entity, [&](EntityPhysicsData* data)
		{
			if (data->RigidBody)
			{
				data->RigidBody->applyImpulse(ConvertToBullet(force), ConvertToBullet(offset));
			}
		});
	}

	void BulletPhysicsSystem::ApplyTorque(EntityHandle entity, const Vec3& torque)
	{
		_entityDataTable.Find(entity, [&](EntityPhysicsData* data)
		{
			if (data->RigidBody)
			{
				data->RigidBody->applyTorque(ConvertToBullet(torque));
			}
		});
	}

	void BulletPhysicsSystem::ApplyTorqueImpulse(EntityHandle entity, const Vec3& torque)
	{
		_entityDataTable.Find(entity, [&](EntityPhysicsData* data)
		{
			if (data->RigidBody)
			{
				data->RigidBody->applyTorqueImpulse(ConvertToBullet(torque));
			}
		});
	}

	void BulletPhysicsSystem::CreateCollider(GHandle<SphereColliderComponent> component, EntityHandle entity, const Transform& transform, SphereColliderComponent::Shape shape)
	{
		auto* entityData = _entityDataTable[entity];

		// Create the sphere collider
		auto* collider = _sphereColliders.New(shape.Radius);
		collider->setLocalScaling(ConvertToBullet(transform.Scale));
		collider->setUserPointer(entityData);
		
		// Add it to the EntityCollider
		entityData->Collider.AddChild(*collider, transform.Location, transform.Rotation);
		UpdateInertia(*entityData);

		// Add it to the table
		_sphereColliderTable[component] = collider;
	}

	void BulletPhysicsSystem::CreateCollider(GHandle<CapsuleColliderComponent> component, EntityHandle entity, const Transform& transform, CapsuleColliderComponent::Shape shape)
	{
		auto* entityData = _entityDataTable[entity];

		// Create the capsule collider
		btCapsuleShape* collider = nullptr;
		switch (shape.Axis)
		{
		case ColliderComponent::ShapeAxis::X:
			collider = _capsuleColliders.New<btCapsuleShapeX>(shape.Radius, shape.Height);
			break;
		case ColliderComponent::ShapeAxis::Y:
			collider = _capsuleColliders.New<btCapsuleShape>(shape.Radius, shape.Height);
			break;
		case ColliderComponent::ShapeAxis::Z:
			collider = _capsuleColliders.New<btCapsuleShapeZ>(shape.Radius, shape.Height);
			break;
		}
		collider->setLocalScaling(ConvertToBullet(transform.Scale));
		collider->setUserPointer(entityData);

		// Add it to the entity collider
		entityData->Collider.AddChild(*collider, transform.Location, transform.Rotation);
		UpdateInertia(*entityData);

		// Add it to the table
		_capsuleColliderTable[component] = collider;
	}

	void BulletPhysicsSystem::CreateCollider(GHandle<StaticMeshColliderComponent> component, EntityHandle entity, const Transform& transform, StaticMeshColliderComponent::Shape shape)
	{
		auto* entityData = _entityDataTable[entity];

		// Find or create a mesh for this collider
		auto& mesh = _triangleMeshes[shape.Mesh];
		if (!mesh)
		{
			mesh = std::make_unique<BulletTriangleMesh>(shape.Mesh);
		}

		// Create the collider
		auto* collider = _staticMeshColliders.New(mesh.get(), true);
		collider->setLocalScaling(ConvertToBullet(transform.Scale));
		collider->setUserPointer(entityData);

		// Add it to the entity collider
		entityData->Collider.AddChild(*collider, transform.Location, transform.Rotation);
		UpdateInertia(*entityData);

		// Add it to the table
		_staticMeshColliderTable[component] = collider;
	}

	void BulletPhysicsSystem::DestroyCollider(GHandle<SphereColliderComponent> component)
	{
		// Get the collider and its compound
		auto* collider = _sphereColliderTable[component];
		auto* entityData = static_cast<EntityPhysicsData*>(collider->getUserPointer());
		
		// Destroy it
		entityData->Collider.RemoveChild(*collider);
		_sphereColliders.Destroy(collider);
		_sphereColliderTable.Remove(component);
	}

	void BulletPhysicsSystem::DestroyCollider(GHandle<CapsuleColliderComponent> component)
	{
		// Get the collider and its compound
		auto* collider = _capsuleColliderTable[component];
		auto* entityData = static_cast<EntityPhysicsData*>(collider->getUserPointer());

		// Destroy it
		entityData->Collider.RemoveChild(*collider);
		_capsuleColliderTable.Remove(component);
		_capsuleColliders.Destroy(collider);
	}

	void BulletPhysicsSystem::DestroyCollider(GHandle<StaticMeshColliderComponent> /*component*/)
	{
		// TODO
	}

	void BulletPhysicsSystem::SetColliderTransform(GHandle<SphereColliderComponent> component, const Transform& transform)
	{
		_sphereColliderTable.Find(component, [&](auto* collider)
		{
			collider->setLocalScaling(ConvertToBullet(transform.Scale));
			auto* entityData = static_cast<EntityPhysicsData*>(collider->getUserPointer());
			entityData->Collider.UpdateChildLocationRotation(*collider, transform.Location, transform.Rotation);
		});
	}

	void BulletPhysicsSystem::SetColliderTransform(GHandle<CapsuleColliderComponent> component, const Transform& transform)
	{
		_capsuleColliderTable.Find(component, [&](auto* collider)
		{
			collider->setLocalScaling(ConvertToBullet(transform.Scale));
			auto* entityData = static_cast<EntityPhysicsData*>(collider->getUserPointer());
			entityData->Collider.UpdateChildLocationRotation(*collider, transform.Location, transform.Rotation);
		});
	}

	void BulletPhysicsSystem::SetColliderTransform(GHandle<StaticMeshColliderComponent> /*component*/, const Transform& /*transform*/)
	{
		// TODO
	}

	void BulletPhysicsSystem::SetColliderShape(GHandle<SphereColliderComponent> /*component*/, SphereColliderComponent::Shape /*shape*/)
	{
		// TODO
	}

	void BulletPhysicsSystem::SetColliderShape(GHandle<CapsuleColliderComponent> /*component*/, CapsuleColliderComponent::Shape /*shape*/)
	{
		// TODO
	}

	void BulletPhysicsSystem::SetColliderShape(GHandle<StaticMeshColliderComponent> /*component*/, StaticMeshColliderComponent::Shape /*shape*/)
	{
		// TODO
	}

	void BulletPhysicsSystem::CreateCharacterController(
		GHandle<CharacterControllerComponent> component, 
		EntityHandle entity, 
		GHandle<PrimitiveColliderComponent> collider, 
		CharacterControllerComponent::Settings settings)
	{
		auto* entityData = _entityDataTable[entity];

		// Find collider
		btConvexShape* bCollider = nullptr;
		_capsuleColliderTable.Find(collider.CastTo<CapsuleColliderComponent>(), bCollider);
		_sphereColliderTable.Find(collider.CastTo<SphereColliderComponent>(), bCollider);

		// Create the controller
		auto* controller = _characterControllers.New(*entityData, *bCollider, settings);
		_characterControllerTable[component] = controller;

		// Add it to the world
		_physicsWorld->GetDynamicsWorld().addAction(controller);
	}

	void BulletPhysicsSystem::CharacterControllerJump(GHandle<CharacterControllerComponent> component)
	{
		auto* controller = _characterControllerTable[component];
		controller->jump();
	}

	void BulletPhysicsSystem::CharacterControllerOnGround(GHandle<CharacterControllerComponent> component, bool& out)
	{
		auto* controller = _characterControllerTable[component];
		out = controller->onGround();
	}

	void BulletPhysicsSystem::CharacterControllerWalk(GHandle<CharacterControllerComponent> component, const Vec2& direction)
	{
		auto* controller = _characterControllerTable[component];
		controller->setWalkDirection(btVector3{ direction.X, 0, direction.Y });
	}
}
