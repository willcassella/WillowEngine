# WillowConvert.makefile

CXX=clang++
CFLAGS=-std=c++11 -Ofast -Wall -D BITS_64 -I ../../Modules/Core/include -I ../../Modules/Resource/include
LFLAGS=-Wl,-rpath=./
DEPS=../../Modules/Core/bin/Core.so ../../Modules/Resource/bin/Resource.so
OUT=-o bin/WillowConvert.out

all: Resource setup
	$(CXX) $(CFLAGS) Source/*.cpp $(LFLAGS) $(DEPS) $(OUT)

Resource:
	make -C ../../Modules/Resource -f Resource.makefile

setup:
	mkdir -p bin

clean:
	rm -rf bin