# Core.makefile

CXX=clang++
CFLAGS=-std=c++11 -D BITS_64 -Wall
LFLAGS=-fPIC -shared
OUT=-o bin/Core.so

all: setup
	$(CXX) $(CFLAGS) source/*.cpp source/Misc/*.cpp source/Reflection/*.cpp $(LFLAGS) $(OUT)

setup:
	mkdir -p bin

clean:
	rm -rf bin
