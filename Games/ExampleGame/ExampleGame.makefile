# ExampleGame.makefile

CFLAGS=-std=c++14 -Wall -Wextra -Wpedantic -I ../../Modules/Core/include -I ../../Modules/Resource/include -I ../../Modules/Engine/include
LFLAGS=-fPIC -shared -Wl,-soname='ExampleGame.so',-rpath='$$ORIGIN'
DEPS=../../Modules/Core/bin/Core.so ../../Modules/Resource/bin/Resource.so ../../Modules/Engine/bin/Engine.so
OUT=-o bin/ExampleGame.so

.PHONY: setup

all: setup
	$(CXX) $(CFLAGS) $(OPT) `find source/ -name "*.cpp"` $(LFLAGS) $(DEPS) $(OUT)

setup:
	mkdir -p bin

clean:
	rm -rf bin
