// NonReflectedType.h
#pragma once

#include "Type.h"

namespace Willow
{
	/** Type holding information about a type that is not reflected */
	class UTILITY_API NonReflectedType : public Type
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE
		EXTENDS(Type)

		////////////////////////
		///   Constructors   ///
	protected:

		NonReflectedType(const String& fullName);

	public:

		/** Registers a type that is not reflected (may be primitive or class) */
		template <typename UserType>
		static NonReflectedType Create(const String& fullName)
		{
			NonReflectedType type(fullName);
			type._size = sizeof(UserType);
			return type;
		}

		///////////////////
		///   Methods   ///
	public:

		/** Returns the namespace this type was declared in */
		String GetNamespace() const;

		/** Returns the full name (including namespace) of this type */
		String GetFullName() const override;

		////////////////
		///   Data   ///
	private:

		String _namespace;
	};

	/** TypeInfo specialization for non-reflected classes */
	#define NON_REFLECTABLE(T)												\
	template <>																\
	struct Willow::__type_info__<T>											\
	{																		\
		static const Willow::Type& __get_type_info__()						\
		{																	\
			static auto myType = Willow::NonReflectedType::Create<T>(#T);	\
			return myType;													\
		}																	\
	};
}