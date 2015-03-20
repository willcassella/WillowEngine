// GameObject.h
#pragma once

#include "EventManager.h"
#include "Transform.h"
#include "Component.h"

namespace Willow
{
	class CORE_API GameObject : public object
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE
		EXTENDS(object)
		friend Scene;
		friend Component;

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

		GameObject();
		~GameObject() override;

		///////////////////
		///   Methods   ///
	public:

		Scene& GetScene();
		const Scene& GetScene() const;
		void Destroy();
		bool IsDestroyed() const;
		List<Component*> GetComponents() const;

		template <class ComponentType>
		ComponentType& AddComponent()
		{
			ComponentType* component = new ComponentType(This);
			_managedComponents.Add(component);
			return *component;
		}

		template <class ComponentType>
		List<ComponentType*> GetComponentsOfType()
		{
			List<ComponentType*> matches;

			for (auto& component : _components)
			{
				if (component->IsA<ComponentType>())
				{
					matches.Add((ComponentType*)component);
				}
			}

			return matches;
		}

	protected:

		virtual void Update(float timeInterval);
		virtual void OnDestroy();

		////////////////
		///   Data   ///
	private:

		List<Component*> _components;
		List<Component*> _managedComponents;
		Scene* _scene;
		bool _isDestroyed;
	};
}