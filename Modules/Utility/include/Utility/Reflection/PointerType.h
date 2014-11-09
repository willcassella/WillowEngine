// PointerType.h
#pragma once

#include "PrimitiveType.h"

namespace Willow
{
	/** Type holding information about pointers to other types */
	class UTILITY_API PointerType : public PrimitiveType
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE
		EXTENDS(PrimitiveType)

		////////////////////////
		///   Constructors   ///
	private:

		PointerType(const Type& pointedType);

	public:

		/** Registers a pointer type */
		template <typename UserType>
		static PointerType Create()
		{
			PointerType type(TypeInfo<UserType>());
			type._size = sizeof(UserType*);
			return type;
		}

		///////////////////
		///   Methods   ///
	public:

		/** Returns the type information for the type pointed to by this pointer */
		const Type& GetPointedType() const;

		////////////////
		///   Data   ///
	private:

		const Type* _pointedType;
	};

	/** TypeInfo Specialization for pointer types */
	template <typename UserType>
	struct __type_info__<UserType*>
	{
		static const Type& __get_type_info__()
		{
			static auto myType = PointerType::Create<UserType>();
			return myType;
		}
	};

	// @TODO: Should this be its own type?
	/** Specialziation for reference types */
	template <typename UserType>
	struct __type_info__<UserType&>
	{
		static const Type& __get_type_info__()
		{
			static auto myType = PointerType::Create<UserType>();
			return myType;
		}
	};
}