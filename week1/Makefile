hello.o: hello.c
	gcc hello.c -c -o hello.o

math.o: math.c
	gcc math.c -c -o math.o

myprogram: math.o hello.o
	gcc math.o hello.o -o myprogram