// Component.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "Entity.h"

namespace willow
{
	class ENGINE_API Component : public GameObject
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

		Component();
		~Component() override = 0;

		///////////////////
		///   Methods   ///
	public:

		void FromArchive(const ArchiveReader& reader) override;

		FORCEINLINE Vec3 get_location() const final override
		{
			return this->get_entity().get_location();
		}

		FORCEINLINE Vec3 get_world_location() const final override
		{
			return this->get_entity().get_world_location();
		}

		FORCEINLINE void set_location(const Vec3& location) final override
		{
			this->get_entity().set_location(location);
		}

		FORCEINLINE void set_world_location(const Vec3& location) final override
		{
			this->get_entity().set_world_location(location);
		}

		FORCEINLINE void translate(const Vec3& vec) final override
		{
			this->get_entity().translate(vec);
		}

		FORCEINLINE void translate_global(const Vec3& vec) final override
		{
			this->get_entity().translate_global(vec);
		}

		FORCEINLINE Quat get_rotation() const final override
		{
			return this->get_entity().get_rotation();
		}

		FORCEINLINE Quat get_world_rotation() const final override
		{
			return this->get_entity().get_world_rotation();
		}

		FORCEINLINE void set_rotation(const Quat& rot) final override
		{
			this->get_entity().set_rotation(rot);
		}

		FORCEINLINE void set_world_rotation(const Quat& rot) final override
		{
			this->get_entity().set_world_rotation(rot);
		}

		FORCEINLINE void rotate(const Vec3& axis, Angle angle) final override
		{
			this->get_entity().rotate(axis, angle);
		}

		FORCEINLINE void rotate_global(const Vec3& axis, Angle angle) final override
		{
			this->get_entity().rotate_global(axis, angle);
		}

		FORCEINLINE Vec3 get_scale() const final override
		{
			return this->get_entity().get_scale();
		}

		FORCEINLINE void set_scale(const Vec3& scale) final override
		{
			this->get_entity().set_scale(scale);
		}

		FORCEINLINE void scale(const Vec3& vec) final override
		{
			this->get_entity().scale(vec);
		}

		FORCEINLINE Mat4 get_transformation_matrix() const final override
		{
			return this->get_entity().get_transformation_matrix();
		}

		FORCEINLINE Entity* get_parent() final override
		{
			return this->get_entity().get_parent();
		}

		FORCEINLINE const Entity* get_parent() const final override
		{
			return this->get_entity().get_parent();
		}

		/** Returns the Entity that this Component is a part of. */
		FORCEINLINE Entity& get_entity()
		{
			return *this->_entity;
		}

		/** Returns the Entity that this Component is a part of. */
		FORCEINLINE const Entity& get_entity() const
		{
			return *this->_entity;
		}

		/** Returns a pointer to the Actor that this Component is attached to. */
		FORCEINLINE Entity* GetActor()
		{
			return this->get_entity().get_actor();
		}

		/** Returns a pointer to the Actor that this Component is attached to. */
		FORCEINLINE const Entity* GetActor() const
		{
			return this->get_entity().get_actor();
		}

		/** Returns whether this entity is parented (directly or indirectly) to the given entity. */
		FORCEINLINE bool IsParentedTo(const Entity& entity) const
		{
			return this->get_entity().is_parented_to(entity);
		}

		/** Sets the parent of this Entity as the given Entity.
		* parent: The Entity being parented to. Use 'nullptr' for no parent. */
		FORCEINLINE void SetParent(Entity* parent, SetParentOffsetMode mode = SP_Keep_World_Offset)
		{
			this->get_entity().set_parent(parent, mode);
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
