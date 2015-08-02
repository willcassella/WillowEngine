# WillowEngine.makefile

.PHONY: Core Resource ResourceConverter

setup:
	mkdir -p bin
	
clean:
	rm -rf bin
	
Core: setup
	make -C Modules/Core/ -f Core.makefile
	cp Modules/Core/bin/Core.so bin/Core.so

Resource: Core setup
	make -C Modules/Resource/ -f Resource.makefile
	cp Modules/Resource/bin/Resource.so bin/Resource.so
	
ResourceConverter: Core Resource setup
	make -C Tools/ResourceConverter/ -f ResourceConverter.makefile
	cp Tools/ResourceConverter/bin/ResourceConverter.out bin/ResourceConverter.out

CoreTest : Core setup
	make -C Tests/CoreTest/ -f CoreTest.makefile
	cp Tests/CoreTest/bin/CoreTest.out bin/CoreTest.out
