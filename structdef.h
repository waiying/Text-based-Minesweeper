#ifndef STRUCTDEF_H
#define STRUCTDEF_H

enum Visibility { REVEALED, CONCEALED, MARKED, QUESTIONED };

typedef struct Tile_struct {
	int is_mine;
	int num_surrounding_mines;
	enum Visibility visibility;
} Tile;

typedef struct Board_struct {
	int rows;
	int cols;
	int mines;
	Tile** tiles;
} Board;

#endif