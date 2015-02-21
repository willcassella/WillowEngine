# Resource.makefile

CXX=clang++
CFLAGS=-std=c++11 -Ofast -Wall -D BITS_64 -I ../Core/include
LFLAGS=-fPIC -shared -Wl,-soname='Resource.so',-rpath='$$ORIGIN' -l freeimage
DEPS=../Core/bin/Core.so
OUT=-o bin/Resource.so

.PHONY: Core setup

all: Core setup
	$(CXX) $(CFLAGS) source/*.cpp $(LFLAGS) $(DEPS) $(OUT)

Core:
	make -C ../Core/ -f Core.makefile

setup:
	mkdir -p bin

clean:
	rm -rf bin