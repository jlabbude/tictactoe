default:
	gcc -Wall *.c *.h -o build/main -lcurses -lncurses
	build/./main
ebuild:
	gcc -Wall *.c *.h -o build/main -lcurses -lncurses
