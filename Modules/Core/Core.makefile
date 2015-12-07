# Core.makefile

CXX=clang++
CFLAGS=-std=c++14 -Ofast -Wall -Wextra -Wpedantic
LFLAGS=-fPIC -shared -Wl,-soname='Core.so'
DEPS=
OUT=-o bin/Core.so

.PHONY: setup

all: setup
	$(CXX) $(CFLAGS) `find source/ -name "*.cpp"` $(LFLAGS) $(DEPS) $(OUT)

setup:
	mkdir -p bin

clean:
	rm -rf bin
