CC?=gcc
AR?=ar

start:
	mkdir -p build/lib

build/lib/libcustom.so: code.c include/mylib.h start
	$(CC) -shared -fPIC -o $@ $<
build/lib/libcustom2.so: code2.c include/mylib.h start
	$(CC) -shared -fPIC -o $@ $<

program: main.c build/lib/libcustom.so build/lib/libcustom2.so
	$(CC) -I./include -L./build/lib $< -lcustom -o build/dynamic -Wl,-rpath=./build/lib

clean:
	rm -rf build/*


.PHONY: start
