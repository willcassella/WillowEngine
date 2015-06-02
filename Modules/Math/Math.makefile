# Math.makefile

CXX=clang++
CFLAGS=-std=c++14 -Ofast -Wall -D BITS_64 -I ../Core/include
LFLAGS=-fPIC -shared -Wl,-soname='Math.so',-rpath='$$ORIGIN'
DEPS=../Core/bin/Core.so
OUT=-o bin/Math.so

.PHONY: setup

all: setup
	$(CXX) $(CFLAGS) source/*.cpp $(LFLAGS) $(DEPS) $(OUT)

setup:
	mkdir -p bin

clean:
	rm -rf bin
