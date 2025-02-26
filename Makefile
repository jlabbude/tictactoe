default:
	gcc -Wall main.c -o build/main -lcurses -lncurses
	build/./main
ebuild:
	gcc -Wall main.c -o build/main -lcurses -lncurses
