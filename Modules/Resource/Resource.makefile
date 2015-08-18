# Resource.makefile

CXX=clang++
CFLAGS=-std=c++14 -Ofast -Wall -Wextra -Wpedantic -D BITS_64 -I ../Core/include
LFLAGS=-fPIC -shared -Wl,-soname='Resource.so',-rpath='$$ORIGIN' -l freeimage
DEPS=../Core/bin/Core.so
OUT=-o bin/Resource.so

.PHONY: setup

all: setup
	$(CXX) $(CFLAGS) `find source/ -name "*.cpp"` $(LFLAGS) $(DEPS) $(OUT)

setup:
	mkdir -p bin

clean:
	rm -rf bin
