// Component.h
#pragma once

#include <Utility\Math\Mat4.h>
#include "config.h"

namespace Willow
{
	class CORE_API Component : public object
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE
		EXTENDS(object)
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

		virtual void Update(float timeInterval);
		virtual void Render(const Mat4& view, const Mat4& proj);

		////////////////
		///   Data   ///
	private:

		GameObject* _owner;
		bool _isEnabled;
	};
}