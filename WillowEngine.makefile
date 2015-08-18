# WillowEngine.makefile

.PHONY: Core Resource ResourceConverter

setup:
	mkdir -p bin
	
clean:
	rm -rf bin

# Modules

Core: setup
	make -C Modules/Core/ -f Core.makefile
	cp Modules/Core/bin/Core.so bin/Core.so

Resource: setup
	make -C Modules/Resource/ -f Resource.makefile
	cp Modules/Resource/bin/Resource.so bin/Resource.so
	
Engine: setup
	make -C Modules/Engine/ -f Engine.makefile
	cp Modules/Engine/bin/Engine.so bin/Engine.so
	
# Games

ExampleGame: setup
	make -C Games/ExampleGame/ -f ExampleGame.makefile
	cp Games/ExampleGame/bin/ExampleGame.so bin/ExampleGame.so
	
# Tools
	
AssetConverter: setup
	make -C Tools/AssetConverter/ -f AssetConverter.makefile
	cp Tools/AssetConverter/bin/AssetConverter.out bin/AssetConverter.out

# Tests

CoreTest : setup
	make -C Tests/CoreTest/ -f CoreTest.makefile
	cp Tests/CoreTest/bin/CoreTest.out bin/CoreTest.out
