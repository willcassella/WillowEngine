# CoreTest.makefile

CFLAGS=-std=c++14 -Wall -Wextra -Wpedantic -I ../../Modules/Core/include
LFLAGS=-Wl,-rpath='$$ORIGIN'
DEPS=../../Modules/Core/bin/Core.so
OUT=-o bin/CoreTest

.PHONY: setup

all: setup
	$(CXX) $(CFLAGS) $(OPT) `find source/ -name "*.cpp"` $(LFLAGS) $(DEPS) $(OUT)

setup:
	mkdir -p bin

clean:
	rm -rf bin
