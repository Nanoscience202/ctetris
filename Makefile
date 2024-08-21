all: compile run

compile:
	mkdir -p bin && clang -std=c2x -o bin/tetris `pkgconf --libs --cflags ncurses libcjson` src/main.c -g

run:
	./bin/tetris

FILE?=src/test/test.c

test:
	mkdir -p bin\
		&& clang -std=c2x -o src/test/bin/test `pkgconf --libs --cflags ncurses libcjson` $(FILE) -g \
		&& ./src/test/bin/test


