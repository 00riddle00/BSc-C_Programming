CFLAGS=-Wall -Wextra -g -lm -std=gnu11

test: test.c 
	gcc -o test test.c -L${LD_LIBRARY_PATH} -l_riddle 
	#gcc -o test test.c sorting.o -L${LD_LIBRARY_PATH} -l_riddle 

#sorting.o: sorting.h sorting.c

clean:
	rm test

