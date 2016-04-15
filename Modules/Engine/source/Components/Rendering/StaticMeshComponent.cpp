// StaticMeshComponent.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../../include/Engine/World.h"
#include "../../../include/Engine/Components/Rendering/StaticMeshComponent.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::StaticMeshComponent)
.Field("visible", &StaticMeshComponent::visible)
.Field("mesh", &StaticMeshComponent::mesh)
.Field("material", &StaticMeshComponent::material)
.Field("instance_params", &StaticMeshComponent::instance_params);
