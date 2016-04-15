// Forwards.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

////////////////////
///   Forwards   ///

/** Defined in a Bullet header. */
class btSphereShape;

/** Defined in a Bullet header. */
class btCapsuleShape;

/** Defined in a Bullet header. */
class btBvhTriangleMeshShape;

namespace willow
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

	/** Defined in 'private/TriangleMesh.h' */
	struct TriangleMesh;
}
