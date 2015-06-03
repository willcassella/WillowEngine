// TypeInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Application.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(TypeInfo);

////////////////////////
///   Constructors   ///

TypeInfo::TypeInfo(void* /*dummy*/, const String& name)
	: _name(name)
{
	_defaultConstructor = []()->void* { return nullptr; };
	_copyConstructor = [](const void* /*copy*/)->void* { return nullptr; };
	_moveConstructor = [](void* /*move*/)->void* { return nullptr; };
	_copyAssignmentOperator = [](void* /*value*/, const void* /*copy*/)->bool { return false; };
	_moveAssigmentOperator = [](void* /*value*/, void* /*move*/)->bool { return false; };
	_destructor = [](void* value)->bool { return false; };

	_toStringImplementation = [](const void* /*value*/)->String { return ""; };
	_fromStringImplementation = [](void* /*value*/, const String& string)->String { return string; };

	_size = 0;
	_isAbstract = false;
	_isPolymorphic = false;
	_isDefaultConstructible = false;
	_isCopyConstructible = false;
	_isMoveConstructible = false;
	_isCopyAssignable = false;
	_isMoveAssignable = false;
	_isDestructible = false;

	RegisterWithApplication();
}

TypeInfo::TypeInfo(TypeInfo&& move)
	: _name(std::move(move._name))
{
	_defaultConstructor = move._defaultConstructor;
	_copyConstructor = move._copyConstructor;
	_moveConstructor = move._moveConstructor;
	_copyAssignmentOperator = move._copyAssignmentOperator;
	_moveAssigmentOperator = move._moveAssigmentOperator;
	_destructor = move._destructor;

	_toStringImplementation = move._toStringImplementation;
	_fromStringImplementation = move._fromStringImplementation;

	_size = move._size;
	_isAbstract = move._isAbstract;
	_isPolymorphic = move._isPolymorphic;
	_isDefaultConstructible = move._isDefaultConstructible;
	_isCopyConstructible = move._isCopyConstructible;
	_isMoveConstructible = move._isMoveConstructible;
	_isCopyAssignable = move._isCopyConstructible;
	_isMoveAssignable = move._isMoveAssignable;
	_isDestructible = move._isDestructible;

	RegisterWithApplication();
}

TypeInfo::~TypeInfo()
{
	Application::Instance()._types.DeleteAll(This);
}

///////////////////
///   Methods   ///

String TypeInfo::GetName() const
{
	return _name;
}

void TypeInfo::RegisterWithApplication()
{
	Application::Instance()._types.Add(This);
}