# Client.makefile

CXX=clang++
CFLAGS=-std=c++14 -Ofast -Wall -Wextra -Wpedantic -D BITS_64 -I ../../Modules/Core/include -I ../../Modules/Resource/include -I ../../Modules/Engine/include -I ../../Services/GLRender/include -I ../../Games/ExampleGame/include `pkg-config glfw3 --cflags`
LFLAGS=-Wl,-rpath='$$ORIGIN' `pkg-config glfw3 --libs`
DEPS=../../Modules/Core/bin/Core.so ../../Modules/Resource/bin/Resource.so ../../Modules/Engine/bin/Engine.so ../../Services/GLRender/bin/GLRender.so ../../Games/ExampleGame/bin/ExampleGame.so
OUT=-o bin/Client

.PHONY: setup

all: setup
	$(CXX) $(CFLAGS) `find source/ -name "*.cpp"` $(LFLAGS) $(DEPS) $(OUT)

setup:
	mkdir -p bin

clean:
	rm -rf bin
