// IEventDispatcher.h
#pragma once

#include "config.h"

namespace Willow
{
	interface IEventDispatcher : public Interface
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_INTERFACE

		///////////////////
		///   Methods   ///
	public:

		virtual void Dispatch(float value) const = 0;
	};

	BEGIN_INTERFACE_INFO(Willow::IEventDispatcher)
	END_REFLECTION_INFO
}