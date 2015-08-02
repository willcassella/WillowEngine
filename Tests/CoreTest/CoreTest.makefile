# CoreTest.makefile

CXX=clang++
CFLAGS=-std=c++14 -Ofast -Wall -Wextra -D BITS_64 -I ../../Modules/Core/include
LFLAGS=-Wl,-rpath='$$ORIGIN'
DEPS=../../Modules/Core/bin/Core.so
OUT=-o bin/CoreTest.out

.PHONY: setup

all: setup
	$(CXX) $(CFLAGS) source/*.cpp $(LFLAGS) $(DEPS) $(OUT)

setup:
	mkdir -p bin

clean:
	rm -rf bin
