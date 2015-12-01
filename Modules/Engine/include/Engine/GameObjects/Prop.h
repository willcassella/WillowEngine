// Prop.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../GameObject.h"
#include "../Components/StaticMeshComponent.h"

class ENGINE_API Prop : public GameObject
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(GameObject)

	///////////////////
	///   Methods   ///
public:

	FORCEINLINE auto GetStaticMeshComponent() const
	{
		return _meshComponent;
	}

protected:

	void Build() override;

	////////////////
	///   Data   ///
private:

	GHandle<StaticMeshComponent> _meshComponent;
};
