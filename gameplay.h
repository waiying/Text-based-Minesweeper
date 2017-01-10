#ifndef GAMEPLAY_H
#define GAMEPLAY_H

bool valid_play(Board board, int playRow, int playCol);
void get_play(Board board, int* playRow, int* playCol);
int get_action(Board board, int i, int j);
void check_mines_left(Board board);
void non_mine_revealed(Board* board, int i, int j);
void play_game(Board board);

#endif
