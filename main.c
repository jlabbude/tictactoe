#include <curses.h>
#include <ncurses.h>
#include <stdio.h>
#include "tictac.h"

#define ARR_UP 'A'
#define ARR_DOWN 'B'
#define ARR_RIGHT 'C'
#define ARR_LEFT 'D'

void jogar(Player table[3][3], Player player) {
	print_table(table);
	int hori = 0;
	int vert = 0;

	char thin = getch();
	bool cont = false;
	do {
		cont = false;
		if (thin == '\033') {
			getch();
			switch(getch()) {
				case ARR_UP:
					vert = (vert > 0) ? vert-1 : 2;
					break;
				case ARR_DOWN:
					vert = (vert < 2) ? vert + 1 : 0;
					break;
				case ARR_LEFT:
					hori = (hori > 0) ? hori-1 : 2;
					break;
				case ARR_RIGHT:
					hori = (hori < 2) ? hori+1 : 0;
					break;
			}
		}
		
		clear();
        selection(table, vert, hori, player);

		// if (table[vert][hori] !=  0) {
		// 	cont = true;
  //           printw("seu fudido");
		// 	thin = getch();
		// 	continue;
		// }
		thin = getch();
		
	} while(thin != '\n' || cont);

    table[vert][hori] = player;
}

int main() {
	Player table[3][3] = { Unplayed };	

    Player current_players[2] = { Circle, Cross };

	initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);


	for (int i = 0; ; i = (i + 1) % 2) {
		print_table(table);
		jogar(table, current_players[i]);
        if (has_won(table, current_players[i])) {
            endwin();
            printf("Player %c has won!\n", return_player_char(current_players[i]));
            return 0;
        }
    }

	return 0;
}
