#include <stdlib.h>
#include <stdint.h>

#ifndef __GAME_OF_LIFE__
#define __GAME_OF_LIFE__

#define GENERATIONS 50

typedef struct coords {
    uint32_t x;
    uint32_t y;
    struct coords *next;
} coords;


extern uint32_t BOARD_SIZE;
uint8_t **BOARD;


void init_hardcoded_game(void);
void init_from_file(const char * filename);
coords* add_coord(coords *head, uint32_t line, uint32_t column);
void play(uint32_t iterations);
void update_board(coords *statesToInvert);
uint8_t change_state(uint32_t line, uint32_t column);
uint8_t is_out_limit(uint32_t line, uint32_t column);
void print_game(void);

#endif
