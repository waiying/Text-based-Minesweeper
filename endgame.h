#ifndef ENDGAME_H
#define ENDGAME_H

bool game_won(Board* board);
bool game_lost(Board board, int i, int j, int action);
bool game_over(Board board, int i, int j, int action);
void destroy_board(Board* board);

#endif
