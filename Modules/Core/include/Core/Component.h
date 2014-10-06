// Component.h
#pragma once

#include <Utility\Math\Mat4.h>
#include "config.h"

namespace Willow
{
	class CORE_API Component
	{
		///////////////////////
		///   Information   ///
	public:

		friend class Scene;

		////////////////////////
		///   Constructors   ///
	public:

		Component(class GameObject& owner);
		virtual ~Component() = default;

		///////////////////
		///   Methods   ///
	public:

		bool IsEnabled() const;
		void Enable();
		void Disable();
		GameObject& GetOwner();
		const GameObject& GetOwner() const;

	protected:

		virtual void OnSceneUpdate(float timeInterval);
		virtual void OnRender(const Mat4& view, const Mat4& proj);

		////////////////
		///   Data   ///
	private:

		GameObject& _owner;
		bool _isEnabled;
	};
}