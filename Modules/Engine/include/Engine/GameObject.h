// GameObject.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Component.h"
#include "GHandle.h"

class ENGINE_API GameObject : public Object,
	public ITransformable
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(Object)
	friend World;

	///////////////////////
	///   Inner Types   ///
public:

	/** The type of ID for GameObjects. */
	using ID = uint64;

	////////////////////////
	///   Constructors   ///
public:

	GameObject();

	///////////////////
	///   Methods   ///
public:

	/** Returns the ID of this GameObject. */
	FORCEINLINE ID GetID() const
	{
		return _id;
	}

	/** Returns the name of this GameObject. */
	FORCEINLINE const String& GetName() const
	{
		return _name;
	}

	/** Returns a reference to the World that this GameObject is a part of. */
	FORCEINLINE World& GetWorld()
	{
		return *_world;
	}

	/** Returns a reference to the World that this GameObject is a part of. */
	FORCEINLINE const World& GetWorld() const
	{
		return *_world;
	}

	/** Returns whether this GameObject has spawned yet. */
	FORCEINLINE bool HasSpawned() const
	{
		return _hasSpawned;
	}

	/** Returns whether this GameObject will be destroyed at the end of the World update. */
	FORCEINLINE bool IsDestroyed() const
	{
		return _isDestroyed;
	}

	/** Returns the root Component of this GameObject. */
	FORCEINLINE Component* GetRootComponent()
	{
		return _rootComponent;
	}

	/** Returns the root Component of this GameObject. */
	FORCEINLINE const Component* GetRootComponent() const
	{
		return _rootComponent;
	}

	/** Sets the root Component of this GameObject. */
	FORCEINLINE void SetRootComponent(Component* rootComponent)
	{
		_rootComponent = rootComponent;
	}

	/** Returns a collection of all the Components attached to this GameObject. */
	FORCEINLINE Array<Component*> GetComponents()
	{
		return _components.GetValues();
	}

	/** Returns a collection of the Components attached to this GameObject. */
	FORCEINLINE Array<const Component*> GetComponents() const
	{
		return _components.GetValues();
	}

	/** Returns a collection of Components of the specified type attached to this GameObject. */
	template <class ComponentT>
	Array<Component*> GetComponentsOfType()
	{
		Array<ComponentT*> matches;

		for (auto& component : _components)
		{
			if (auto castedComponent = Cast<ComponentT>(*component.Second))
			{
				matches.Add(castedComponent);
			}
		}

		return matches;
	}

	/** Returns a collection of Components of the specified type attached to this GameObject. */
	template <class ComponentT>
	Array<const Component*> GetComponentsOfType() const
	{
		Array<const ComponentT*> matches;

		for (auto& component : _components)
		{
			if (auto castedComponent = Cast<ComponentT>(*component.Second))
			{
				matches.Add(castedComponent);
			}
		}

		return matches;
	}

	/** Returns a pointer to the Component of this GameObject with the given handle.
	* NOTE: Returns 'null' if the given handle does not refer to a component attached to this GameObject. */
	Component* GetComponent(GHandle<Component> handle);

	/** Returns a pointer to the Component of this GameObject with the given handle.
	* NOTE: Returns 'null' if the given handle does not refer to a component attached to this GameObject. */
	const Component* GetComponent(GHandle<Component> handle) const;

	/** Returns a pointer to the Component of this GameObject with the given handle.
	* NOTE: Returns 'null' if the given handle does not refer to a component attached to this GameObject. */
	template <class ComponentT>
	ComponentT* GetComponent(GHandle<ComponentT> handle)
	{
		GHandle<Component> h = handle;
		return static_cast<ComponentT*>(GetComponent(h));
	}

	/** Returns a pointer to the Component of this GameObject with the given handle.
	* NOTE: Returns 'null' if the given handle does not refer to a component attached to this GameObject. */
	template <class ComponentT>
	const ComponentT* GetComponent(GHandle<ComponentT> handle) const
	{
		GHandle<Component> h = handle;
		return static_cast<const ComponentT*>(this->GetComponent(h));
	}

	template <class BehaviorT>
	BehaviorT* GetBehavior();

	template <class BehaviorT>
	const BehaviorT* GetBehavior() const;

	/** Adds the given Component to this GameObject. 
	* NOTE: If the given Component is already a Component of this GameObject, this does nothing. */
	void AddComponent(Component& component);

	/** Adds the given Component to this GameObject.
	* NOTE: If the given Component is already a Component of this GameObject, this does nothing. */
	void AddComponent(GHandle<Component> handle);

	/** Spawns a new Component of the given type and adds it to this GameObject. 
	* Returns a reference to the created component. */
	template <class ComponentT>
	ComponentT& AddComponent();

	/** Adds the given Component to this GameObject, and parents it to this GameObject's root Component. 
	* NOTE: If this GameObject has no root Component, this will become it. */
	void Attach(Component& component);

	/** Adds the given Component to this GameObject, and parents it to this GameObject's root Component.
	* NOTE: If this GameObject has no root Component, this will become it. */
	void Attach(GHandle<Component> handle);

	/** Spawns a new instance of the given Component type, and parents it to this GameObject's root Component.
	* NOTE: If this GameObject has no root Component, this will become it. */
	template <class ComponentT>
	ComponentT& Attach();

	/** Spawns a new Behavior of the given type and adds it to this GameObject. */
	template <class BehaviorT>
	BehaviorT& AddBehavior();

	void RemoveComponent(Component& component);

	void RemoveComponent(GHandle<Component> handle);

	/** Detaches the given Component from this GameObject.
	* Returns the owning pointer of the detached Component. 
	* NOTE: Returns 'null' if the given Component is not attached to this GameObject. */
	void Detach(Component& component);

	/** Detaches the given Component from this GameObject.
	* Returns the owning pointer of the detached Component.
	* NOTE: Returns 'null' if the given handle does not refer to a Component of this GameObject. */
	void Detach(GHandle<Component> handle);

	void RemoveBehavior(Behavior& behavior);
	
	/** Initiates the destruction procedure for this GameObject. */
	void Destroy();

	/** Sets the location of this GameObject's root Component relative to its parent.
	* NOTE: If the root Component has no parent, this has the same effect as "SetWorldLocation".
	* NOTE: If this GameObject has no root Component, this has no effect. */
	FORCEINLINE void SetLocation(const Vec3& vec) final override
	{
		if (_rootComponent)
		{
			_rootComponent->SetLocation(vec);
		}
	}

	/** Sets the location of this GameObject's root Component in world space. 
	* NOTE: If this GameObject has no root Component, this has no effect. */
	FORCEINLINE void SetWorldLocation(const Vec3& vec) final override
	{
		if (_rootComponent)
		{
			_rootComponent->SetWorldLocation(vec);
		}
	}

	/** Translates this GameObject's root Component along the given vector, in local space.
	* NOTE: If this GameObject has no root Component, this has no effect. */
	FORCEINLINE void Translate(const Vec3& vec) final override
	{
		if (_rootComponent)
		{
			_rootComponent->Translate(vec);
		}
	}

	/** Translates this GameObject's root Component along the given vector, in world space.
	* NOTE: If this GameObject has no root Component, this has no effect. */
	FORCEINLINE void TranslateGlobal(const Vec3& vec) final override
	{
		if (_rootComponent)
		{
			_rootComponent->TranslateGlobal(vec);
		}
	}

	/** Sets the rotation of this GameObject's root Component relative to its parent.
	* NOTE: If the root Component has no parent, this has the same effect as "SetWorldRotation".
	* NOTE: If this GameObject has no root Component, this has no effect. */
	FORCEINLINE void SetRotation(const Quat& rot) final override
	{
		if (_rootComponent)
		{
			_rootComponent->SetRotation(rot);
		}
	}

	/** Sets the rotation of this GameObject's root Component in world space.
	* NOTE: If this GameObject has no root Component, this has no effect. */
	FORCEINLINE void SetWorldRotation(const Quat& rot) final override
	{
		if (_rootComponent)
		{
			_rootComponent->SetWorldRotation(rot);
		}
	}

	/** Rotates this GameObject's root Component along the given axis by the given angle, in local space.
	* NOTE: If this GameObject has no root Component, this has no effect. */
	FORCEINLINE void Rotate(const Vec3& axis, Angle angle) final override
	{
		if (_rootComponent)
		{
			_rootComponent->Rotate(axis, angle);
		}
	}

	/** Rotates this GameObject's root Component along the given axis by the given angle, in world space.
	* NOTE: If this GameObject has no root Component, this has no effect. */
	FORCEINLINE void RotateGlobal(const Vec3& axis, Angle angle) final override
	{
		if (_rootComponent)
		{
			_rootComponent->RotateGlobal(axis, angle);
		}
	}

	/** Sets this GameObject's root Component's scale to the given value.
	* NOTE: If this GameObject has no root Component, this has no effect. */
	FORCEINLINE void SetScale(const Vec3& scale) final override
	{
		if (_rootComponent)
		{
			_rootComponent->SetScale(scale);
		}
	}

	/** Scales this GameObject's root Component by the given value.
	* NOTE: If this GameObject has no root Component, this has no effect. */
	FORCEINLINE void Scale(const Vec3& scale) final override
	{
		if (_rootComponent)
		{
			_rootComponent->Scale(scale);
		}
	}

protected:

	/** Performs building procedure for this GameObject. */
	virtual void Build();

	/** Behavior for this GameObject upon spawning. */
	virtual void OnSpawn();

	/** Behavior for this GameObject upon destruction. */
	virtual void OnDestroy();

	////////////////
	///   Data   ///
private:

	World* _world;
	Component* _rootComponent;
	Table<Component::ID, Component*> _components;
	Array<UniquePtr<Behavior>> _behaviors;
	String _name;
	ID _id;
	bool _hasSpawned;
	bool _isDestroyed;
};
