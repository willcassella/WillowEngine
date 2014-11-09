// TemplateType.cpp

#include "..\..\include\Utility\Reflection\Reflection.h"
using namespace Willow;

//////////////////////
///   Reflection   ///

BEGIN_CLASS_INFO(Willow::TemplateType)
END_REFLECTION_INFO

////////////////////////
///   Constructors   ///

TemplateType::TemplateType(const String& fullName, const List<const Type&>& innerTypes)
	: Super(fullName), _innerTypes(innerTypes)
{
	// All done
}

///////////////////
///   Methods   ///

String TemplateType::GetFullName() const
{
	String str = Super::GetFullName() + "<";
	bool fence = false;
	for (const auto& type : _innerTypes)
	{
		if (fence)
		{
			str += ", ";
		}
		else
		{
			fence = true;
		}

		str += type.GetFullName();
	}

	return str + ">";
}

List<const Type&> TemplateType::GetInnerTypes() const
{
	return _innerTypes;
}