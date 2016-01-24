# Engine.makefile

CFLAGS=-std=c++14 -Wall -Wextra -Wpedantic -I ../Core/include -I ../Resource/include `pkg-config --cflags bullet` -D ENGINE_BUILD
LFLAGS=-fPIC -shared -Wl,-soname='Engine.so',-rpath='$$ORIGIN' `pkg-config --libs --static bullet`
DEPS=../Core/bin/Core.so ../Resource/bin/Resource.so
OUT=-o bin/Engine.so

.PHONY: setup

all: setup
	$(CXX) $(CFLAGS) $(OPT) `find source/ -name "*.cpp"` $(LFLAGS) $(DEPS) $(OUT)

setup:
	mkdir -p bin

clean:
	rm -rf bin
