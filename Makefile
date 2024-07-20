all: compile run

compile:
	mkdir -p bin && clang -std=c2x -o bin/tetris `pkgconf --libs --cflags ncurses libcjson` main.c

run:
	./bin/tetris
