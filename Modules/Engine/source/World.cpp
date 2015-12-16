// World.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <memory>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
#include "../include/Engine/World.h"
#include "../include/Engine/GameObjects/Prop.h"
#include "../include/Engine/ServiceInterfaces/IRenderer.h"

/////////////////
///   Types   ///

Ptr<Prop> testObject;

class MyMotionState : public btMotionState
{
	////////////////////////
	///   Constructors   ///
public:

	MyMotionState(const btTransform& transform = btTransform())
		: Transform(transform)
	{
		// All done
	}

	//////////////////
	///   Fields   ///
public:

	btTransform Transform;

	///////////////////
	///   Methods   ///
public:

	void getWorldTransform(btTransform& worldTransform) const override
	{
		worldTransform = Transform;
	}

	void setWorldTransform(const btTransform& worldTransform) override
	{
		Transform = worldTransform;
	}
};

/** Internal structure holding bullet physics data. */
struct PhysicsData final
{
	////////////////////////
	///   Constructors   ///
public:

	PhysicsData()
	{
		// Initialize physics configuration
		BroadPhaseInterface = std::make_unique<btDbvtBroadphase>();
		CollisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
		Dispatcher = std::make_unique<btCollisionDispatcher>(CollisionConfiguration.get());
		btGImpactCollisionAlgorithm::registerAlgorithm(Dispatcher.get());

		// Initialize the physics world
		DynamicsWorld = std::make_unique<btDiscreteDynamicsWorld>(Dispatcher.get(), BroadPhaseInterface.get(), ConstraintSolver.get(), CollisionConfiguration.get());
		DynamicsWorld->setGravity(btVector3(0, -10, 0));

		// Create collision shapes
		GroundShape = std::make_unique<btStaticPlaneShape>(btVector3(0, 1, 0).normalize(), 1.f);
		GunShape = std::make_unique<btCylinderShape>(btVector3(3, 1, 0.4f));

		// Create the ground rigid body
		GroundMotionState = std::make_unique<btDefaultMotionState>(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1.75f, 0)));
		btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, GroundMotionState.get(), GroundShape.get(), btVector3(0, 0, 0));
		GroundRigidBody = std::make_unique<btRigidBody>(groundRigidBodyCI);

		// Add the ground to the world
		DynamicsWorld->addRigidBody(GroundRigidBody.get());

		// Calcuate gun local intertia
		btScalar mass = 1;
		btVector3 localInertia;
		GunShape->calculateLocalInertia(mass, localInertia);

		// Create gun rigid body
		GunMotionState = std::make_unique<MyMotionState>(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 5, 0)));
		btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(mass, GunMotionState.get(), GunShape.get(), localInertia);
		GunRigidBody = std::make_unique<btRigidBody>(sphereRigidBodyCI);

		// Add the gun to the world
		DynamicsWorld->addRigidBody(GunRigidBody.get());
	}

	~PhysicsData()
	{
		DynamicsWorld->removeRigidBody(GroundRigidBody.get());
		DynamicsWorld->removeRigidBody(GunRigidBody.get());
	}

	//////////////////
	///   Fields   ///
public:

	// Physics configuration
	std::unique_ptr<btBroadphaseInterface> BroadPhaseInterface;
	std::unique_ptr<btCollisionConfiguration> CollisionConfiguration;
	std::unique_ptr<btCollisionDispatcher> Dispatcher;
	std::unique_ptr<btConstraintSolver> ConstraintSolver;
	
	// Physics world
	std::unique_ptr<btDynamicsWorld> DynamicsWorld;
	
	// Shapes
	std::unique_ptr<btCollisionShape> GroundShape;
	std::unique_ptr<btCollisionShape> GunShape;

	// Motion States
	std::unique_ptr<btMotionState> GroundMotionState;
	std::unique_ptr<btMotionState> GunMotionState;

	// Rigid bodies
	std::unique_ptr<btRigidBody> GroundRigidBody;
	std::unique_ptr<btRigidBody> GunRigidBody;
};

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(World)
.Data("GameObject", &World::_gameObjects)
.Data("Components", &World::_components)
.Field("TimeDilation", &World::TimeDilation, "The time dilation of the world. Default is 1.")
.Field("TimeStep", &World::TimeStep, "The amount of time (ms) that each update of the world represents.");

////////////////////////
///   Constructors   ///

World::World()
{
	_nextGameObjectID = 1;
	_nextComponentID = 1;
	testObject = &Spawn<Prop>();
	testObject->GetComponent(testObject->MeshComponent)->Material = "Content/Materials/Sponza.mat"_p;
	testObject->GetComponent(testObject->MeshComponent)->Mesh = "Content/Models/battle_rifle.dat";
	testObject->GetComponent(testObject->MeshComponent)->InstanceParams["diffuse"] = AssetPtr<Texture>("Content/Textures/battle_rifle_tex.png");
	_physicsData = std::make_unique<PhysicsData>();
}

World::~World()
{
	// Do nothing (PhysicsData is only defined in this file, so we must define a destructor here to prevent errors when other files attempt
	// to call the implicitly defined destructor. This is why we can't have nice things).
}

///////////////////
///   Methods   ///

void World::Update()
{
	Events.DispatchEvent("Update", 1.f);
	Events.Flush();

	// Remove stale objects
	while (!_destroyedObjects.IsEmpty())
	{
		auto object = _destroyedObjects.Pop();
		_gameObjects.Remove(object->GetID());
	}

	// Spawn new objects
	while (!_unspawnedObjects.IsEmpty())
	{
		auto object = _unspawnedObjects.Pop();
		object->OnSpawn();
	}

	// Simulate physics
	_physicsData->DynamicsWorld->stepSimulation(TimeStep, 10);

	// Get the position of the sphere1
	btTransform trans;
	_physicsData->GunRigidBody->getMotionState()->getWorldTransform(trans);

	// Move the test object
	testObject->GetRootComponent()->SetLocation({ trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ() });


	//t->Orientation.X = -trans.getRotation().getX();
	//t->Orientation.Y = -trans.getRotation().getY();
	//t->Orientation.Z = -trans.getRotation().getZ();
	//t->Orientation.W = -trans.getRotation().getW();

	//_physicsData->GunRigidBody->setMotionState(_physicsData->GunMotionState.get());
}

void World::Destroy(GameObject& object)
{
	_destroyedObjects.Push(&object);
	object._isDestroyed = true;
	object.OnDestroy();
}

void World::Destroy(GHandle<GameObject> handle)
{
	_gameObjects.Find(handle.GetID(), [this](auto& object) { this->Destroy(*object); });
}


Component& World::SpawnComponent(UniquePtr<Component> component)
{
	auto& ref = *component;
	component->_id = _nextComponentID++;
	component->_world = this;
	_components[component->_id] = component.Transfer();

	ref.Initialize(self);

	return ref;
}

GameObject& World::SpawnGameObject(UniquePtr<GameObject> gameObject)
{
	auto& ref = *gameObject;
	gameObject->_id = _nextGameObjectID++;
	gameObject->_world = this;
	_gameObjects[gameObject->_id] = gameObject.Transfer();
	_unspawnedObjects.Push(&ref);

	ref.Build();

	return ref;
}