# Resource.makefile

CXX=clang++
CFLAGS=-std=c++11 -Ofast -Wall -D BITS_64 -I ../Core/include
LFLAGS=-fPIC -shared -Wl,-soname=Resource.so,-rpath=./ -l freeimage
OUT=-o bin/Resource.so

all: Core setup
	$(CXX) $(CFLAGS) source/*.cpp ../Core/bin/Core.so $(LFLAGS) $(OUT)

setup:
	mkdir -p bin

Core:
	make -C ../Core/ -f Core.makefile

clean:
	rm -rf bin
