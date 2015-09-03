# Willow Engine

Willow Engine is a game engine in development by Will Cassella.
For a summary of the layout of the engine, please see "Architecture" document in the Documentation directory.

Note: While most of the engine is compilable and functional, some parts do not compile on any platforms; particularily the "GLRender" service. The rest of the engine is undergoing refactoring, and that module has not been updated to match new API.

## What works

Currently, not a whole lot. The "Client" runtime can start up and show a black screen, and while it's actually running the game behind the scenes, you can't see anything. Once the "GLRender" service is back up and running, you'll get a nice pretty picture of your game!

## Compiling the engine

### Windows

The engine requires Visual Studio 2015 to compile on Windows, older versions of VS will not work.
Before building for the first time, you must run the 'packages.py' script in the root directory; this downloads and extracts all required Windows binaries.

Additionally, there are natvis files for various types in the engine in the "extras" directory, so you can use those to assist debugging in Visual Studio.

### Linux

The engine compiles cleanly on Clang and GCC, however you do need to install the following aptitude packages:
+ libglfw3-dev
+ libfreeimage-dev

You also need the following packages, since for some reason GLFW doesn't actually download all of its dependencies:
+ xorg-dev
+ libglu1-mesa-dev

Once you have all packages installed, compiling the engine is as simple as:

`make -f WillowEngine.makefile all`

### Mac

I honestly haven't tried Mac, but it works on Linux and since all the packages are portable, I don't see why it wouldn't work on Mac as well.

Copyright 2013-2015 Will Cassella, All Rights Reserved
