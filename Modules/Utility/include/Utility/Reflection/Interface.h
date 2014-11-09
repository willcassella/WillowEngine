// Interface.h
#pragma once

#include "..\config.h"

namespace Willow
{
	/** Base class for interfaces */
	class UTILITY_API Interface
	{
		////////////////////////
		///   Constructors   ///
	public:

		virtual ~Interface() = default;
	};

	/** Declares this interface as reflectable */
	#define REFLECTABLE_INTERFACE										\
	private:															\
		static const inline Willow::InterfaceType& __get_type_info__();	\
	public:																\
		template <typename T> friend struct Willow::__type_info__;

	/** Defines the reflection information for an interface
	WARNING: This must exist in the interface's header */
	#define BEGIN_INTERFACE_INFO(T)									\
	const Willow::InterfaceType& T::__get_type_info__()				\
	{																\
		static bool init = false;									\
		static auto myType = Willow::InterfaceType::Create<T>(#T);	\
		if (!init)													\
		{															\
			init = true;
}