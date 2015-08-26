// ArchNode.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Core/ArchNode.h"
#include "../include/Core/Reflection/ClassInfo.h"
#include "../include/Core/Reflection/StructInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(ArchNode)
.AddProperty("Name", "", &ArchNode::GetName, nullptr);
