#include "tictac.h"
#include <stdbool.h>

bool check_straight(Player table[3][3], Player player) {
    for (int i = 0; i < 3; i++) {
	    if (table[i][0] == player && table[i][1] == player && table[i][2] == player) {
            return true;
        }
        if (table[0][i] == player && table[1][i] == player && table[2][i] == player) {
            return true;
        }

    }
    return false;
}

bool check_diagonal(Player table[3][3], Player player) {
    bool diag1 = (table[0][0] == player && table[1][1] == player && table[2][2] == player);
    bool diag2 = (table[0][2] == player && table[1][1] == player && table[2][0] == player);
    return diag1 || diag2;
}

bool has_won(Player table[3][3], Player player) {
    return check_straight(table, player) || check_diagonal(table, player);
}

char return_player_char(Player player) {
    switch(player) {
        case Circle:
            return 'O';
            break;
        case Cross:
            return 'X';
            break;
        case Unplayed:
            return ' ';
            break;
       default:
            // -Wall keeps bugging me, even though this shouldn't happen.
            return '\0';
            break;
    }
}
