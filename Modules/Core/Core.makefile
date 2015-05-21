# Core.makefile

CXX=clang++
CFLAGS=-std=c++14 -Ofast -Wall -D BITS_64
LFLAGS=-fPIC -shared -Wl,-soname='Core.so'
DEPS=
OUT=-o bin/Core.so

.PHONY: setup

all: setup
	$(CXX) $(CFLAGS) source/*.cpp source/Misc/*.cpp source/Reflection/*.cpp source/Operations/*.cpp $(LFLAGS) $(DEPS) $(OUT)

setup:
	mkdir -p bin

clean:
	rm -rf bin
