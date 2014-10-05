// Scene.h
#pragma once

#include <Utility\Queue.h>
#include "GameObject.h"
#include "Camera.h"

namespace Willow
{
	// Scene class contains all game objects and scene information
	// @TODO: this needs some serious work
	class CORE_API Scene
	{
		///////////////////////
		///   Information   ///
	public:

		//////////////////
		///   Fields   ///
	public:

		float TimeDilation = 1.0f;
		float TimeStep = 1.f / 60;

		// @TODO: This needs to be replaced
		List<Camera*> Cameras;

		////////////////////////
		///   Constructors   ///
	public:

		// @TODO: Rule of 5
		~Scene();

		///////////////////
		///   Methods   ///
	public:

		void Update();
		void DispatchEvent(const String& eventName, float value);
		void Render() const;

		template <class GameObjectClass>
		GameObjectClass& AddObject(GameObjectClass* object)
		{
			object->_scene = this;
			_freshObjects.Push(object);
			return *object;
		}

		////////////////
		///   Data   ///
	private:

		List<GameObject*> _objects;
		Queue<GameObject*> _freshObjects;
		Queue<GameObject*> _staleObjects;
	};
}