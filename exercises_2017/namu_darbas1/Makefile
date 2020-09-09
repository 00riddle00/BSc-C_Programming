CFLAGS=-Wall -Wextra -g -lm -std=gnu11

program: program.c binary_file.o filter.o sorting.o
	gcc -o program program.c binary_file.o filter.o sorting.o -L${LD_LIBRARY_PATH} -l_riddle -lm

binary_file.o: binary_file.h binary_file.c 

sorting.o: database.h sorting.c sorting.h

filter.o: database.h filter.c filter.h

clean:
	rm -f program binary_file.o sorting.o filter.o

rebuild: clean program

