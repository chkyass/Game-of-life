#include <stdlib.h>
#include <stdio.h>
//#include <stdint.h>
#include "gameOfLife.h"

uint32_t BOARD_SIZE = 6;

void alloc_board () {
    BOARD = (uint8_t**) malloc(sizeof(uint8_t*)*BOARD_SIZE);
    for(size_t i = 0; i < BOARD_SIZE; i++) {
        BOARD[i] = (uint8_t*) calloc(BOARD_SIZE, sizeof(uint8_t));
    }
}

void free_board() {
    for(size_t i = 0; i < BOARD_SIZE; i++) {
        free(BOARD[i]);
    }
    free(BOARD);
}

void init_hardcoded_game() {
    alloc_board();
    for(uint32_t j = 0; j < BOARD_SIZE; j++)
    {
        for (uint32_t i = 0; i < BOARD_SIZE; i++)
        {
            BOARD[j][i] = 0;
        }
    }
    BOARD[1][2] = 1;
	BOARD[3][1] = 1;
	BOARD[3][2] = 1;
	BOARD[3][3] = 1;
	BOARD[2][3] = 1;
}

void init_from_file(const char * filename) {
    FILE * fd = fopen(filename, "r");
    if(fd == NULL)
        exit(EXIT_FAILURE);
    
    if(fscanf(fd, "%u\n", (unsigned int*) &BOARD_SIZE) == 0){
        exit(EXIT_FAILURE);
    }
    
    alloc_board();
    int x;
    int y;
    while(fscanf(fd, "%d %d\n", &x, &y) != EOF) {
        BOARD[x][y] = 1;
    }
}

void print_game() {
    for (size_t i = 0; i < BOARD_SIZE; i++) {
        for (size_t j = 0; j < BOARD_SIZE; j++) {
            printf("|%u|", BOARD[i][j]);
        }
        puts("");
    }
}

/* Use switch case to make it O(2)*/
uint8_t is_out_limit(uint32_t line, uint32_t column) {
    return  line >= BOARD_SIZE || column >= BOARD_SIZE;
}

/* check if cell has a futur different state */
uint8_t change_state(uint32_t line, uint32_t column) {
    uint8_t neighboors = 0;
    for (int8_t i = -1; i < 2; i++)
    {
        for (int8_t j = -1; j < 2; j++)
        {
            if (!is_out_limit(line+i, column+j)) {
                neighboors += BOARD[line+i][column+j];
            }

        }  
    }
    /* for i=j=0 in the loop */
    neighboors -= BOARD[line][column];

    /* 
    first part compute the new state of tghe cell 
    the second check if it's a new state 
    */
    return ((BOARD[line][column] && (neighboors == 2)) || (neighboors == 3))^BOARD[line][column];    
}

coords* add_coord(coords *head, uint32_t x, uint32_t y) {
    coords *coord = (coords*) malloc(sizeof(coords));
    coord->x = x;
    coord->y = y;
    coord->next = head;

    return coord;
}

void update_board(coords *statesToInvert) {
    coords *coord; 
    while(statesToInvert != NULL) {
        BOARD[statesToInvert->x][statesToInvert->y] = !BOARD[statesToInvert->x][statesToInvert->y];
        coord = statesToInvert;
        statesToInvert = statesToInvert->next;
        free(coord);
    }
}

void play(uint32_t iterations) {
    while (iterations-- > 0) {
        coords *statesToInvert = NULL;
        for (uint32_t i = 0; i < BOARD_SIZE; i++) {
            for (uint32_t j = 0; j < BOARD_SIZE; j++) {
                if(change_state(i, j)) {
                    statesToInvert = add_coord(statesToInvert, i, j);
                }
            }   
        }
        update_board(statesToInvert);
    }
    free_board();
}
