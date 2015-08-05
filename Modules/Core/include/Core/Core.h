// Core.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
/** Since a lot of the core behavior is spread out across many header files, this includes all of them */
#pragma once

////////////////
///   Core   ///

#include "Console.h"
#include "Object.h"
#include "Interface.h"
#include "Application.h"

//////////////////////
///   Containers   ///

#include "Containers/Array.h"
#include "Containers/List.h"
#include "Containers/Pair.h"
#include "Containers/Queue.h"
#include "Containers/Stack.h"
#include "Containers/Table.h"
#include "Containers/Tuple.h"

//////////////////
///   Memory   ///

#include "Memory/New.h"
#include "Memory/OwnerPtr.h"
#include "Memory/SharedPtr.h"
#include "Memory/Ptr.h"

/////////////////
///   Event   ///

#include "Event/Event.h"
#include "Event/EventHandler.h"
#include "Event/EventManager.h"

//////////////////////
///   Reflection   ///

#include "Reflection/PointerInfo.h"
#include "Reflection/EnumInfo.h"
#include "Reflection/StructInfo.h"
#include "Reflection/ClassInfo.h"
#include "Reflection/InterfaceInfo.h"
#include "Reflection/VoidInfo.h"
#include "Reflection/Variant.h"
#include "Reflection/Module.h"

//////////////////////
///   Operations   ///

#include "Operations/ToString.h"
#include "Operations/FromString.h"

////////////////
///   Misc   ///

#include "Misc/Signature.h"
#include "Misc/TimeStamp.h"
