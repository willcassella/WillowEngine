# WillowEngine.makefile

.PHONY: Core Math Resource ResourceConverter

setup:
	mkdir -p bin
	
clean:
	rm -rf bin
	
Core: setup
	make -C Modules/Core/ -f Core.makefile
	cp Modules/Core/bin/Core.so bin/Core.so
	
Math: Core, setup
	make -C Modules/Math/ -f Math.makefile
	cp Modules/Math/bin/Math.so bin/Math.so

Common: Core, setup
	make -C Modules/Common/ -f Common.makefile
	cp Modules/Common/bin/Common.so bin/Common.so
	
ResourceConverter: Core, Common, setup
	make -C Tools/ResourceConverter/ -f ResourceConverter.makefile
	cp Tools/ResourceConverter/bin/ResourceConverter.out bin/ResourceConverter.out