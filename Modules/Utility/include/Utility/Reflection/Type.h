// Type.h
#pragma once

#include "..\String.h"
#include "..\List.h"
#include "..\Pair.h"

namespace Willow
{
	/** Abstract base class for type reflection info */
	class UTILITY_API Type : public object
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE
		EXTENDS(object)

		///////////////////
		///   Methods   ///
	public:

		/** Returns the state of this Type as a String */
		String ToString() const override;

		/** Returns the name of this type (without namespace) */
		String GetName() const;

		/** Returns the full name (including namespace, if it has one) of this type */
		virtual String GetFullName() const = 0;

		/** Returns the size of this class */
		uint32 GetSize() const;

		/////////////////////
		///   Operators   ///
	public:

		friend UTILITY_API bool operator==(const Type& lhs, const Type& rhs);
		inline friend UTILITY_API bool operator!=(const Type& lhs, const Type& rhs)
		{
			return !(lhs == rhs);
		}

		////////////////
		///   Data   ///
	protected:

		String _name;
		uint32 _size;
	};

	/** Returns the type information fot the given type (overrideable) */
	template <typename UserType>
	struct __type_info__
	{
		static const Type& __get_type_info__()
		{
			return UserType::__get_type_info__();
		}
	};

	/** Returns the Type information for the given type */
	template <typename T>
	const Type& TypeInfo()
	{
		return __type_info__<T>::__get_type_info__();
	}

	/* Implementation template, please use MultipleTypeInfo<...>() instead */
	template <typename FirstType = void, typename ... RestTypes>
	struct __multiple_type_info__
	{
		static List<const Type&> GetTypes()
		{
			List<const Type&> types;
			types.Add(TypeInfo<FirstType>());
			return types + __multiple_type_info__<RestTypes...>::GetTypes();
		}
	};

	/* Implementation template, please use MultipleTypeInfo<...>() instead */
	template <>
	struct __multiple_type_info__<void>
	{
		static List<const Type&> GetTypes()
		{
			return List<const Type&>();
		}
	};

	/** Creates a list of Types from all given types, useful for template type inner class gathering */
	template <typename ... Types>
	List<const Type&> MultipleTypeInfo()
	{
		return __multiple_type_info__<Types...>::GetTypes();
	}
}