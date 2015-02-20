# Resource.makefile

CXX=clang++
CFLAGS=-std=c++11 -Ofast -Wall -D BITS_64 -I ../Core/include
LFLAGS=-fPIC -shared -Wl,-soname=Resource.so,-rpath=./ -l freeimage
DEPS=../Core/bin/Core.so
OUT=-o bin/Resource.so

all: Core setup
	$(CXX) $(CFLAGS) source/*.cpp $(LFLAGS) $(DEPS) $(OUT)

setup:
	mkdir -p bin

Core:
	make -C ../Core/ -f Core.makefile

clean:
	rm -rf bin