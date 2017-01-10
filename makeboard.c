//This file initializes the status of the game board
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structdef.h"
#include "makeboard.h"
#include "gameplay.h"

Board create_board(int rows, int cols, int num_mines) {
	//This function initializes the status of the board
	//@rows: an integer representing the number of rows
	//@cols: an integer representing the number of columns
	//@num_mines: an integer representing the total number of mines
	//@return: board, a Board type
	int i, j;
	int randRow, randCol; //temporary location of the mines
	Board board; //creates the board
	board.rows = rows;
	board.cols = cols;
	board.mines = num_mines;

	board.tiles = (Tile**)malloc(rows * sizeof(Tile*)); //allocates memory for the board tiles
	for (i = 0; i<rows; ++i) {
		board.tiles[i] = (Tile*)malloc(cols * sizeof(Tile));
	}

	//initializes every tile to be concealed and every num_surrounding mines to be zero.
	for (i = 0; i<rows; ++i) {
		for (j = 0; j<cols; ++j) {
			board.tiles[i][j].visibility = CONCEALED;
			board.tiles[i][j].num_surrounding_mines = 0;
		}
	}

	i = 1;
	//Start placing mines.
	randRow = rand() % rows;//assigns a random row for the first mine
	randCol = rand() % cols; //assigns a random column for the first mine
	board.tiles[randRow][randCol].is_mine = 1; //'1' means that tile is a mine
	printf("Placing mine at %d, %d\n", randRow, randCol);
	while (i != num_mines) {
		if (board.tiles[randRow][randCol].is_mine == 1) { //checks if that tile already has a mine
			randRow = rand() % rows;
			randCol = rand() % cols;
			continue;
		}
		else { //if tile has no mine, assign a mine to it
			board.tiles[randRow][randCol].is_mine = 1;
			++i;
			printf("Placing mine at %d, %d\n", randRow, randCol);
			randRow = rand() % rows;
			randCol = rand() % cols;
		}
	}

	for (i = 0; i<board.rows; ++i) { //goes through every tile that is not a mine to check for the number of surrounding mine
		for (j = 0; j<board.cols; ++j) {
			if (board.tiles[i][j].is_mine == 0) { //checks if the tile is a mine or not
				if ((i < board.rows - 1) && (i > 0) && (j < board.cols - 1) && (j > 0)) { //checks in the 8 surrounding tiles for the number of surrounding mines for each tile not on the edge of the board.
					if (board.tiles[i - 1][j - 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i][j - 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i + 1][j - 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i + 1][j].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i + 1][j + 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i][j + 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i - 1][j + 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i - 1][j].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
				}
				else if (i == 0 && j == 0) { //checks tile on the bottom left corner of the board
					if (board.rows == 1) {
						if (board.tiles[i][j + 1].is_mine == 1) {
							++board.tiles[i][j].num_surrounding_mines;
						}
					}
					else if (board.cols == 1) {
						if (board.tiles[i + 1][j].is_mine == 1) {
							++board.tiles[i][j].num_surrounding_mines;
						}
					}
					else {
						if (board.tiles[i + 1][j].is_mine == 1) {
							++board.tiles[i][j].num_surrounding_mines;
						}
						if (board.tiles[i + 1][j + 1].is_mine == 1) {
							++board.tiles[i][j].num_surrounding_mines;
						}
						if (board.tiles[i][j + 1].is_mine == 1) {
							++board.tiles[i][j].num_surrounding_mines;
						}
					}
				}
				else if ((i == board.rows - 1) && j == 0) { //checks tile on the top left corner of the board
					if (board.tiles[i - 1][j].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i - 1][j + 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i][j + 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
				}
				else if ((i == board.rows - 1) && (j == board.cols - 1)) { //checks tile on the top right corner of the board
					if (board.tiles[i][j - 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i - 1][j - 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i - 1][j].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
				}
				else if (i == 0 && (j == board.cols - 1)) { //checks tile on the bottom left corner of the board
					if (board.tiles[i][j - 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i + 1][j - 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i + 1][j].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
				}
				else if (i == 0) { //checks the bottom row of tiles
					if (board.tiles[i][j + 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i + 1][j + 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i + 1][j].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i + 1][j - 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i][j - 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
				}
				else if (j == 0) { //checks the left column of tiles
					if (board.tiles[i + 1][j].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i + 1][j + 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i][j + 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i - 1][j + 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i - 1][j].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
				}
				else if (j == board.cols - 1) { //checks the right column of tiles
					if (board.tiles[i + 1][j].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i + 1][j - 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i][j - 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i - 1][j - 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i - 1][j].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
				}
				else if (i == board.rows - 1) { //checks the top row of tiles
					if (board.tiles[i][j + 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i - 1][j + 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i - 1][j].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i - 1][j - 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
					if (board.tiles[i][j - 1].is_mine == 1) {
						++board.tiles[i][j].num_surrounding_mines;
					}
				}
			}
		}
	}
	check_mines_left(board);//prints out how many mines are left
	return board;
}