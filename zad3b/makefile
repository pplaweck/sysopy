CC = gcc -Wall -std=c11 -ggdb

all: static_lib shared_lib clean

static_lib:
	$(CC) -c library.c
	ar rcs library.a library.o

shared_lib:
	$(CC) -c -fPIC library.c
	$(CC) -shared -fPIC -o library.o library.so

zad3_s:
	make static_lib
	$(CC) -o test main.c library.a -I .
	make tests

zad3_d:
	make shared_lib
	$(CC) -o test main_dyn.c library.a -I .
	make tests
tests:
	./test
clean:
	rm -f *.o tmp

opt0:
	make static_lib
	$(CC) -O -o test main_dyn.c library.a -I .
	make tests
opt02:
	make static_lib
	$(CC) -O2 -o test main_dyn.c library.a -I .
	make tests
opt03:
	make static_lib
	$(CC) -O3 -o test main_dyn.c library.a -I .
	make tests
opt0s:
	make static_lib
	$(CC) -Os -o test main_dyn.c library.a -I .
	make tests

