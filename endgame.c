//The file contains functions that deals with the game ending
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structdef.h"
#include "endgame.h"
#include "printboard.h"

bool game_won(Board* board) {
	//THis function checks if the game is won
	//@board: Board pointer type, points to the memory location that represents the status of the board
	//@returns: boolean value
	int i, j;
	int count = 0, mine_count = 0; //count is the number of revealed tiles, mine_count is the number of marked tiles.
	for (i = 0; i < board->rows; ++i) {//iterates through all the tiles to count
		for (j = 0; j < board->cols; ++j) {
			if (board->tiles[i][j].visibility == REVEALED) {
				++count;
			}
			else if (board->tiles[i][j].visibility == MARKED) {
				++mine_count;
			}
		}
	}

	if (count == ((board->rows * board->cols) - board->mines) && mine_count == board->mines) {//if count is equal to the number of non-mine tiles and mine_count is the total number of mines, then the game is won.
		for (i = 0; i<board->rows; ++i) {
			for (j = 0; j<board->cols; ++j) {
				board->tiles[i][j].visibility = REVEALED; //reveal every tile
			}
		}
		return true;
	}
	else { //otherwise game is not won
		return false;
	}
	return false;
}

bool game_lost(Board board, int i, int j, int action) {
	//this function checks to see if the game is lost
	//@board: Board type, represents the status of the board
	//@i: integer type, the current row chosen by the player
	//@j: integer type, the current column chosen by the player
	//@action: integer type, represents the action chosen by the player
	//@return: boolean value
	int k, m;
	if (board.tiles[i][j].is_mine == 1 && action == 0) { //if player choose to reveal a mine tile, game is lost
		for (k = 0; k<board.rows; ++k) {
			for (m = 0; m<board.cols; ++m) {
				board.tiles[k][m].visibility = REVEALED; //every tile gets revealed
			}
		}
		return true;
	}
	return false;
}

bool game_over(Board board, int i, int j, int action) {
	//this function determines if the game is over because the game was either lost or won.
	//@board: Board type, represents the status of the board
	//@i: integer type, the current row chosen by the player
	//@j: integer type, the current column chosen by the player
	//@action: integer type, represents the action chosen by the player
	//@return: boolean value
	if (game_lost(board, i, j, action)) {
		print_board(board);
		printf("You Lost :(\n");
		return true;
	}
	else if (game_won(&board)) {
		print_board(board);
		printf("You Won!!\n");
		return true;
	}
	return false; //game is not over since the game is not won or lost
}

void destroy_board(Board* board) {
	/*This function frees the allocated memory space for board. Nothing is returned.
	The parameter, board, is a character double pointer that stores the contents of the board.
	The parameter, row, is of int type, representing the # of rows in the board.*/
	int i;
	for (i = 0; i < board->rows; ++i) {
		free(board->tiles[i]); //frees each row of lists.
	}
	free(board->tiles);//frees the space for the list of rows.
	return;
}