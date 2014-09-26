// IEventDispatcher.h
#pragma once

#include "config.h"

namespace Willow
{
	interface IEventDispatcher
	{
		////////////////////////
		///   Constructors   ///
	public:

		virtual ~IEventDispatcher() = default;

		///////////////////
		///   Methods   ///
	public:

		virtual void Dispatch(float value) const = 0;
	};
}