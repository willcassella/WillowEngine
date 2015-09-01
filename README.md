
Willow Engine is a game engine in development by Will Cassella.
For a summary of the layout of the engine, please see "Architecture.txt" in the Documentation directory.

Note: While most of the engine is compilable and functional, some parts do not compile on any platforms; particularily the "GLRender" service. The rest of the engine is undergoing refactoring, and that module has not been updated to match new API.

Also, everything other than "Core" and "Resource" currently does not compile on Windows, due to some fuckery with the NuGet packages I was using. I'm going to fix that once I find a permanent solution: either uploading my own packages, or using a custom build system.

Copyright 2013-2015 Will Cassella, All Rights Reserved
