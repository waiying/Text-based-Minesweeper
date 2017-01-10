//This file prints the board according to its status
#include <stdio.h>
#include <stdlib.h>
#include "structdef.h"
#include "printboard.h"

void print_board(Board board) {
	int i, j;

	//prints the row numbers and the board rows' contents.
	for (i = board.rows - 1; i >= 0; --i) {//prints from the top row.
		if (i < 10) { //board spacing will be different if there are double digit columns and rows.
			printf(" %d", i);
		}
		else {
			printf("%d", i);
		}
		for (j = 0; j < board.cols - 1; ++j) { //prints the board row's contents starting from the left. 
			if (board.cols > 9) {//different spacing if the total columns is 2 digits.
				if (board.tiles[i][j].visibility == CONCEALED) {//prints the appropriate concealed character
					printf("  #");
				}
				else if (board.tiles[i][j].visibility == REVEALED) { //prints the appropriate revealed tile character
					if (board.tiles[i][j].is_mine == 1) {
						printf("  *");
					}
					else {
						printf("  %d", board.tiles[i][j].num_surrounding_mines);
					}
				}
				else if (board.tiles[i][j].visibility == MARKED) {//prints the appropriate marked character
					printf("  !");
				}
				else if (board.tiles[i][j].visibility == QUESTIONED) {//prints the appropriate questioned character
					printf("  ?");
				}
			}
			else {//different spacing if the total columns is only 1 digit, the rest is same as the top.
				if (board.tiles[i][j].visibility == CONCEALED) {
					printf(" #");
				}
				else if (board.tiles[i][j].visibility == REVEALED) {
					if (board.tiles[i][j].is_mine == 1) {
						printf(" *");
					}
					else {
						printf(" %d", board.tiles[i][j].num_surrounding_mines);
					}
				}
				else if (board.tiles[i][j].visibility == MARKED) {
					printf(" !");
				}
				else if (board.tiles[i][j].visibility == QUESTIONED) {
					printf(" ?");
				}
			}
		}
		//THe following if-else block prints the last part of the row (just adds the new line character).
		if (board.cols > 9) {
			if (board.tiles[i][board.cols - 1].visibility == CONCEALED) {
				printf("  #\n");
			}
			else if (board.tiles[i][board.cols - 1].visibility == REVEALED) {
				if (board.tiles[i][board.cols - 1].is_mine == 1) {
					printf("  *\n");
				}
				else {
					printf("  %d\n", board.tiles[i][board.cols - 1].num_surrounding_mines);
				}
			}
			else if (board.tiles[i][board.cols - 1].visibility == MARKED) {
				printf("  !\n");
			}
			else if (board.tiles[i][board.cols - 1].visibility == QUESTIONED) {
				printf("  ?\n");
			}
		}
		else {
			if (board.tiles[i][board.cols - 1].visibility == CONCEALED) {
				printf(" #\n");
			}
			else if (board.tiles[i][board.cols - 1].visibility == REVEALED) {
				if (board.tiles[i][board.cols - 1].is_mine == 1) {
					printf(" *\n");
				}
				else {
					printf(" %d\n", board.tiles[i][board.cols - 1].num_surrounding_mines);
				}
			}
			else if (board.tiles[i][board.cols - 1].visibility == MARKED) {
				printf(" !\n");
			}
			else if (board.tiles[i][board.cols - 1].visibility == QUESTIONED) {
				printf(" ?\n");
			}
		}
	}

	//prints the column numbers.
	if (board.cols > 9) { //prints the 0 first
		printf("    0");
	}
	else {
		printf("   0");
	}
	for (i = 1; i < board.cols - 1; ++i) { //prints the rest of the column numbers except for the last one
		if (i < 10 && board.cols > 9) {
			printf("  %d", i);
		}
		else {
			printf(" %d", i);
		}
	}
	printf(" %d\n", board.cols - 1); //prints the last column number
	return;
}
