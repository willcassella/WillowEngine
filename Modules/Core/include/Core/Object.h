// Object.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "config.h"
#include "Forwards/Core.h"
#include "Forwards/Reflection.h"

/////////////////
///   Types   ///

/** Base of every polymorphic type in the engine */
class CORE_API Object
{
	///////////////////////
	///   Information   ///
public:

	template <class ObjecT>
	friend struct Ptr;

	/** Type information for 'Object' */
	static const ClassInfo StaticTypeInfo;

	////////////////////////
	///   Constructors   ///
public:

	Object();
	Object(const Object& copy);
	Object(Object&& move);
	virtual ~Object();

	///////////////////
	///   Methods   ///
public:

	/** Returns the type information for this Object */
	virtual const ClassInfo& GetType() const = 0;

private:

	/** Registers a reference to the given Object. */
	static void AddReference(const Object*& reference);

	/** Unregisters a reference to the given Object. */
	template <class T>
	FORCEINLINE static void AddReference(T*& reference)
	{
		static_assert(std::is_base_of<Object, T>::value || std::is_base_of<Interface, T>::value,
			"The pointed type must extend either 'Object' or 'Interface'");

		AddReference((const Object*&)reference);
	}

	/** Unregisters a reference to the given Object. */
	static void RemoveReference(const Object*& reference);

	/** Unregisters a reference to the given Object. */
	template <class T>
	FORCEINLINE static void RemoveReference(T*& reference)
	{
		static_assert(std::is_base_of<Object, T>::value || std::is_base_of<Interface, T>::value,
			"The pointed type must extend either 'Object' or 'Interface'");

		RemoveReference((const Object*&)reference);
	}

	/////////////////////
	///   Operators   ///

	Object& operator=(const Object& copy) = default;
	Object& operator=(Object&& move);
};
