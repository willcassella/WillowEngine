# Resource.makefile

CC=clang++
CFLAGS=-std=c++11 -D BITS_64 -Wall -I ../Core/include
LFLAGS=-fPIC -shared -Wl,-rpath,./ -l freeimage
OUT=-o bin/Resource.so

all: Core setup
	$(CC) $(CFLAGS) source/*.cpp ../Core/bin/Core.so $(LFLAGS) $(OUT)

setup:
	mkdir -p bin

Core:
	make -C ../Core/ -f Core.makefile

clean:
	rm -rf bin
