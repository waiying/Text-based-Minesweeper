//This file contains functions that facilitates the game play of minesweeper
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structdef.h"
#include "gameplay.h"
#include "endgame.h"
#include "printboard.h"

bool valid_play(Board board, int playRow, int playCol) {
	//This function checks if the play move is valid. 
	//@board: Board type, represents the status of the board
	//@playRow: integer type, represents the row that the player chose
	//@playCol: integer type, represents the column that the player chose
	//@return: boolean value
	if (playRow > (board.rows - 1) || playCol > (board.cols - 1) || playRow < 0 || playCol < 0) { //invalid if play move is outside of board
		return false;
	}
	else if (board.tiles[playRow][playCol].visibility == REVEALED) {
		printf("This tile is already revealed.\n");
		return false;
	}
	else {
		return true;
	}
}

void get_play(Board board, int* playRow, int* playCol) {
	//this function gets the player's move
	//@board: Board type, represents the status of the board
	//@playRow: integer pointer type, points to a memory location that represents the row that the player chose
	//@playCol: integer pointer type, points to a memory location that represents the column that the player chose
	//@return: none
	printf("Enter row a row between 0-%d and a column between 0-%d: ", board.rows - 1, board.cols - 1);
	scanf("%d %d", playRow, playCol);
	return;
}

int get_action(Board board, int i, int j) {
	//this function prints the appropriate set of actions to chose from and gets the action that the player chose
	//@board: Board type, represents the status of the board
	//@i: integer type, the current row chosen by the player
	//@j: integer type, the current column chosen by the player
	//@return: integer type, the action chosen by the player
	int action;
	if (board.tiles[i][j].visibility == QUESTIONED) {
		printf("Enter Action\n");
		printf("0. UnQuestion\n");
		printf("1. Cancel\n");
		printf("Action: ");
		scanf("%d", &action);
	}
	else if (board.tiles[i][j].visibility == MARKED) {
		printf("Enter Action\n");
		printf("0. UnMark\n");
		printf("1. Cancel\n");
		printf("Action: ");
		scanf("%d", &action);
	}
	else {
		printf("Enter Action\n");
		printf("0. Reveal\n");
		printf("1. Question\n");
		printf("2. Mark\n");
		printf("3. Cancel\n");
		printf("Action: ");
		scanf("%d", &action);
	}
	return action;
}

void check_mines_left(Board board) {
	//this function prints out how many mines are left.
	//@board: Board type, represents the status of the board
	//@return: none
	int i, j;
	for (i = 0; i<board.rows; ++i) {
		for (j = 0; j<board.cols; ++j) {
			if (board.tiles[i][j].visibility == MARKED) {
				--board.mines;
			}
		}
	}
	printf("There are %d mines left\n", board.mines);
	return;
}

