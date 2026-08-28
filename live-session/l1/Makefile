

%.S: %.c
	gcc -fno-inline -fno-stack-protector -fno-pic -static -Werror -fcf-protection=none -fno-asynchronous-unwind-tables -Os -S -masm=intel $^ -o $@


main: puzzle3.S main.c
	as puzzle3.S -o mystery.o
	gcc main.c -c -o main.o
	gcc mystery.o main.o -o main
