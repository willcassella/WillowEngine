
Willow Engine is a game engine in development by Will Cassella.
For a summary of the layout of the engine, please see "Architecture.txt" in the Documentation directory.

Note: While most of the engine is compilable and functional, some parts do not compile on any platforms; particularily the "GLRender" service. The rest of the engine is undergoing refactoring, and that module has not been updated to match new API.

# Building

## Windows

Currently the engine requires Visual Studio 2015 to compile on Windows.
Before building for the first time, you must run the 'packages.py' script in the root directory. This pulls all required Windows binaries into the directory.

## Linux

The engine compiles cleanly on Clang and GCC, however you do need to install the following aptitude packages:
+ libglfw3-dev
+ libfreeimage-dev
+ libglew-dev

# Mac

I honestly haven't tried Mac, but it works on Linux and since all the packages are portable, I don't see why it wouldn't work on mac as well.

Copyright 2013-2015 Will Cassella, All Rights Reserved
