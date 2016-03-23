// Physics.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

/////////////////
///   Types   ///

namespace Willow
{
	/** Defined in "source/Physics/PhysicsWorld.h" */
	class PhysicsWorld;

	/** Defined in "source/Physics/PhysicsBody.h" */
	class PhysicsBody;

	/** Defined in "source/Physics/EntityCollider.h" */
	class EntityCollider;

	/** Defined in "source/Physics/BulletTriangleMesh.h" */
	class BulletTriangleMesh;
}

/** Defined in one of the Bullet headers. */
class btCollisionShape;

/** Defined in one of the Bullet headers. */
class btCapsuleShape;

/** Defined in one of the Bullet headers. */
class btSphereShape;

/** Defined in one of the Bullet headers. */
class btBvhTriangleMeshShape;
