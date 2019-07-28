#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "gameOfLife.h"

int main(int argc, char **argv) {
    //init_hardcoded_game();
    if(argc != 2)
        exit(1);
    init_from_file(argv[1]);
    play(10);
    return 0;
}
