#ifndef TICTAC_H
#define TICTAC_H
#include <stdbool.h>

typedef enum Player {
	Unplayed = 0,
	Circle = 1,
	Cross = 2,
} Player;

bool check_straight(Player table[3][3], Player player);
bool check_diagonal(Player table[3][3], Player player);
bool has_won(Player table[3][3], Player player);
char return_player_char(Player player);
void print_table(Player table[3][3]);
void selection(Player table[3][3], int y, int x, Player player);

#endif
