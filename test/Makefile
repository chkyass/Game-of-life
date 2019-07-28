CC := /usr/local/bin/gcc-9 
CFLAGS := -O0 -g -std=c99 -Wall -Werror -Wextra -Wshadow -pedantic  

all:
	@$(CC) $(CFLAGS) gameOfLife-test.c ../gameOfLife.c  -o test.bin && ./test.bin ../board.txt