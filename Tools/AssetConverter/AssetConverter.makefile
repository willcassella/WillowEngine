# AssetConverter.makefile

CFLAGS=-std=c++14 -Wall -Wextra -Wpedantic -I ../../Modules/Core/include -I ../../Modules/Resource/include -I ../../Modules/Engine/include
LFLAGS=-Wl,-rpath='$$ORIGIN'
DEPS=../../Modules/Core/bin/Core.so ../../Modules/Resource/bin/Resource.so ../../Modules/Engine/bin/Engine.so
OUT=-o bin/AssetConverter

.PHONY: setup

all: setup
	$(CXX) $(CFLAGS) $(OPT) `find source/ -name "*.cpp"` $(LFLAGS) $(DEPS) $(OUT)

setup:
	mkdir -p bin

clean:
	rm -rf bin
