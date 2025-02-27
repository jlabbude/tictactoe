#include "tictac.h"
#include <curses.h>
#include <ncurses.h>

void print_table(Player table[3][3]) {
	clear();
	for (int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			printw("[ %c ] ", return_player_char((Player)table[i][j]));
        }
		printw("\n");
	}
}

void selection(Player table[3][3], int y, int x, Player player) {
	for (int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
            if (y == i && x == j) {
                attron(COLOR_PAIR(1)); 
                printw("[ %c ] ", return_player_char(player));
                attroff(COLOR_PAIR(1));
            } else {
                printw("[ %c ] ", return_player_char((Player)table[i][j]));
            }	
	    }
        printw("\n");
    }
}
