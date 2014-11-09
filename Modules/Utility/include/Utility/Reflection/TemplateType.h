// TemplateType.h
#pragma once

#include "ClassType.h"

namespace Willow
{
	/** Type holding information about a template type */
	class UTILITY_API TemplateType : public ClassType
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE
		EXTENDS(ClassType)

		////////////////////////
		///   Constructors   ///
	private:

		TemplateType(const String& name, const List<const Type&>& innerTypes);

	public:

		/** Registers a template class */
		template <class UserTemplate, typename ... InnerTypes>
		static TemplateType Create(const String& fullName)
		{
			TemplateType type(fullName, MultipleTypeInfo<InnerTypes...>());
			type._size = sizeof(UserTemplate);
			return type;
		}

		///////////////////
		///   Methods   ///
	public:

		/** Returns the full name (including namespace and inner types) of this template */
		String GetFullName() const override;

		/** Returns the type info for all types this template class was instantiated with */
		List<const Type&> GetInnerTypes() const;

		////////////////
		///   Data   ///
	private:

		List<const Type&> _innerTypes;
	};
}