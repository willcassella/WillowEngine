# Project Structure

The engine is currently divided into several major bits: "Modules", "Systems", "Runtimes", "Games", "Tools", and "Tests".

## Modules and Systems

The distinction between Modules and Systems is mostly semantic. Modules are key parts of the engine that it simply couldn't function without, while Systems are external services that provide features that are considered extraneous to the core behavior of the engine (a container of Enties and Components). While the engine may be severely gimped without some systems, it still can exist without them.

### Core module

This module contains low-level types and features of the engine that everything else is built upon. It is written in such a way that it could easily be extracted and used in other applications that are not related to game engines. It's basically a replacement/extension of the C++ standard library. At the moment this module contains the vast majority of code in the engine.

### Resource module

This module defines the interface for loading and accessing generic resources and assets from the file system, as well as some specific resource types. This module is still agnostic of any game engine specific behavior, though it is specifically designed for use within a game engine.

### Engine module

This module defines the classes and functions that make up the meat of the game engine itself. While this module acknowledges the existance of services such as rendering, it does not implement any actual rendering behavior or interact with the renderer directly.

### GLRender system

This system observes the current state of the game world and draws it to the screen, implemented in OpenGL. The engine for the most part does not interact with the renderer, other than supplying it all necessary rendering data.

### BulletPhysics system

This system is responsible for simulating physics in the game world via the Bullet 2 library. At the moment this system is less seperated from the engine then I would like, but deadlines are deadlines.

## Runtimes

"Runtimes" are executable modules that are responsible for starting up the engine for a specific platform or use.

## Games

"Games" are modules where game-specific behavior is written, and are loaded dynamically at runtime. The only existing project is "ExampleGame", which is pretty minimal.

## Tools

"Tools" are similar to runtimes in that they are executable programs that are built on top of the engine, but they are generally just minimal tools for tasks that shouldn't be a part of the main engine. Currently the only instance of this is "AssetConverter", which is responsible for converting various asset formats into formats that are consumable by the engine. While it is an executable program, it is written in such a way that it would be trivial to turn it into a library.

## Tests

"Test" are tests, and they generally don't do a whole lot. They're basically just scratch programs for testing various features when I want to, but they don't have any real code-coverage.
