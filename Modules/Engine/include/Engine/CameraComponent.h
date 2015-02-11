// CameraComponent.h - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "GameObject.h"

class ENGINE_API CameraComponent : public Component
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(Component);

	////////////////////////
	///   Constructors   ///
public:

	CameraComponent(GameObject& owner);

	//////////////////
	///   Fields   ///
public:

	float VFOV = 43.f;
	float Ratio = 1280.f / 720.f;
	float ZMin = 0.1f;
	float ZMax = 90.f;

	///////////////////
	///   Methods   ///
public:

	Mat4 GetPerspective() const;
};