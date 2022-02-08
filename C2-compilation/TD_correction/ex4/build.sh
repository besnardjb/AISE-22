#!/bin/sh

# preprocessing
cpp main.c -o main.i

# compilation
# be sure to use the right version  (here GCC 9 series)
/usr/lib/gcc/x86_64-linux-gnu/9/cc1 main.i -o main.s

## Assemble
as main.s -o main.o

## Link:
## crt1 -> _start()
## crti -> _init()
## crtn -> _fini()
## -dynamic-linker -> to register the program bootstraping libraries
ld main.o -o program /usr/lib/x86_64-linux-gnu/crt1.o /usr/lib/x86_64-linux-gnu/crti.o /usr/lib/x86_64-linux-gnu/crtn.o   -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2

./program

rm -f main.o main.s main.i
