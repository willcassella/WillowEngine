// string.h
#pragma once

#include "config.h"

namespace Willow
{
	struct CORE_API String
	{
		////////////////////////
		///   Constructors   ///
	public:

		String(const char* _value = nullptr);

		/////////////////////
		///   Operators   ///
	public:

		String& operator= (const char* rhs);
		operator const char*() const;

		////////////////
		///   Data   ///
	private:

		const char* value;
	};
}