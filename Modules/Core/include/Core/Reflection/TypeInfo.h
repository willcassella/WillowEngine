// TypeInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../String.h"
#include "../Object.h"

/////////////////
///   Types   ///

/** Base of every reflection meta-class in the engine */
class CORE_API TypeInfo : public Object
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(Object);
	friend Variant;
	friend VoidInfo;
	template <typename AnyType> friend String ToString(const AnyType&);
	template <typename AnyType> friend String FromString(AnyType&, const String&);

	////////////////////////
	///   Constructors   ///
public:

	TypeInfo(const TypeInfo& copy) = delete;
	TypeInfo(TypeInfo&& move);
	~TypeInfo() override;

protected:

	/** @TODO: Documentation */
	template <typename AnyType>
	TypeInfo(AnyType* dummy, const String& name)
		: _name(name)
	{
		_constructor = []()->void* 
		{ 
			return Implementation::Construct<AnyType>::Function();
		};
		_copyConstructor = [](const void* copy)->void* 
		{ 
			return Implementation::CopyConstruct<AnyType>::Function(*static_cast<const AnyType*>(copy)); 
		};
		_copyAssignmentOperator = [](void* value, const void* copy)->bool 
		{
			return Implementation::CopyAssign<AnyType>::Function(*static_cast<AnyType*>(value), *static_cast<const AnyType*>(copy));
		};
		_destructor = [](void* value)->bool
		{
			return Implementation::Destroy<AnyType>::Function(*static_cast<AnyType*>(value));
		};

		_size = sizeof(AnyType);
		_isDefaultConstructible = std::is_default_constructible<AnyType>::value;
		_isCopyConstructible = std::is_copy_constructible<AnyType>::value;
		_isCopyAssignable = std::is_copy_assignable<AnyType>::value;
		_isDestructible = std::is_destructible<AnyType>::value;
	}

private:

	/** Special constructor for creating TypeInfo for 'void'  */
	TypeInfo(const String& name);

	///////////////////
	///   Methods   ///
public:

	/** Returns the static size of this type */
	uint32 GetSize() const;

	/** Returns the name of this type */
	virtual String GetName() const;

	/** Returns whether this type is abstract
	* i.e - It has at least one pure virtual function */
	virtual bool IsAbstract() const = 0;

	/** Returns whether this type is polymorphic
	* i.e - It has at least one virtual function */
	virtual bool IsPolymorphic() const = 0;

	/** Returns whether this type is default-constructible */
	FORCEINLINE bool IsDefaultConstructible() const
	{
		return _isDefaultConstructible;
	}

	/** Returns whether this type is copy-constructible */
	FORCEINLINE bool IsCopyConstructible() const
	{
		return _isCopyConstructible;
	}

	/** Returns whether this type is copy-assignable */
	FORCEINLINE bool IsCopyAssignable() const
	{
		return _isCopyAssignable;
	}

	/** Returns whether this type is destructible */
	FORCEINLINE bool IsDestructible() const
	{
		return _isDestructible;
	}

	/** Returns whether this type is bitwise castable to the given type */
	virtual bool IsCastableTo(const TypeInfo& type) const = 0;

	/** Returns a Variant to an instance of this type
	* NOTE: Callee has ownership over the lifetime of returned value (it must be deleted manually)
	* NOTE: Returns a "void" Variant if this type is not default-constructible, check 'IsConstructible()' before calling */
	Variant Construct() const;
	
	/** Returns whether this type is bitwise castable to the given type */
	template <typename AnyType>
	FORCEINLINE bool IsCastableTo() const
	{
		return IsCastableTo(TypeOf<AnyType>());
	}

	/////////////////////
	///   Operators   ///
public:

	TypeInfo& operator=(const TypeInfo& copy) = delete;
	TypeInfo& operator=(TypeInfo&& move) = delete;
	friend FORCEINLINE CORE_API bool operator==(const TypeInfo& lhs, const TypeInfo& rhs)
	{
		return lhs.GetName() == rhs.GetName();
	}
	friend FORCEINLINE CORE_API bool operator!=(const TypeInfo& lhs, const TypeInfo& rhs)
	{
		return lhs.GetName() != rhs.GetName();
	}

	////////////////
	///   Data   ///
private:

	String _name;
	void*(*_constructor)();
	void*(*_copyConstructor)(const void*);
	bool(*_copyAssignmentOperator)(void*, const void*);
	bool(*_destructor)(void*);
	String(*_toStringImplementation)(const void*);
	String(*_fromStringImplementation)(void*, const String&);
	uint32 _size;
	bool _isDefaultConstructible;
	bool _isCopyConstructible;
	bool _isCopyAssignable;
	bool _isDestructible;
};

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Default implementation of "Cast" */
	template <typename TargetType, typename AnyType>
	struct Cast
	{
		/** Attempt to cast reference */
		FORCEINLINE static TargetType* Function(AnyType& value)
		{
			if (::TypeOf(value).template IsCastableTo<TargetType>())
			{
				return reinterpret_cast<TargetType*>(&value);
			}
			else
			{
				return nullptr;
			}
		}

		/** Attempt to cast const reference */
		FORCEINLINE static const TargetType* Function(const AnyType& value)
		{
			if (::TypeOf(value).template IsCastableTo<TargetType>())
			{
				return reinterpret_cast<const TargetType*>(&value);
			}
			else
			{
				return nullptr;
			}
		}
	};
}

/////////////////////
///   Functions   ///

/** Safely casts from a reference of one type to the target class/interface/type
* WARNING: Returns a null pointer if the cast is invalid (value does not legally translate to the given type)
* DO NOT OVERLOAD: Specialize struct 'Implementation::Cast' */
template <typename TargetType, typename AnyType>
FORCEINLINE TargetType* Cast(AnyType& value)
{
	static_assert(!std::is_reference<TargetType>::value, "Using 'Cast' to cast to a reference type is not allowed");
	return Implementation::Cast<TargetType, AnyType>::Function(value);
}

/** Safely casts from an immutable reference of one type to the target class/interface/type
* WARNING: Returns a null pointer if the cast is invalid (value does not legally translate to the given type)
* DO NOT OVERLOAD: Specialize struct 'Implementation::Cast' */
template <typename TargetType, typename AnyType>
FORCEINLINE const TargetType* Cast(const AnyType& value)
{
	static_assert(!std::is_reference<TargetType>::value, "Using 'Cast' to cast to a reference is not allowed");
	return Implementation::Cast<TargetType, AnyType>::Function(value);
}

// @TODO: Documentation
template <typename AnyType>
String ToString(const AnyType& value)
{
	return TypeOf<AnyType>()._toStringImplementation(&value);
}