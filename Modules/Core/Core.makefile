# Core.makefile

CC=clang++
CFLAGS=-std=c++11 -D BITS_64 -Wall
LFLAGS=-fPIC -shared
OUT=-o bin/Core.so

all: setup
	$(CC) $(CFLAGS) source/*.cpp source/Reflection/*.cpp $(LFLAGS) $(OUT)

setup:
	mkdir -p bin

clean:
	rm -rf bin
