# Resource.makefile

CFLAGS=-std=c++14 -Wall -Wextra -Wpedantic -I ../Core/include
LFLAGS=-fPIC -shared -Wl,-soname='Resource.so',-rpath='$$ORIGIN' -l freeimage
DEPS=../Core/bin/Core.so
OUT=-o bin/Resource.so

.PHONY: setup

all: setup
	$(CXX) $(CFLAGS) $(OPT) `find source/ -name "*.cpp"` $(LFLAGS) $(DEPS) $(OUT)

setup:
	mkdir -p bin

clean:
	rm -rf bin
