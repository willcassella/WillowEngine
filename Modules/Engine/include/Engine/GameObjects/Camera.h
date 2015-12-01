// Camera.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../GameObject.h"
#include "../Components/CameraComponent.h"

class ENGINE_API Camera : public GameObject
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(GameObject)

	///////////////////
	///   Methods   ///
public:

	/** Returns the perspective matrix of the CameraComponent attached to this Camera. */
	FORCEINLINE Mat4 GetPerspective() const
	{ 
		return GetComponent(_cameraComponent)->GetPerspective();
	}
	
	/** Returns the CameraComponent attached to this Camera. */
	FORCEINLINE auto GetCameraComponent() const
	{
		return _cameraComponent;
	}

protected:

	void Build() override;

	////////////////
	///   Data   ///
private:

	GHandle<CameraComponent> _cameraComponent;
};