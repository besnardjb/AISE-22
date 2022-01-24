CC=gcc
CFLAGS=-O3 -g
 
TARGET=test
 
all: $(TARGET)
 
libppm.so : ppm.c
	$(CC) $(CFLAGS)  -fpic -shared $^ -o $@
 
test: main.c libppm.so
	$(CC) $(CFLAGS) $(LDFLAGS) main.c -lppm -L. -Wl,-rpath=$(PWD) -o $@
 
clean:
	rm -fr $(TARGET) *.so

