// Component.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Forwards/Engine.h"
#include "ITransformable.h"
#include "Transform.h"

class ENGINE_API Component : public Object, 
	public ITransformable
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(Object)
	friend GameObject;
	friend World;

	///////////////////////
	///   Inner Types   ///
public:

	/** The type of ID for components. */
	using ID = uint64;

	/** Different management states a Component may exist in. */
	enum class Status : byte
	{
		/* This Component has not yet been initialized, and should not be used in the Scene. */
		Uninitialized,

		/* This Component is currently undergoing its Initialization procedure. */
		Initializing,
		
		/* This Component is currently Initialized in the Scene. */
		Initialized
	};

	////////////////////////
	///   Constructors   ///
public:

	Component();
	~Component() override;

	///////////////////
	///   Methods   ///
public:

	/** Returns the ID of this Component. */
	FORCEINLINE ID GetID() const
	{
		return _id;
	}

	/** Returns the management status of this Component. */
	FORCEINLINE Status GetStatus() const
	{
		return _status;
	}

	/** Returns whether this Component is an orphan (has no owning GameObject). */
	FORCEINLINE bool IsOrphan() const
	{
		return _owner == nullptr;
	}

	/** Returns a pointer to the GameObject that owns this Component.
	* NOTE: Returns 'null' if this Component is orphaned. */
	FORCEINLINE GameObject* GetOwner()
	{
		return _owner;
	}

	/** Returns a pointer to the GameObject that owns this Component.
	* NOTE: Returns 'null' if this Component is orphaned. */
	FORCEINLINE const GameObject* GetOwner() const
	{
		return _owner;
	}

	/** Returns a reference to the World that this Component is a part of. */
	FORCEINLINE World& GetWorld()
	{
		return *_world;
	}

	/** Returns a reference to the World that this Component is a part of. */
	FORCEINLINE const World& GetWorld() const
	{
		return *_world;
	}

	/** Returns the parent of this Component.
	* NOTE: If 'null' is returned, then this Component has no parent. */
	FORCEINLINE Component* GetParent()
	{
		return _parent;
	}

	/** Returns the parent of this Component.
	* NOTE: If 'null' is returned, then this Component has no parent. */
	FORCEINLINE const Component* GetParent() const
	{
		return _parent;
	}

	/** Returns whether this Component is parented to the given Component (directly or indirectly). */
	bool IsParentedTo(const Component& component) const;

	/** Parents this Component to the given Component.
	* NOTE: You may pass 'null' if you wish for this Component to have no parent. */
	void SetParent(Component* parent);

	/** Returns an Array of all Components parented to this Component. */
	FORCEINLINE const Array<Component*>& GetChildren()
	{
		return _children;
	}

	/** Returns an Array of all Components parented to this Component. */
	FORCEINLINE const Array<const Component*>& GetChildren() const
	{
		return static_cast<const Array<const Component*>&>(_children);
	}

	/** Returns the location of this Component relative to its parent. */
	FORCEINLINE const Vec3& GetLocation() const
	{
		return _transform.GetLocation();
	}
	
	/** Returns the location of this Component in world space. */
	FORCEINLINE Vec3 GetWorldLocation() const
	{
		if (_parent)
		{
			return _parent->GetTransformationMatrix() * _transform.GetLocation();
		}
		else
		{
			return _transform.GetLocation();
		}
	}

	/** Sets the location of this Component in parent space. */
	FORCEINLINE void SetLocation(const Vec3& location) final override
	{
		_transform.SetLocation(location);
	}

	/** Sets the location of this Component in world space. */
	FORCEINLINE void SetWorldLocation(const Vec3& /*location*/) final override
	{
		// TODO
	}

	/** Translates this Component along the given vector in local space. */
	FORCEINLINE void Translate(const Vec3& vec) final override
	{
		auto translateVec = _transform.GetLocation() + Mat4::Rotate(_transform.GetRotation()) * vec;
		_transform.SetLocation(translateVec);
	}

	/** Translates this Component along the given vector in world space. */
	FORCEINLINE void TranslateGlobal(const Vec3& vec) final override
	{
		_transform.SetLocation(_transform.GetLocation() + vec);
	}

	/** Returns the rotation of this Component relative to its parent. */
	FORCEINLINE const Quat& GetRotation() const
	{
		return _transform.GetRotation();
	}

	/** Returns the rotation of this Component in world space. */
	FORCEINLINE Quat GetWorldRotation() const
	{
		if (_parent)
		{
			return _parent->GetWorldRotation() * _transform.GetRotation();
		}
		else
		{
			return _transform.GetRotation();
		}
	}

	/** Sets the rotation of this Component relative to the parent. */
	FORCEINLINE void SetRotation(const Quat& rotation) final override
	{
		_transform.SetRotation(rotation);
	}

	/** Sets the rotation of this Component in world space. */
	FORCEINLINE void SetWorldRotation(const Quat& /*rotation*/) final override
	{
		// TODO
	}

	/** Rotates this Component along the given axis by the given angle in local space. */
	FORCEINLINE void Rotate(const Vec3& axis, Angle angle) final override
	{
		Quat rotation = _transform.GetRotation();
		rotation.RotateByAxisAngle(axis, angle, true);
		_transform.SetRotation(rotation);
	}

	/** Rotates this Component along the given axis by the given angle in global space. */
	FORCEINLINE void RotateGlobal(const Vec3& axis, Angle angle) final override
	{
		Quat rotation = _transform.GetRotation();
		rotation.RotateByAxisAngle(axis, angle, false);
		_transform.SetRotation(rotation);
	}

	/** Returns the scale of this Component, relative to the parent. */
	FORCEINLINE const Vec3& GetScale() const
	{
		return _transform.GetScale();
	}

	/** Sets the scale of this Component. */
	FORCEINLINE void SetScale(const Vec3& scale) final override
	{
		_transform.SetScale(scale);
	}

	/** Scales this Component by the given amount. */
	FORCEINLINE void Scale(const Vec3& scale) final override
	{
		Vec3 newScale = _transform.GetScale() * scale;
		_transform.SetScale(newScale);
	}

	/** Returns the transformation matrix of this Component. */
	Mat4 GetTransformationMatrix() const;

protected:

	/** Method called when this Component is spawned into the World. */
	virtual void OnInitialize();

private:

	void Initialize(World& world);

	////////////////
	///   Data   ///
private:

	GameObject* _owner;
	World* _world;
	ID _id;
	Status _status;

	Transform _transform;
	Component* _parent;
	Array<Component*> _children;
};

REFLECTABLE_ENUM(Component::Status);
