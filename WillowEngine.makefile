# WillowEngine.makefile

### Variables ###
CXX=clang++	# C++ Compiler to use
OPT=-Ofast	# Optimization seting to use

export

### Targets ###

.PHONY: setup clean all

setup:
	mkdir -p bin
	
clean:
	rm -rf bin
	
all: Core Resource Engine GLRender ExampleGame CoreTest AssetConverter Client
	echo "Build complete"

# Modules

Core: setup
	make -C Modules/Core/ -f Core.makefile
	cp Modules/Core/bin/Core.so bin/

Resource: setup
	make -C Modules/Resource/ -f Resource.makefile
	cp Modules/Resource/bin/Resource.so bin/
	
Engine: setup
	make -C Modules/Engine/ -f Engine.makefile
	cp Modules/Engine/bin/Engine.so bin/
	
# Services

GLRender: setup
	make -C Services/GLRender/ -f GLRender.makefile
	cp Services/GLRender/bin/GLRender.so bin/
	
# Runtimes

Client : setup
	make -C Runtimes/Client/ -f Client.makefile
	cp Runtimes/Client/bin/Client bin/
	
# Games

ExampleGame: setup
	make -C Games/ExampleGame/ -f ExampleGame.makefile
	cp Games/ExampleGame/bin/ExampleGame.so bin/
	
# Tools
	
AssetConverter: setup
	make -C Tools/AssetConverter/ -f AssetConverter.makefile
	cp Tools/AssetConverter/bin/AssetConverter bin/

# Tests

CoreTest : setup
	make -C Tests/CoreTest/ -f CoreTest.makefile
	cp Tests/CoreTest/bin/CoreTest bin/
