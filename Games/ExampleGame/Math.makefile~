# ExampleGame.makefile

CXX=clang++
CFLAGS=-std=c++14 -Ofast -Wall -D BITS_64 -I ../../Modules/Core/include -I ../../Modules/Math/include -I ../../Modules/Engine/include
LFLAGS=-fPIC -shared -Wl,-soname='ExampleGame.so',-rpath='$$ORIGIN'
DEPS=../../Modules/Core/bin/Core.so ../../Modules/Math/bin/Math.so ../../Modules/Engine/bin/Engine.so
OUT=-o bin/ExampleGame.so

.PHONY: setup

all: setup
	$(CXX) $(CFLAGS) source/*.cpp $(LFLAGS) $(DEPS) $(OUT)

setup:
	mkdir -p bin

clean:
	rm -rf bin
