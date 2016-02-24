// Entity.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "Forwards/Engine.h"
#include "GameObject.h"
#include "Transform.h"

namespace Willow
{
	/** An 'Entity' is a collection of Components that should be together thought of as a single object.
	* Components can be added and removed ("connected" and "disconnected") from an Entity, but they cannot be moved between Entities.
	* Components are always connected to a single Entity.
	* Entities can be parented to one-another via 'Attach', or 'SetParent'.
	* The Entity class may be extended, creating an 'Actor'. */
	class ENGINE_API Entity : public GameObject
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(GameObject)
		friend class World;

		////////////////////////
		///   Constructors   ///
	public:

		Entity();

		///////////////////
		///   Methods   ///
	public:

		void ToArchive(ArchiveWriter& writer) const override;

		FORCEINLINE World& GetWorld() final override
		{
			return *_world;
		}

		FORCEINLINE const World& GetWorld() const final override
		{
			return *_world;
		}

		Vec3 GetLocation() const final override;

		Vec3 GetWorldLocation() const final override;

		void SetLocation(const Vec3& location) final override;

		void SetWorldLocation(const Vec3& location) final override;

		void Translate(const Vec3& vec) final override;

		void TranslateGlobal(const Vec3& vec) final override;

		Quat GetRotation() const final override;

		Quat GetWorldRotation() const final override;

		void SetRotation(const Quat& rot) final override;

		void SetWorldRotation(const Quat& rot) final override;

		void Rotate(const Vec3& axis, Angle angle) final override;

		void RotateGlobal(const Vec3& axis, Angle angle) final override;

		Vec3 GetScale() const final override;

		void SetScale(const Vec3& scale) final override;

		void Scale(const Vec3& vec) final override;

		Mat4 GetTransformationMatrix() const final override;

		FORCEINLINE Entity* GetParent() final override
		{
			return _parent;
		}

		FORCEINLINE const Entity* GetParent() const final override
		{
			return _parent;
		}

		/** Returns the name of this Entity. */
		FORCEINLINE const String& GetName() const /*&*/
		{
			return _name;
		}

		/** Returns whether this Entity is an Actor.
		* An 'Actor' is any class that extends 'Entity'. */
		bool IsActor() const;

		/** Returns the Actor that this Entity is directly (or indirectly) parented to.
		* NOTE: If this Entity is itself an Actor, returns a pointer to itself.
		* NOTE: If this Entity is not attached to an Actor, returns 'null'. */
		Entity* GetActor();

		/** Returns the Actor that this Entity is directly (or indirectly) attached to.
		* NOTE: If this Entity is itself an Actor, returns a pointer to itself.
		* NOTE: If this Entity is not attached to an Actor, returns 'null'. */
		const Entity* GetActor() const;

		/** Returns whether this Entity is parented to the given Entity (directly or indirectly). */
		bool IsParentedTo(const Entity& entity) const;

		/** Sets the parent of this Entity as the given Entity.
		* parent: The Entity being parented to. Use 'nullptr' for no parent. */
		void SetParent(Entity* parent, SetParentOffsetMode mode = SP_KeepWorldOffset);

		/** Connects a new instance of the given Component type to this Entity. */
		template <class T>
		T& Connect();

		/** Parents a new instance of the given type to this Entity.
		* Returns a reference to the new object. */
		template <class T>
		T& Attach();

		/** Parents a new instance of the given type to this Entity.
		* Returns a reference to the new object.
		* Sets the name of the spawned Entity to the given name. */
		template <class T>
		T& Attach(String name);

		/** Enumerates all components of the given type connected to this Entity. */
		template <class T = Component>
		auto EnumerateConnected()
		{
			Array<T*> result;

			for (auto& component : _components)
			{
				if (auto c = Cast<T>(*component))
				{
					result.Add(c);
				}
			}

			return result;
		}

		/** Enumerates all components of the given type connected to this Entity. */
		template <class T = Component>
		auto EnumerateConnected() const
		{
			Array<const T*> result;

			for (const auto& component : _components)
			{
				if (auto c = Cast<T>(*component))
				{
					result.Add(c);
				}
			}

			return result;
		}

		/** Enumerates all Entities attached to this Entity (children). */
		template <class T = Entity>
		auto EnumerateChildren()
		{
			Array<T*> result;

			for (auto& child : _children)
			{
				if (auto c = Cast<T>(*child))
				{
					result.Add(c);
				}
			}

			return result;
		}

		/** Enumerates all Entities attached to this Entity (children). */
		template <class T = Entity>
		auto EnumerateChildren() const
		{
			Array<const T*> result;

			for (const auto& child : _children)
			{
				if (auto c = Cast<T>(*child))
				{
					result.Add(c);
				}
			}

			return result;
		}

	protected:

		void OnDestroy() override;

	private:

		void Editor_SetName(String name);

		////////////////
		///   Data   ///
	private:

		String _name;
		World* _world;
		Array<Component*> _components;

		Transform _transform;
		Entity* _parent;
		Array<Entity*> _children;
	};
}
