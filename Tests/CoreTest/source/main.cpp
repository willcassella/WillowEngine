// main.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Core/Core.h>

void PrintProperties(ImmutableVariant v)
{
	Console::Write("@: ", v.GetType());

	if (auto pType = Cast<CompoundInfo>(v.GetType()))
	{
		Console::NewLine();
		for (const auto& propInfo : pType->GetProperties())
		{
			Console::WriteLine("@ (@) : @", propInfo.GetName(), propInfo.GetPropertyType(), propInfo.Get(v));
		}
	}
	else
	{
		Console::Write(v);
	}
}

void PrintValues(const EnumInfo& info)
{
	Console::WriteLine(info.GetValues());
}

int main()
{
	PrintProperties(TypeOf<ClassInfo>());
	Console::NewLine();
	PrintValues(TypeOf<PropertyAccess>());
	Console::NewLine();
	PrintValues(TypeOf<PropertyFlags>());
	Console::Prompt();
}
