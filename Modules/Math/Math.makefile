# Math.makefile

CXX=clang++
CFLAGS=-std=c++11 -Ofast -Wall -D BITS_64 -I ../Core/include
LFLAGS=-fPIC -shared -Wl,-soname=Math.so,-rpath=./
DEPS=../Core/bin/Core.so
OUT=-o bin/Math.so

all: Core setup
	$(CXX) $(CFLAGS) source/*.cpp $(LFLAGS) $(DEPS) $(OUT)

setup:
	mkdir -p bin

Core:
	make -C ../Core/ -f Core.makefile

clean:
	rm -rf bin