// Core.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

/////////////////
///   Types   ///

/** Defined in 'String.h' */
struct String;

/** Defined in 'Object.h */
class Object;

/** Defined in 'Interface.h' */
class Interface;

/** Defined in 'Application.h' */
class Application;

/////////////////////
///   Functions   ///

/** Defined in 'String.h' */
template <typename ... T>
String Format(const String& format, const T& ... values);

/** Defined in 'String.h' */
template <typename ... T>
String Parse(const String& string, const String& format, T& ... values);
