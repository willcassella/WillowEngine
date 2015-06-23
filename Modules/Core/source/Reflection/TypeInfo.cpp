// TypeInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Application.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(TypeInfo)
.AddProperty("Name", "The name of the type.", &TypeInfo::GetName, nullptr)
.AddProperty("Size", "The size (in bytes) of an instance of this type.", &TypeInfo::_size, nullptr)
.AddProperty("Compound", "Whether this type is a compound type.", &TypeInfo::_isCompound, nullptr)
.AddProperty("Abstract", "Whether this type is an abstract type.", &TypeInfo::_isAbstract, nullptr)
.AddProperty("Polymorphic", "Whether this type is polymorphic.", &TypeInfo::_isPolymorphic, nullptr)
.AddProperty("Default-Constructible", "Whether this type is default-constructible", &TypeInfo::_isDefaultConstructible, nullptr)
.AddProperty("Copy-Constructible", "Whether this type is copy-constructible.", &TypeInfo::_isCopyConstructible, nullptr)
.AddProperty("Move-Constructible", "Whether this type is move-constructible.", &TypeInfo::_isMoveConstructible, nullptr)
.AddProperty("Copy-Assignable", "Whether this type is copy-assignable.", &TypeInfo::_isCopyAssignable, nullptr)
.AddProperty("Move-Assignable", "Whether this type is move-assignable.", &TypeInfo::_isMoveAssignable, nullptr)
.AddProperty("Destructible", "Whether this type is destructible.", &TypeInfo::_isDestructible, nullptr);

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
	Application::Instance()._types.DeleteAll(self);
}

///////////////////
///   Methods   ///

String TypeInfo::GetName() const
{
	return _name;
}

Variant TypeInfo::Construct() const
{
	return Variant(_defaultConstructor(), self);
}

void TypeInfo::RegisterWithApplication()
{
	Application::Instance()._types.Add(self);
}