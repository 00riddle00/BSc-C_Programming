CC=gcc
CFLAGS=-Wall -Wextra -xc -g -std=gnu99

kontrolinis2: lib_riddle.a
	$(CC) -o kontrolinis2 kontrolinis2.c -L. lib_riddle.a

clean:
	rm kontrolinis2

rebuild: clean kontrolinis2
