// InterfaceType.h
#pragma once

#include "Type.h"

namespace Willow
{
	class UTILITY_API InterfaceType : public Type
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE
		EXTENDS(Type)

		////////////////////////
		///   Constructors   ///
	private:

		InterfaceType(const String& fullName);

	public:

		/** Registers a new interface */
		template <class UserInterface>
		static InterfaceType Create(const String& fullName)
		{
			InterfaceType type(fullName);
			type._size = sizeof(UserInterface);
			return type;
		}

		///////////////////
		///   Methods   ///
	public:

		/** Returns the namespace this interface was declared in */
		String GetNamespace() const;

		/** Returns the full name (including namespace) of this type */
		String GetFullName() const override;

		////////////////
		///   Data   ///
	private:

		String _namespace;
	};
}