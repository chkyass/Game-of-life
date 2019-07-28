#include <stdio.h>
#include <assert.h>
#include "../gameOfLife.h"

void test_is_out_limit() {
    assert(is_out_limit(-1, 1));
    assert(is_out_limit(10, -1));
    assert(is_out_limit(-1, -1));
    assert(is_out_limit(BOARD_SIZE, BOARD_SIZE));
    assert(is_out_limit(BOARD_SIZE, -1));
    assert(!is_out_limit(0,5));
}

/*
	world[1][2] = ALIVE;
	world[3][1] = ALIVE;
	world[3][2] = ALIVE;
	world[3][3] = ALIVE;
	world[2][3] = ALIVE;

  0 1 2 3 4 5
0| | | | | | |
1| | |*| | | |
2| | | |*| | |
3| |*|*|*| | |
4| | | | | | |
5| | | | | | |

  0 1 2 3 4 5
0| | | | | | |
1| | | | | | |
2| |*| |*| | |
3| | |*|*| | |
4| | |*| | | |
5| | | | | | |
 */

void test_change_state() {
    init_hardcoded_game();
    /* 0 neighboors dead */
    assert(change_state(0,0) == 0);
    /* 3 neighboors live */
    assert(change_state(2,3) == 0);
    assert(change_state(3,2) == 0);
    /* 2 neighboors live */
    assert(change_state(3,3) == 0);
    /* 1 neighboor die */
    assert(change_state(3,1) == 1);
    assert(change_state(1,2) == 1);
    /* 3 neighboors become alive */
    assert(change_state(2,1) == 1);
    assert(change_state(4,2) == 1);

}

void test_update_board() {
    init_hardcoded_game();
    coords * c = add_coord(NULL, 0, 0);
    c = add_coord(c, 1, 2);

    uint8_t previous_state0 = BOARD[0][0];
    uint8_t previous_state1 = BOARD[1][2];

    update_board(c);
    assert(BOARD[0][0] != previous_state0);
    assert(BOARD[1][2] != previous_state1);

}

void test_init_from_file() {
    init_from_file("board.txt");
    assert(BOARD[1][2] == 1);
	assert(BOARD[3][1] == 1);
	assert(BOARD[3][2] == 1);
	assert(BOARD[3][3] == 1);
	assert(BOARD[2][3] == 1);
}

int main(int argc, char ** argv) {
    test_is_out_limit();
    test_change_state();
    test_update_board();
    if(argc != 2)
        exit(1);
    init_from_file(argv[1]);
    return 0;
}