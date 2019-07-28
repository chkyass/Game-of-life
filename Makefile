CC := gcc-9
CFLAGS := -O0 -g -std=c99 -Wall -Werror -Wextra -Wshadow -pedantic  

all:
	@$(CC) $(CFLAGS) main.c gameOfLife.c -o gameOfLife.bin

run:
	./gameOfLife.bin board.txt
