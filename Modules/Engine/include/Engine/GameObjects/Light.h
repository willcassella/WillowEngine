// Light.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../GameObject.h"
#include "../Components/LightComponent.h"

class ENGINE_API Light : public GameObject
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(GameObject)

	///////////////////
	///   Methods   ///
public:

	FORCEINLINE auto GetLightComponent() const
	{
		return _lightComponent;
	}

protected:

	void Build() override;

	//////////////////////
	///   Components   ///
private:

	GHandle<LightComponent> _lightComponent;
};
