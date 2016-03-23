// SphereColliderComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "ColliderComponent.h"

namespace Willow
{
	class ENGINE_API SphereColliderComponent final : public ColliderComponent
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(ColliderComponent)

		/////////////////////
		///   Constants   ///
	public:

		/** The default radius for SphereColliders. */
		static constexpr float DefaultRadius = 1.f;

		////////////////////////
		///   Constructors   ///
	public:
		
		SphereColliderComponent();
		~SphereColliderComponent() override;

		///////////////////
		///   Methods   ///
	public:

		void ToArchive(ArchiveWriter& writer) const override;

		void FromArchive(const ArchiveReader& reader) override;

		float GetRadius() const;

		void SetRadius(float radius, UpdateEntityColliderOptions updateOptions = UpdateAll);

	protected:

		void OnSpawn() override;

	private:

		btCollisionShape* GetCollisionShape() const override;

		void EDITOR_SetRadius(float radius);

		////////////////
		///   Data   ///
	private:

		std::unique_ptr<btSphereShape> _shape;
	};
}
