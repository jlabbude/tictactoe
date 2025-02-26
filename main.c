#include <curses.h>
#include <ncurses.h>
#include <stdbool.h>

#define CIRCLE 1
#define CROSS 2

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
					if (vert > 0) {
						vert--;
					}
					break;
				case ARR_DOWN:
					if (vert < 2) {
						vert++;
					}
					break;
				case ARR_LEFT:
					if (hori > 0) {
						hori--;
					}
					break;
				case ARR_RIGHT:
					if(hori < 2) {
						hori++;
					}
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
	
	Player um = Circle;
	Player dois = Cross;

	initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);


	while(1) {
		print_table(table);
		jogar(table, um);
        if (has_won(table, um)) {
            endwin();
            printf("Jogador %c ganhou!\n", return_player_char(um));
            return 0;
        }

        print_table(table);
		jogar(table, dois);
        if (has_won(table, dois)) {
            endwin();
            printf("Jogador %c ganhou!\n", return_player_char(dois));
            return 0;
        }
    }

	return 0;
}
