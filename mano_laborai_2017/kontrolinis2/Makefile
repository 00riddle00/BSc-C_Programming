CC=gcc
CFLAGS=-DNDEBUG -fPIC -Wall -g -std=gnu11 #-Wextra -Wconversion -pedantic
#CFLAGS=-fPIC -Wall -g -std=gnu11 #-Wextra -Wconversion -pedantic

kontrolinis2: lib_riddle.a
	$(CC) $(CFLAGS) -o kontrolinis2 kontrolinis2.c -L. lib_riddle.a

clean:
	rm kontrolinis2

rebuild: clean kontrolinis2
