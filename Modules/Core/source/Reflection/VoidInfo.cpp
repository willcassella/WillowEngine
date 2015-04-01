// VoidInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/VoidInfo.h"
#include "../../include/Core/Reflection/ClassInfo.h"

//////////////////////
///   Reflection   ///

//CLASS_REFLECTION(VoidInfo);
//
//////////////////////////
/////   Constructors   ///
//
//VoidInfo::VoidInfo(VoidInfo&& move)
//	: Super(std::move(move))
//{
//	// All done
//}
//
//VoidInfo::VoidInfo()
//	: Super(static_cast<void*>(nullptr), "void")
//{
//	// All done
//}
//
/////////////////////
/////   Methods   ///
//
//bool VoidInfo::IsAbstract() const
//{
//	return false;
//}
//
//bool VoidInfo::IsPolymorphic() const
//{
//	return false;
//}
//
//bool VoidInfo::IsCastableTo(const TypeInfo& type) const
//{
//	return type == TypeOf<void>();
//}
//
////////////////////////////
/////   Implementation   ///
//
//namespace Implementation
//{
//	const VoidInfo TypeOf<void>::StaticTypeInfo = VoidInfo();
//}