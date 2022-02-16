CC?=gcc

all: owner.exe user.exe

%.exe: %.c
	$(CC) $< -o $@

clean:
	rm -f *.exe libsquare.o

.PHONY: clean
