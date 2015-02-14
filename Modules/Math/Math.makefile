# Math.makefile

CXX=clang++
CFLAGS=-std=c++11 -D BITS_64 -Wall -I ../Core/include
LFLAGS=-fPIC -shared -Wl,-rpath,./
OUT=-o bin/Math.so

all: Core setup
	$(CXX) $(CFLAGS) source/*.cpp ../Core/bin/Core.so $(LFLAGS) $(OUT)

setup:
	mkdir -p bin

Core:
	make -C ../Core/ -f Core.makefile

clean:
	rm -rf bin