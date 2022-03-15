CC=gcc
CFLAGS=-O3 -g
 
libppm.so : ppm.c
	    $(CC) $(CFLAGS)  -fpic -shared $^ -o $@

program: algo.c libppm.so
	$(CC) -L. $< -o $@ -lppm -lm
