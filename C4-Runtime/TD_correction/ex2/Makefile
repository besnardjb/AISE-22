CC?=gcc

all: reader.exe writer.exe

%.exe: %.c
	$(CC) $< -o $@

clean:
	rm -f *.exe map_file.txt

.PHONY: clean
