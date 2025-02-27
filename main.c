#include <curses.h>
#include <ncurses.h>
#include <stdbool.h>

#define ARR_UP 'A'
#define ARR_DOWN 'B'
#define ARR_RIGHT 'C'
#define ARR_LEFT 'D'

typedef enum Player {
	Unplayed = 0,
	Circle = 1,
	Cross = 2,
} Player;

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

void jogar(Player table[3][3], Player player) {
	clear();
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

		if (table[vert][hori] !=  0) {
			cont = true;
			thin = getch();
			continue;
		}
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
