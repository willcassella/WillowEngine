// StaticMeshComponent.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Engine/World.h"
#include "../../include/Engine/Components/StaticMeshComponent.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::StaticMeshComponent)
.Field("Visible", &StaticMeshComponent::Visible)
.Field("Mesh", &StaticMeshComponent::Mesh)
.Field("Material", &StaticMeshComponent::Material)
.Field("InstanceParams", &StaticMeshComponent::InstanceParams);
