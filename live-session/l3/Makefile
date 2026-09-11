CC = gcc
CFLAGS = -Wall -g

all: matmul-ijk matmul-ikj matmul-jik matmul-jki matmul-kij matmul-kji

matmul-%: matmul.c matrix-%.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o matmul-ijk matmul-ikj
