# ResourceConverter.makefile

CXX=clang++
CFLAGS=-std=c++11 -Ofast -Wall -D BITS_64 -I ../../Modules/Core/include -I ../../Modules/Common/include
LFLAGS=-Wl,-rpath='$$ORIGIN'
DEPS=../../Modules/Core/bin/Core.so ../../Modules/Common/bin/Common.so
OUT=-o bin/ResourceConverter.out

.PHONY: setup

all: setup
	$(CXX) $(CFLAGS) Source/*.cpp $(LFLAGS) $(DEPS) $(OUT)

setup:
	mkdir -p bin

clean:
	rm -rf bin
