// GameObject.h
#pragma once

#include "EventManager.h"
#include "Transform.h"
#include "Component.h"

namespace Willow
{
	class CORE_API GameObject
	{
		///////////////////////
		///   Information   ///
	public:

		friend class Scene;

		//////////////////
		///   Fields   ///
	public:

		String Name;
		Transform Transform;
		// @TODO: Move this into the Player system when that's ready
		EventManager EventManager;

		////////////////////////
		///   Constructors   ///
	public:

		GameObject(const String& name = "");

	protected:

		/* GameObjects should be deleted through the scene. Use Destroy() instead */
		virtual ~GameObject() = default;

		///////////////////
		///   Methods   ///
	public:

		Scene& GetScene();
		const Scene& GetScene() const;
		void Destroy();
		bool IsDestroyed() const;
		// @TODO: Should there be a const version of this?
		virtual List<Component*> GetComponents();

	protected:

		virtual void Tick(float timeInterval);
		virtual void OnDestroy();

		////////////////
		///   Data   ///
	private:

		Scene* _scene;
		bool _isDestroyed;
	};
}