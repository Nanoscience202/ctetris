#ifndef LIB_H
#define LIB_H

#include <cJSON.h>
#include <math.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

enum State { MENU, GAME, OVER };

void init() {
  initscr(); // init curses
  //
  if (COLS < 53) {
    endwin();
    fprintf(stderr, "Window size too small\n");
    fprintf(stderr, "Current: %i; required: 53\n", COLS);
    exit(1);
  }

  cbreak();              // don't wait for new line
  keypad(stdscr, true);  // enable arrow keys
  noecho();              // don't echo back inputs
  curs_set(0);           // hide cursor
  nodelay(stdscr, true); // getch is non-blocking
  clear();
  refresh();

  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_WHITE);
}

void quit() {
  clear();
  refresh();
  curs_set(1);
  endwin(); // ends curses
  exit(0);
}

#endif
