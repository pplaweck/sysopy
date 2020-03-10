CC = gcc -Wall -std=c11 -ggdb

all: static_lib shared_lib clean

static_lib:
	$(CC) -c library.c
	ar rcs library.a library.o

shared_lib:
	$(CC) -c -fPIC library.c
	$(CC) -shared -fPIC -o library.so library.o

clean:
	rm -f *.o tmp
