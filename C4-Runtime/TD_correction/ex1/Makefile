CC?=gcc

all: libmystring.so program

libmystring.so: string.c mystring.h
	$(CC) $< -o $@ -shared -fPIC -I.

program: main.c libmystring.so
	$(CC) -I. -L. $< -o $@ -lmystring

clean:
	rm -f *.o *.so program

.PHONY: clean
