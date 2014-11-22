//  Module.h
#pragma once

#include "Reflection.h"

namespace Willow
{
	class UTILITY_API Module
	{
		///////////////////
		///   Methods   ///
	public:

		List<const Type&> GetTypes() const;

		////////////////
		///   Data   ///
	private:

		List<const Type&> _types;
	};
}