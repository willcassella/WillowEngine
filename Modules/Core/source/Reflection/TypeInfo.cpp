// TypeInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Application.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(TypeInfo);

////////////////////////
///   Constructors   ///

TypeInfo::TypeInfo(TypeInfo&& move)
	: _name(std::move(move._name)), _constructor(move._constructor), _copyConstructor(move._copyConstructor),
	_copyAssignmentOperator(move._copyAssignmentOperator), _destructor(move._destructor), _toStringImplementation(move._toStringImplementation),
	_fromStringImplementation(move._fromStringImplementation), _size(move._size), _isAbstract(move._isAbstract), _isPolymorphic(move._isPolymorphic),
	_isDefaultConstructible(move._isDefaultConstructible), _isCopyConstructible(move._isCopyConstructible), _isCopyAssignable(move._isCopyAssignable),
	_isDestructible(move._isDestructible)
{
	RegisterWithApplication();
}

TypeInfo::~TypeInfo()
{
	Application::Instance()._types.DeleteAll(this);
}

///////////////////
///   Methods   ///

String TypeInfo::GetName() const
{
	return _name;
}

void TypeInfo::RegisterWithApplication()
{
	Application::Instance()._types.Add(this);
}