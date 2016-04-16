# Willow Engine
[![Build status](https://ci.appveyor.com/api/projects/status/kjyfj7a0i02kdnhe?svg=true)](https://ci.appveyor.com/project/willcassella/willowengine)
[![Build Status](https://travis-ci.org/willcassella/WillowEngine.svg?branch=master)](https://travis-ci.org/willcassella/WillowEngine)

Willow Engine is a game engine in development by Will Cassella.

<img src="http://www.willcassella.net/WillowEngine/demo_screenshot.png" alt="Demo scene">

## Compiling the engine

### Windows

The engine requires Visual Studio 2015 to compile on Windows, older versions of VS will not work. To build the engine, just open the 'WillowEngine.sln' file and build all.
Note that the CMake files have not been tested on Windows, but I'm not planning on replacing my beautiful hand-crafted Visual Studio project files with ugly CMake generated ones anyway.

Additionally, there are natvis files for various types in the engine in the "extras" directory, so you can use those to assist debugging in Visual Studio.

### Linux

The engine compiles cleanly on Clang and GCC, however you do need to install the following aptitude packages:
+ libglfw3-dev
+ libfreeimage-dev
+ libpugixml-dev
+ libglew-dev
+ libbullet-dev

You also need the following packages, since for some reason GLFW doesn't actually download all of its dependencies:
+ xorg-dev
+ libglu1-mesa-dev

Once you have all packages installed, compiling the engine is as simple as:

`mkdir build`  
`cd build`  
`cmake ../`  
`make`  

### Mac

Mac is not officially supported, but I don't see any reason why it wouldn't work, assuming you set up the packages (which are all portable) correctly.
If I eventually get a Mac I'll add support for it in the CMake files.

## Further documentation

- [Project Structure](Documentation/ProjectStructure.md)  
- [Reflection System](Documentation/Reflection.md)

Copyright 2013-2016 Will Cassella, All Rights Reserved
