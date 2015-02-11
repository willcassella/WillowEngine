// TypeInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

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

	////////////////////////
	///   Constructors   ///
public:

	TypeInfo(const TypeInfo& copy) = delete;
	TypeInfo(TypeInfo&& move);
	~TypeInfo() override;

protected:

	TypeInfo(uint32 size, const String& name);

	///////////////////
	///   Methods   ///
public:

	/** Returns the static size of this type */
	uint32 GetSize() const;

	/** Returns the name of this type */
	virtual String GetName() const;

	/** Returns whether this type is abstract
	* i.e - it has at least one pure virtual function */
	virtual bool IsAbstract() const = 0;

	/** Returns whether this type is polymorphic
	* i.e - it is a class or interface (has virtual functions) */
	virtual bool IsPolymorphic() const = 0;

	/** Returns whether this type is instantiable via 'Instantiate()' */
	virtual bool IsInstantiable() const = 0;

	/** Returns whether this type is castable (via 'reinterpret_cast') to the given type */
	virtual bool IsCastableTo(const TypeInfo& type) const = 0;

	/** Returns an instance of this type, allocated on the stack
	* WARNING: Returns a null Value if this type is not instantiable (check 'IsInstantiable()') */
	virtual Value StackInstance() const = 0;

	/** Returns a Reference to an instance of this type, allocated on the heap
	* WARNING: Callee has ownership over the lifetime of returned value (it must be deleted manually)
	* WARNING: Returns a null Reference if this type is not instantiable (check 'IsIntantiable()') */
	virtual Reference HeapInstance() const = 0;
		
	/** Returns whether this type is castable (via 'reinterpret_cast') to the given type */
	template <typename AnyType>
	inline bool IsCastableTo() const
	{
		return IsCastableTo(TypeOf<AnyType>());
	}

	/////////////////////
	///   Operators   ///
public:

	TypeInfo& operator=(const TypeInfo& copy) = delete;
	TypeInfo& operator=(TypeInfo&& move) = delete;
	friend inline CORE_API bool operator==(const TypeInfo& lhs, const TypeInfo& rhs)
	{
		return lhs._name == rhs._name;
	}
	friend inline CORE_API bool operator!=(const TypeInfo& lhs, const TypeInfo& rhs)
	{
		return lhs._name != rhs._name;
	}

	////////////////
	///   Data   ///
protected:

	uint32 _size;
	String _name;
};

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Default implementation of Cast */
	template <typename TargetType, typename AnyType>
	struct Cast
	{
		/** Attempt to cast reference */
		inline static TargetType* Function(AnyType& value)
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

		/** Attempt to cast immutable reference */
		inline static const TargetType* Function(const AnyType& value)
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

	/** Casting to references */
	template <typename TargetType, typename AnyType>
	struct Cast < TargetType&, AnyType >
	{
		// No casting to references!
	};
}

/////////////////////
///   Functions   ///

/** Safely casts from a reference of one type to the target class/interface/type
* WARNING: Returns 'nullptr' if the cast is invalid (value does not legally translate to the given type)
* DO NOT OVERLOAD: Specialize struct 'Implementation::Cast' */
template <typename TargetType, typename AnyType>
inline TargetType* Cast(AnyType& value)
{
	return Implementation::Cast<TargetType, AnyType>::Function(value);
}

/** Safely casts from an immutable reference of one type to the target class/interface/type
* WARNING: Returns 'nullptr' if the cast is invalid (value does not legally translate to the given type)
* DO NOT OVERLOAD: Specialize struct 'Implementation::Cast' */
template <typename TargetType, typename AnyType>
inline const TargetType* Cast(const AnyType& value)
{
	return Implementation::Cast<TargetType, AnyType>::Function(value);
}