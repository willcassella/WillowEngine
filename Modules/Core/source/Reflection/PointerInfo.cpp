// PointerInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/PointerInfo.h"
#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Reflection/StructInfo.h"
#include "../../include/Core/Reflection/VoidInfo.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(PointerInfo);

////////////////////////
///   Constructors   ///

TypeInfoBuilder<std::nullptr_t, PointerInfo>::TypeInfoBuilder()
	: TypeInfoBuilderBase<std::nullptr_t, PointerInfo>("nullptr")
{
	_data.PointedType = &TypeOf<void>();
	_data.IsConst = false;
	_data.IsNullptr = true;
}

///////////////////
///   Methods   ///

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

String PointerInfo::GenerateName() const
{
	if (_data.IsConst)
	{
		// If we have a pointer to a pointer
		if (_data.PointedType->GetType() == TypeOf<PointerInfo>())
		{
			return Format("@ const*", _data.PointedType->GetName());
		}
		else
		{
			return Format("const @*", _data.PointedType->GetName());
		}
	}
	else
	{
		return Format("@*", _data.PointedType->GetName());
	}
}
