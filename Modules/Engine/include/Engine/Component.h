// Component.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "Entity.h"

namespace Willow
{
	class ENGINE_API Component : public GameObject
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(GameObject)
		friend class Entity;

		////////////////////////
		///   Constructors   ///
	public:

		Component();
		~Component() override = 0;

		///////////////////
		///   Methods   ///
	public:

		void FromArchive(const ArchiveReader& reader) override;

		FORCEINLINE World& GetWorld() final override
		{
			return this->GetEntity().GetWorld();
		}

		FORCEINLINE const World& GetWorld() const final override
		{
			return this->GetEntity().GetWorld();
		}

		FORCEINLINE Vec3 GetLocation() const final override
		{
			return this->GetEntity().GetLocation();
		}

		FORCEINLINE Vec3 GetWorldLocation() const final override
		{
			return this->GetEntity().GetWorldLocation();
		}

		FORCEINLINE void SetLocation(const Vec3& location) final override
		{
			this->GetEntity().SetLocation(location);
		}

		FORCEINLINE void SetWorldLocation(const Vec3& location) final override
		{
			this->GetEntity().SetWorldLocation(location);
		}

		FORCEINLINE void Translate(const Vec3& vec) final override
		{
			this->GetEntity().Translate(vec);
		}

		FORCEINLINE void TranslateGlobal(const Vec3& vec) final override
		{
			this->GetEntity().TranslateGlobal(vec);
		}

		FORCEINLINE Quat GetRotation() const final override
		{
			return this->GetEntity().GetRotation();
		}

		FORCEINLINE Quat GetWorldRotation() const final override
		{
			return this->GetEntity().GetWorldRotation();
		}

		FORCEINLINE void SetRotation(const Quat& rot) final override
		{
			this->GetEntity().SetRotation(rot);
		}

		FORCEINLINE void SetWorldRotation(const Quat& rot) final override
		{
			this->GetEntity().SetWorldRotation(rot);
		}

		FORCEINLINE void Rotate(const Vec3& axis, Angle angle) final override
		{
			this->GetEntity().Rotate(axis, angle);
		}

		FORCEINLINE void RotateGlobal(const Vec3& axis, Angle angle) final override
		{
			this->GetEntity().RotateGlobal(axis, angle);
		}

		FORCEINLINE Vec3 GetScale() const final override
		{
			return this->GetEntity().GetScale();
		}

		FORCEINLINE void SetScale(const Vec3& scale) final override
		{
			this->GetEntity().SetScale(scale);
		}

		FORCEINLINE void Scale(const Vec3& vec) final override
		{
			this->GetEntity().Scale(vec);
		}

		FORCEINLINE Mat4 GetTransformationMatrix() const final override
		{
			return this->GetEntity().GetTransformationMatrix();
		}

		FORCEINLINE Entity* GetParent() final override
		{
			return this->GetEntity().GetParent();
		}

		FORCEINLINE const Entity* GetParent() const final override
		{
			return this->GetEntity().GetParent();
		}

		/** Returns the Entity that this Component is a part of. */
		FORCEINLINE Entity& GetEntity()
		{
			return *_entity;
		}

		/** Returns the Entity that this Component is a part of. */
		FORCEINLINE const Entity& GetEntity() const
		{
			return *_entity;
		}

		/** Returns a pointer to the Actor that this Component is attached to. */
		FORCEINLINE Entity* GetActor()
		{
			return this->GetEntity().GetActor();
		}

		/** Returns a pointer to the Actor that this Component is attached to. */
		FORCEINLINE const Entity* GetActor() const
		{
			return this->GetEntity().GetActor();
		}

		/** Returns whether this entity is parented (directly or indirectly) to the given entity. */
		FORCEINLINE bool IsParentedTo(const Entity& entity) const
		{
			return this->GetEntity().IsParentedTo(entity);
		}

		/** Sets the parent of this Entity as the given Entity.
		* parent: The Entity being parented to. Use 'nullptr' for no parent. */
		FORCEINLINE void SetParent(Entity* parent, SetParentOffsetMode mode = SP_KeepWorldOffset)
		{
			this->GetEntity().SetParent(parent, mode);
		}

		////////////////
		///   Data   ///
	private:

		Entity* _entity;
	};

	inline Component::~Component()
	{
		// 'Component' is abstract
	}
}
