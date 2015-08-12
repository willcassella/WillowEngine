# Engine.makefile

CXX=clang++
CFLAGS=-std=c++14 -Ofast -Wall -D BITS_64 -I ../Core/include -I ../Resource/include
LFLAGS=-fPIC -shared -Wl,-soname='Engine.so',-rpath='$$ORIGIN'
DEPS=../Core/bin/Core.so ../Resource/bin/Math.so
OUT=-o bin/Engine.so

.PHONY: setup

all: setup
	$(CXX) $(CFLAGS) source/*.cpp source/Asset/*.cpp source/Components/*.cpp source/GameObjects/*.cpp $(LFLAGS) $(DEPS) $(OUT)

setup:
	mkdir -p bin

clean:
	rm -rf bin
