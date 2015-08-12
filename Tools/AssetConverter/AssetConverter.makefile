# AssetConverter.makefile

CXX=clang++
CFLAGS=-std=c++11 -Ofast -Wall -D BITS_64 -I ../../Modules/Core/include -I ../../Modules/Resource/include -I ../../Modules/Engine/include
LFLAGS=-Wl,-rpath='$$ORIGIN'
DEPS=../../Modules/Core/bin/Core.so ../../Modules/Resource/bin/Resource.so ../../Modules/Engine/bin/Engine.so
OUT=-o bin/AssetConverter.out

.PHONY: setup

all: setup
	$(CXX) $(CFLAGS) Source/*.cpp $(LFLAGS) $(DEPS) $(OUT)

setup:
	mkdir -p bin

clean:
	rm -rf bin
