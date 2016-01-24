# GLRender.makefile

CFLAGS=-std=c++14 -Wall -Wextra -Wpedantic -I ../../Modules/Core/include -I ../../Modules/Resource/include -I ../../Modules/Engine/include `pkg-config glew --cflags` -D GLRENDER_BUILD
LFLAGS=-fPIC -shared -Wl,-soname='GLRender.so',-rpath='$$ORIGIN' `pkg-config glew --libs --static`
DEPS=../../Modules/Core/bin/Core.so ../../Modules/Resource/bin/Resource.so ../../Modules/Engine/bin/Engine.so
OUT=-o bin/GLRender.so

.PHONY: setup

all: setup
	$(CXX) $(CFLAGS) $(OPT) `find source/ -name "*.cpp"` $(LFLAGS) $(DEPS) $(OUT)

setup:
	mkdir -p bin

clean:
	rm -rf bin
