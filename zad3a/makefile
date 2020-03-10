CC = gcc -Wall -std=c11 -ggdb

all: static_lib shared_lib clean

static_lib:
	$(CC) -c library.c
	ar rcs library.a library.o

shared_lib:
	$(CC) -c -fPIC library.c
	$(CC) -shared -fPIC -o library.so library.o

zad3_s:
	make static
	$(CC) -o test main.c library.a -I .
	make tests

zad3_d:
	zad3_dynamic:
	make shared
	$(CC) -o test main_dyn.c -I .
	make tests
tests:
	./main 
	
	./main_dyn
clean:
	rm -f *.o tmp
