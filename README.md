# Willow Engine

Willow Engine is a game engine in development by Will Cassella.

## Compiling the engine

### Windows

The engine requires Visual Studio 2015 to compile on Windows, older versions of VS will not work.
Before building for the first time, you must run the 'packages.py' script in the root directory; this downloads and extracts all required Windows binaries.

Additionally, there are natvis files for various types in the engine in the "extras" directory, so you can use those to assist debugging in Visual Studio.

### Linux

The engine compiles cleanly on Clang and GCC, however you do need to install the following aptitude packages:
+ libglfw3-dev
+ libfreeimage-dev
+ libglew-dev
+ libbullet-dev

You also need the following packages, since for some reason GLFW doesn't actually download all of its dependencies:
+ xorg-dev
+ libglu1-mesa-dev

Once you have all packages installed, compiling the engine is as simple as:

`make -f WillowEngine.makefile all`

### Mac

I honestly haven't tried Mac, but it works on Linux and since all the packages are portable, I don't see why it wouldn't work on Mac as well.

## Further documentation

- [Engine Architecture](Documentation/Architecture.md)  
- [Reflection System](Documentation/Reflection.md)

Copyright 2013-2015 Will Cassella, All Rights Reserved
