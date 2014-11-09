// PrimitiveType.h
#pragma once

#include "Type.h"

namespace Willow
{
	/** Type holding information about primitive types */
	class UTILITY_API PrimitiveType : public Type
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE
		EXTENDS(Type)

		////////////////////////
		///   Constructors   ///
	protected:

		PrimitiveType(const String& name);

	public:

		/** Registers a primitive type */
		template <typename UserType>
		static PrimitiveType Create(const String& fullName)
		{
			PrimitiveType type(fullName);
			type._size = sizeof(UserType);
			return type;
		}

		///////////////////
		///   Methods   ///
	public:

		/** Returns the full name of this primitive */
		String GetFullName() const override;
	};

	/** TypeInfo specialization for primitive classes */
	#define PRIMITIVE(T)												\
	template <>															\
	class Willow::__type_info__<T>										\
	{																	\
	public:																\
		static const Willow::Type& __get_type_info__()					\
		{																\
			static auto myType = Willow::PrimitiveType::Create<T>(#T);	\
			return myType;												\
		}																\
	};

	PRIMITIVE(bool)
	PRIMITIVE(char)
	PRIMITIVE(byte)
	PRIMITIVE(int16)
	PRIMITIVE(int32)
	PRIMITIVE(int64)
	PRIMITIVE(ubyte)
	PRIMITIVE(uint16)
	PRIMITIVE(uint32)
	PRIMITIVE(uint64)
	PRIMITIVE(float)
	PRIMITIVE(double)
}