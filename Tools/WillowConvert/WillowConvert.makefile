# WillowConvert.makefile

CXX=clang++
CFLAGS=-std=c++11 -Ofast -Wall -D BITS_64 -I ../../Modules/Core/include -I ../../Modules/Resource/include
LFLAGS=-Wl,-rpath=./
OUT=-o bin/WillowConvert.out

all: Resource setup
	$(CXX) $(CFLAGS) Source/*.cpp ../../Modules/Core/bin/Core.so ../../Modules/Resource/bin/Resource.so  $(LFLAGS) $(OUT)

Resource:
	make -C ../../Modules/Resource -f Resource.makefile

setup:
	mkdir -p bin

clean:
	rm -rf bin
