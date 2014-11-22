// object.h
#pragma once

#include "../config.h"

namespace Willow
{
	class UTILITY_API object
	{
		////////////////////////
		///   Constructors   ///
	public:

		virtual ~object() = default;

		///////////////////
		///   Methods   ///
	public:

		/** Gets the type information for this object */
		virtual const ClassType& GetType() const = 0;

		/** Returns the state of this object as a String */
		virtual String ToString() const;
		
		/** Returns whether this object is a compatible type with the given type */
		bool IsA(const Type& type) const;

		/** Returns whether this object implements the given interface */
		bool Implements(const Type& interf) const;

		/** Returns whether this object is a compatbile type with the given type */
		template <class OtherType>
		bool IsA() const
		{
			return this->IsA(TypeInfo<OtherType>());
		}

		/** Returns whether this object implements the given interface */
		template <class UserInterface>
		bool Implements() const
		{
			return this->Implements(TypeInfo<UserInterface>());
		}

		/////////////////////
		///   Operators   ///
	public:

		virtual void operator=(const object& rhs);
	};

	/** Cast an object to another type 
	* WARNING: value must be compatible with TargetType */
	template <typename TargetType>
	TargetType& Cast(object& value)
	{
		return (TargetType&)value;
	}

	/** Casts an object to another type
	* WARNING: value must be compatible with TargetType */
	template <typename TargetType>
	const TargetType& Cast(const object& value)
	{
		return (const TargetType&)value;
	}

	/** Converts an object to another type, returning a new value, useful for primitives held as Strings
	* WARNING: value must be compatible with TargetType */
	// @TODO: This may have to be either removed or moved, to maintain compatibility with Clang
	template <typename TargetType>
	TargetType Convert(const object& value)
	{
		if (value.IsA<String>() && TypeInfo<TargetType>().IsA<PrimitiveType>())
		{
			TargetType temp;
			using Willow::ValueFromString;
			ValueFromString(Cast<String>(value), temp);
			return temp;
		}
		else
		{
			return Cast<TargetType>(value);
		}
	}

	/** Creates a new instance of UserClass
	* If your class has special initialization requirements, specialize this */
	template <class UserClass>
	struct __factory__
	{
		static object& __create__()
		{
			return *(new UserClass());
		}
	};

	/** Creates a new instance of UserClass 
	* WARNING: Returned reference must be deleted manually */
	template <class UserClass>
	object& Factory()
	{
		return __factory__<UserClass>::__create__();
	}

	/** Declares a class reflectable
	* Use in the header of any subclass of Willow::object
	* Any class that uses this macro must also use the BEGIN_CLASS_INFO and END_REFLECTION_INFO macros in its source file */
	#define REFLECTABLE												\
	private:														\
		static const Willow::ClassType& __get_type_info__();		\
	public:															\
		template <typename T> friend struct Willow::__type_info__;	\
		const Willow::ClassType& GetType() const override;			\
		void operator=(const Willow::object& rhs) override;
			
	/** Tells the reflection system what the base class of this class is
	* Use in the header of any subclass of Willow::object */
	#define EXTENDS(T)		\
	public:					\
		typedef T Super;

	/** Put at start of reflection declarations in the source file of a reflected class
	* The class must declare the REFLECTABLE macro in its header body
	* All REFLECTABLE classes must use this macro in their source file, even if they have nothing to reflect */
	#define BEGIN_CLASS_INFO(T)									\
	const Willow::ClassType& T::GetType() const					\
	{															\
		return T::__get_type_info__();							\
	}															\
	void T::operator=(const Willow::object& rhs)				\
	{															\
		This = Willow::Cast<T>(rhs);							\
	}															\
	const Willow::ClassType& T::__get_type_info__()				\
	{															\
		typedef T UserClass;									\
		static bool init = false;								\
		static auto myType = Willow::ClassType::Create<T>(#T);	\
		if (!init)												\
		{														\
			init = true;										\
			myType.SetBase<Super>();

	/** Put at start of reflection declarations in the header of a reflected template class 
	* The class must declare the REFLECTABLE macro in its header body 
	* All REFLECTABLE template classes must use this macro in their header file, even if they have nothing to reflect */
	#define BEGIN_TEMPLATE_INFO(T, ...)													\
	template <__VA_ARGS__>																\
	const Willow::ClassType& T<__VA_ARGS__>::GetType() const							\
	{																					\
		return T<__VA_ARGS__>::__get_type_info__();										\
	}																					\
	template <__VA_ARGS__>																\
	void T<__VA_ARGS__>::operator=(const Willow::object& rhs)							\
	{																					\
		This = (const T<__VA_ARGS__>&)rhs;												\
	}																					\
	template <__VA_ARGS__>																\
	const Willow::ClassType& T<__VA_ARGS__>::__get_type_info__()						\
	{																					\
		typedef T<__VA_ARGS__> UserClass;												\
		static bool init = false;														\
		static auto myType = Willow::TemplateType::Create<UserClass, __VA_ARGS__>(#T);	\
		if (!init)																		\
		{																				\
			init = true;																\
			myType.SetBase<Super>();

	/** Tells the reflection system what interfaces this class implements
	* Put between BEGIN_X_INFO and END_REFLECTION_INFO macros */
	#define IMPLEMENTS(...) ; myType.AddInterfaces<__VA_ARGS__>()

	/** Tells the reflection system that this class can be default-constructed, or has specialized the __factory__ template */
	#define HAS_FACTORY ; myType.SetFactory<UserClass>()

	/** Declares a field to be reflected
	* Put between BEGIN_X_INFO and END_REFLECTION_INFO macros */
	#define FIELD(F) ; myType.AddField(#F, &UserClass::F)

	/** Declares a property to be reflected
	* Put between BEGIN_X_INFO and END_REFLECTION_INFO macros */
	#define PROPERTY(P) ; myType.AddProperty(#P, &UserClass::Get##P, &UserClass::Set##P)

	/** Put this macro at the end of reflection declarations in the source file of a reflected class */
	#define END_REFLECTION_INFO	\
			;					\
		}						\
		return myType;			\
	}
}