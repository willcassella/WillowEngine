The engine is currently divided into several major bits: "Modules", "Services", "Runtimes", "Games", "Tools", and "Tests".

## Modules and Services

The distinction between Modules and Services is mostly semantic. Modules are key parts of the engine that basically nothing could function without, while Services are external ... services that provide features that are considered extraneous to the core behavior of the engine. Basically any engine feature that isn't actually needed to successfully simulate the game world is broken off as a Service. At the moment that only includes "GLRender", as rendering is not considered something necessary to successfully simulate the game. In the future services will include Audio, debugging and profiling tools, and other extensions to the engine.

## Runtimes

"Runtimes" are executable modules that are responsible for starting up the engine for a specific platform or use. At the moment that only includes "Client", but in the future it will include "Server", and "Editor", among others.

## Games

"Games" are modules where game-specific behavior is written, and are loaded dynamically at runtime. The only existing project is "ExampleGame", which is pretty minimal.

## Tools

"Tools" are similar to runtimes in that they are executable programs that are built on top of the engine, but they are generally just minimal tools for tasks that shouldn't be a part of the main engine. Currently the only instance of this is "AssetConverter", which is responsible for converting various asset formats into formats that are consumable by the engine. While it is an executable program, it is written in such a way that it would be trivial to turn it into a library.

## Tests

"Test" are tests, and they generally don't do a whole lot. They're basically just scratch programs for testing various features when I want to, but they don't have any real code-coverage.