void non_mine_revealed(Board* board, int i, int j) {
	//this function reveals the tile that the player chose and recursively reveals all the tiles until it reaches a tile that has mines surrounding it if the tile that the player chose has no mines surrounding it.
	//@board: Board pointer type, points to the memory location that represents the status of the board
	//@i: integer type, the current row chosen by the player
	//@j: integer type, the current column chosen by the player
	//@return: none
	if (board->tiles[i][j].num_surrounding_mines > 0 && (board->tiles[i][j].visibility == CONCEALED || board->tiles[i][j].visibility == REVEALED)) { //if the current tile has mines surrounding it and its visibility status is either concealed or revealed, the tile will be revealed and exit the functon.
		board->tiles[i][j].visibility = REVEALED;
		return;
	}
	else {//if the tile is not a mine
		if (board->tiles[i][j].visibility == CONCEALED) { //reveal the concealed non-mine tile and reveal the surrounding tiles
			board->tiles[i][j].visibility = REVEALED;
			if ((i < board->rows - 1) && (i > 0) && (j < board->cols - 1) && (j > 0)) { // checks if the tile is not on the boarders of the board
				non_mine_revealed(board, i - 1, j - 1);
				non_mine_revealed(board, i, j - 1);
				non_mine_revealed(board, i + 1, j - 1);
				non_mine_revealed(board, i + 1, j);
				non_mine_revealed(board, i + 1, j + 1);
				non_mine_revealed(board, i, j + 1);
				non_mine_revealed(board, i - 1, j + 1);
				non_mine_revealed(board, i - 1, j);
			}
			else if (i == 0 && j == 0) {//checks if the tile is on the bottom left corner
				non_mine_revealed(board, i + 1, j);
				non_mine_revealed(board, i + 1, j + 1);
				non_mine_revealed(board, i, j + 1);
			}
			else if ((i == board->rows - 1) && j == 0) { //checks if the tile is on the top right corner
				non_mine_revealed(board, i - 1, j);
				non_mine_revealed(board, i - 1, j + 1);
				non_mine_revealed(board, i, j + 1);
			}
			else if ((i == board->rows - 1) && (j == board->cols - 1)) { // checks if the tile is on the top left corner
				non_mine_revealed(board, i, j - 1);
				non_mine_revealed(board, i - 1, j - 1);
				non_mine_revealed(board, i - 1, j);
			}
			else if (i == 0 && (j == board->cols - 1)) { //checks tile on the bottom left corner of the board
				non_mine_revealed(board, i, j - 1);
				non_mine_revealed(board, i + 1, j - 1);
				non_mine_revealed(board, i + 1, j);
			}
			else if (i == 0) { //checks the bottom row of tiles
				non_mine_revealed(board, i, j + 1);
				non_mine_revealed(board, i + 1, j + 1);
				non_mine_revealed(board, i + 1, j);
				non_mine_revealed(board, i + 1, j - 1);
				non_mine_revealed(board, i, j - 1);
			}
			else if (j == 0) { //checks the left column of tiles
				non_mine_revealed(board, i + 1, j);
				non_mine_revealed(board, i + 1, j + 1);
				non_mine_revealed(board, i, j + 1);
				non_mine_revealed(board, i - 1, j + 1);
				non_mine_revealed(board, i - 1, j);
			}
			else if (j == board->cols - 1) { //checks the right column of tiles
				non_mine_revealed(board, i + 1, j);
				non_mine_revealed(board, i + 1, j - 1);
				non_mine_revealed(board, i, j - 1);
				non_mine_revealed(board, i - 1, j - 1);
				non_mine_revealed(board, i - 1, j);
			}
			else if (i == board->rows - 1) { //checks the top row of tiles
				non_mine_revealed(board, i, j + 1);
				non_mine_revealed(board, i - 1, j + 1);
				non_mine_revealed(board, i - 1, j);
				non_mine_revealed(board, i - 1, j - 1);
				non_mine_revealed(board, i, j - 1);
			}
		}
		else if (board->tiles[i][j].visibility == REVEALED) {//exits the function if the non-mine tile is revealed
			return;
		}
	}
	return;
}

void play_game(Board board) {
	//this function facilitates the gameplay
	//@board: Board type, represents the status of the board
	//@return: none
	int action; //player's choice of action
	int playRow, playCol; //player's choice of tile location

	get_play(board, &playRow, &playCol);
	while (!valid_play(board, playRow, playCol)) {
		get_play(board, &playRow, &playCol);
	}
	action = 20; //initializes action
	while (!game_over(board, playRow, playCol, action)) { //game continues if the game is not over
		if (board.tiles[playRow][playCol].visibility == QUESTIONED || board.tiles[playRow][playCol].visibility == MARKED) {
			action = get_action(board, playRow, playCol);
			if (action == 0) {
				board.tiles[playRow][playCol].visibility = CONCEALED;
				action = 20; //resets action value
			}
			else if (action >= 1 || action < 0) {
				get_play(board, &playRow, &playCol); //asks for a new move since the user either canceled the previous move or entered an invalid action.
				while (!valid_play(board, playRow, playCol)) {
					get_play(board, &playRow, &playCol);
				}
				continue;
			}
		}
		else if (board.tiles[playRow][playCol].visibility == CONCEALED) {
			action = get_action(board, playRow, playCol);
			if (action >= 3 || action < 0) {//asks for a new move since the user either canceled the previous move or entered an invalid action.
				get_play(board, &playRow, &playCol);
				while (!valid_play(board, playRow, playCol)) {
					get_play(board, &playRow, &playCol);
				}
				continue;
			}
			else if (action == 0) {
				if (board.tiles[playRow][playCol].is_mine == 0) {
					non_mine_revealed(&board, playRow, playCol);
				}
			}
			else if (action == 1) {
				board.tiles[playRow][playCol].visibility = QUESTIONED;
			}
			else if (action == 2) {
				board.tiles[playRow][playCol].visibility = MARKED;
			}
			if (game_over(board, playRow, playCol, action)) {
				return;
			}
		}
		check_mines_left(board);
		print_board(board);
		get_play(board, &playRow, &playCol);
		while (!valid_play(board, playRow, playCol)) {
			get_play(board, &playRow, &playCol);
		}
		action = 20; //resets action
	}
	return;
}