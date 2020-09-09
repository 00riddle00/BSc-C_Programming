CC = gcc
CFLAGS=-Wall -xc -g -lm -std=gnu99

f.o: f.s
	gcc -c f.s -o f.o

f.s: f.i
	gcc -S f.i -o f.s

f.i: f.c
	gcc -E f.c -o f.i

main.exe: main.c f.o
	gcc main.c f.o -o main.exe

clean:
	rm -f f.i f.o f.s main.exe

clean_all:
	rm *.i *.o *.s *.exe

rebuild: clean main.exe
	# to preprocessed source code
	#gcc -E f.c -o f.i

	# to assembly code	
	#gcc -S f.i -o f.s 
	
	# to object file:
	#gcc -c f.s -o f.o
		
	# to executable
	#gcc main.c f.o -o main.exe


