# Core.makefile

CXX=clang++
CFLAGS=-std=c++11 -Ofast -Wall -D BITS_64
LFLAGS=-fPIC -shared -Wl,-soname=Core.so
OUT=-o bin/Core.so

all: setup
	$(CXX) $(CFLAGS) source/*.cpp source/Misc/*.cpp source/Reflection/*.cpp $(LFLAGS) $(OUT)

setup:
	mkdir -p bin

clean:
	rm -rf bin
