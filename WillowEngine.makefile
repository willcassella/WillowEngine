# WillowEngine.makefile

.PHONY: Core Math Resource WillowConvert

setup:
	mkdir -p bin
	
clean:
	rm -rf bin
	
Core: setup
	make -C Modules/Core/ -f Core.makefile
	cp Modules/Core/bin/Core.so bin/Core.so
	
Math: setup
	make -C Modules/Core/ -f Core.makefile
	cp Modules/Core/bin/Core.so bin/Core.so
	make -C Modules/Math/ -f Math.makefile
	cp Modules/Math/bin/Math.so bin/Math.so
	
Resource: setup
	make -C Modules/Core/ -f Core.makefile
	cp Modules/Core/Core.so bin/Core.so
	make -C Modules/Resource/ -f Resource.makefile
	cp Modules/Resource/bin/Resource.so bin/Resource.so
	
WillowConvert: setup
	make -C Modules/Core/ -f Core.makefile
	cp Modules/Core/bin/Core.so bin/Core.so
	make -C Modules/Resource/ -f Resource.makefile
	cp Modules/Resource/bin/Resource.so bin/Resource.so
	make -C Tools/WillowConvert/ -f WillowConvert.makefile
	cp Tools/WillowConvert/bin/WillowConvert.out bin/WillowConvert.out