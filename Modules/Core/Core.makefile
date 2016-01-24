# Core.makefile

CFLAGS=-std=c++14 -Wall -Wextra -Wpedantic -D CORE_BUILD
LFLAGS=-fPIC -shared -Wl,-soname='Core.so'
DEPS=
OUT=-o bin/Core.so

.PHONY: setup

all: setup
	$(CXX) $(CFLAGS) $(OPT) `find source/ -name "*.cpp"` $(LFLAGS) $(DEPS) $(OUT)

setup:
	mkdir -p bin

clean:
	rm -rf bin
