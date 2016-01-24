// GameObject.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Math/Vec3.h>
#include <Core/Math/Quat.h>
#include <Core/Math/Mat4.h>
#include "config.h"

/** Behavior for handling the transform of a GameObject upon setting the parent.
* Used by the 'SetParent' member functions. */
enum SetParentOffsetMode
{
	/** When this GameObjects's parent is set, its location of moved to the Origin of the new parent (world center for 'null'). */
	SP_MoveToOrigin,

	/** The transform is set relative to the new parent as it was to the old parent. */
	SP_KeepLocalOffset,

	/** The transform is set in such a way that the object does not move at all (in world space) when the parent is set. */
	SP_KeepWorldOffset
};

/** Base for all "Objects" in the game (Entities, Components, Actors, etc). */
class ENGINE_API GameObject : public Object
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(Object)
	friend class World;

	///////////////////////
	///   Inner Types   ///
public:

	/** Unique identifier for GameObjects. */
	using ID = uint64;

	/** The possible states for a GameObject to exist in, in order. */
	enum class State : byte
	{
		/** This GameObject has just been constructed, and has not been initialized yet. */
		Uninitialized,

		/** This GameObject has been initialized, but has not been spawned yet. */
		Initialized,

		/** This GameObject is in the process of spawning. */
		Spawning,

		/** This GameObject has been successfully spawned. */
		Spawned,

		/** This GameObject has been destroyed. */
		Destroyed
	};

	///////////////////
	///   Methods   ///
public:

	/** Returns the ID of this GameObject. */
	FORCEINLINE ID GetID() const
	{
		return _id;
	}

	/** Returns the state of this GameObject. */
	FORCEINLINE State GetState() const
	{
		return _state;
	}

	/** Returns whether this GameObject has completed its spawning procedure. */
	FORCEINLINE bool HasSpawned() const
	{
		return this->GetState() >= State::Spawned;
	}

	/** Returns whether this GameObject has been destroyed. */
	FORCEINLINE bool IsDestroyed() const
	{
		return this->GetState() >= State::Destroyed;
	}

	/** Returns a reference to the World that this GameObject belongs to. */
	virtual World& GetWorld() = 0;

	/** Returns a reference to the World that this GameObject belongs to. */
	virtual const World& GetWorld() const = 0;

	/** Returns whether this GameObject has a parent. */
	FORCEINLINE bool HasParent() const
	{
		return this->GetParent() != nullptr;
	}

	/** Returns the parent of this GameObject. 
	* NOTE: Returns 'null' if this GameObject has no parent. */
	virtual GameObject* GetParent() = 0;

	/** Returns the parent of this GameObject.
	* NOTE: Returns 'null' if this GameObject has no parent. */
	virtual const GameObject* GetParent() const = 0;

	/** Returns the location of this GameObject in local space. */
	virtual Vec3 GetLocation() const = 0;

	/** Returns the location of this GameOject in world space. */
	virtual Vec3 GetWorldLocation() const = 0;

	/** Sets the location of this GameObject in local space. */
	virtual void SetLocation(const Vec3& location) = 0;

	/** Sets the location of this GameObject in world space. */
	virtual void SetWorldLocation(const Vec3& lcoation) = 0;

	/** Translates this GameObject along the given vector in local space. */
	virtual void Translate(const Vec3& vec) = 0;

	/** Translates this GameObject along the given vector in world space. */
	virtual void TranslateGlobal(const Vec3& vec) = 0;

	/** Returns the rotation of this GameObject in local space. */
	virtual Quat GetRotation() const = 0;

	/** Returns the location of this GameObject in world space. */
	virtual Quat GetWorldRotation() const = 0;

	/** Sets the rotation of this GameObject in local space. */
	virtual void SetRotation(const Quat& rotation) = 0;

	/** Sets the rotation of this GameObject in world space. */
	virtual void SetWorldRotation(const Quat& rotation) = 0;

	/** Rotates this GameObject along the given axis by the given angle, in local space. */
	virtual void Rotate(const Vec3& axis, Angle angle) = 0;

	/** Rotates this GameObject along the given axis by the given angle, in world space. */
	virtual void RotateGlobal(const Vec3& axis, Angle angle) = 0;

	/** Returns the scale of this GameObject. */
	virtual Vec3 GetScale() const = 0;

	/** Sets the scale of this GameObject. */
	virtual void SetScale(const Vec3& scale) = 0;

	/** Scales this GameObject by the given vector. */
	virtual void Scale(const Vec3& vec) = 0;

	/** Returns a matrix of the world transformation for this GameObject. */
	virtual Mat4 GetTransformationMatrix() const = 0;

	/** Performs spawning procedure. */
	void Spawn();

	/** Destroys this GameObject. TODO: Add delay */
	void Destroy();

protected:

	/** Handles spawning procedure. */
	virtual void OnSpawn();

	/** Handles destruction procedure. */
	virtual void OnDestroy();

private:

	/** Performs initialization procedure. */
	void Initialize(ID id);

	////////////////
	///   Data   ///
private:

	ID _id = 0;
	State _state = State::Uninitialized;
};

REFLECTABLE_ENUM(GameObject::State)
