// View.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

/** View objects should ONLY be used as function arguements.
* They should NOT be stored, or passed up the stack.*/
struct View
{
	////////////////////////
	///   Constructors   ///
public:

	View() = default;
	View(const View& copy) = delete;
	View(View&& move) = default;
	~View() = default;

	/////////////////////
	///   Operators   ///
public:

	View& operator=(const View& copy) = delete;
	View& operator=(View&& move) = delete;
};
