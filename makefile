CC=gcc

game: Main.c
	$(CC) -o game Main.c -lncurses
