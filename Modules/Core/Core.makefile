# Core.makefile

CXX=clang++
CFLAGS=-std=c++14 -Ofast -Wall -Wextra -D BITS_64
LFLAGS=-fPIC -shared -Wl,-soname='Core.so'
DEPS=
OUT=-o bin/Core.so

.PHONY: setup

all: setup
	$(CXX) $(CFLAGS) source/*.cpp source/Containers/*.cpp source/Event/*.cpp source/Math/*.cpp source/Memory/*.cpp source/Misc/*.cpp source/Operations/*.cpp source/Reflection/*.cpp $(LFLAGS) $(DEPS) $(OUT)

setup:
	mkdir -p bin

clean:
	rm -rf bin
