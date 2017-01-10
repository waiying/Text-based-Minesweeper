//This is a minesweeper game. The goal is to try to mark all the mines and reveal all the non-mine tiles.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "structdef.h"
#include "makeboard.h"
#include "printboard.h"
#include "gameplay.h"
#include "endgame.h"

void check_args(int tot_args, char** argv) {
	//This function checks whether the amount of command line arguments is correct.
	//@tot_args: an integer of the total elements in the command line
	//@argv: a list of arrays of the command line arguments
	//@return: none
	if (tot_args == 5) {
		srand(atoi(argv[4]));//uses the specified seed
	}
	else {
		if (tot_args == 4) {
			srand((int)time(0));//assigns a random seed at the current time
		}
		else if (tot_args < 4) {
			printf("Not enough arguments. Usage:\n");
			printf("./mine_sweeper.out num_rows num_cols num_mines [seed])\n");
			exit(EXIT_SUCCESS);
		}
		else if (tot_args > 5) {
			printf("Too many arguments. Usage:\n");
			printf("./mine_sweeper.out num_rows num_cols num_mines [seed])\n");
			exit(EXIT_SUCCESS);
		}
	}
	return;
}

int main(int argc, char** argv) {

	int rows = 0;
	int cols = 0;
	int tot_mines = 0;//total # of mines on the board
	Board TheBoard; //current status of the board

	check_args(argc, argv);
	rows = atoi(argv[1]);
	cols = atoi(argv[2]);
	tot_mines = atoi(argv[3]);

	TheBoard = create_board(rows, cols, tot_mines);
	print_board(TheBoard);
	play_game(TheBoard);
	destroy_board(&TheBoard);

	return 0;
}