CC?=gcc
AR?=ar

start:
	mkdir -p build/lib

build/lib/libmylib.a: code.c include/mylib.h start
	$(CC) -o build/code.o $< -c
	$(AR) rcs $@ build/code.o


build/lib/libmylib.so: code.c include/mylib.h start
	$(CC) -shared -fPIC -o $@ $<

program: main.c build/lib/libmylib.a build/lib/libmylib.so
	$(CC) -I./include -L./build/lib $< -lmylib -o build/dynamic -Wl,-rpath=./build/lib
	$(CC) -I./include -L./build/lib $< -lmylib -static -o build/static

clean:
	rm -rf build/*


.PHONY: start
