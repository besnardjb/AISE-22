CC?=gcc
AR?=ar

start:
	mkdir -p build/lib

build/lib/libmymalloc.so: lib.c start
	$(CC) -shared -fPIC -o $@ $< -ldl

build/program: main.c build/lib/libmymalloc.so
	$(CC) $< -o $@

run: build/program build/lib/libmymalloc.so
	LD_PRELOAD=build/lib/libmymalloc.so build/program

clean:
	rm -rf build/*


.PHONY: start
