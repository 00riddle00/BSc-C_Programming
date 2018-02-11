CFLAGS=-Wall -Wextra -g -lm -std=gnu11

test: test.c 
	gcc -o test test.c -L${LD_LIBRARY_PATH} -l_riddle 
	#gcc -o test test.c binary_file.o -L${LD_LIBRARY_PATH} -l_riddle 
	#gcc -o test test.c sorting.o -L${LD_LIBRARY_PATH} -l_riddle 

#sorting.o: sorting.h sorting.c
#binary_file.o: binary_file.h binary_file.c

clean:
	rm test

