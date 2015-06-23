# Engine.makefile

CXX=clang++
CFLAGS=-std=c++14 -Ofast -Wall -D BITS_64 -I ../Core/include -I ../Math/include
LFLAGS=-fPIC -shared -Wl,-soname='Engine.so',-rpath='$$ORIGIN'
DEPS=../Core/bin/Core.so ../Math/bin/Math.so
OUT=-o bin/Engine.so

.PHONY: setup

all: setup
	$(CXX) $(CFLAGS) source/*.cpp $(LFLAGS) $(DEPS) $(OUT)

setup:
	mkdir -p bin

clean:
	rm -rf bin
