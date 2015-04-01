// PointerInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/PointerInfo.h"
#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Reflection/StructInfo.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(PointerInfo);

////////////////////////
///   Constructors   ///

PointerInfo::PointerInfo(PointerInfo&& move)
	: Super(std::move(move)), _pointedType(move._pointedType), _isConst(move._isConst)
{
	// All done
}

///////////////////
///   Methods   ///

String PointerInfo::GetName() const
{
	if (_isConst)
	{
		return String::Format("const @*", _pointedType->GetName());
	}
	else
	{
		return String::Format("@*", _pointedType->GetName());
	}
}

bool PointerInfo::IsCastableTo(const TypeInfo& type) const
{
	// Make sure the given type is a pointer type
	if (type.GetType().Extends<PointerInfo>())
	{
		const PointerInfo& pointerType = static_cast<const PointerInfo&>(type);

		// If this type is a const pointer and the other is not, these are not compatible
		if (IsConst() && !pointerType.IsConst())
		{
			return false;
		}

		// If the pointed types are compatible, then we're good to go
		return GetPointedType().IsCastableTo(pointerType.GetPointedType());
	}
	else
	{
		return false;
	}
}