#include "lib.h"

void print_instructions(WINDOW *win) {
  char *instructions[] = {
      "LEFT - move piece left", "RIGHT - move piece right",
      "DOWN - soft drop",       "SPACE - hard drop",
      "z - rotate left",        "x - rotate right",
      "c - swap hold",          "q - quit",
  };

  for (int i = 0; i < 8; i++) {
    mvwprintw(win, i + 1, 2, instructions[i]);
  }
  wrefresh(win);
}

void game(enum State *game_state) {
  WINDOW *win = newwin(0, 0, 0, 0);
  wclear(win);
  wrefresh(win);

  print_instructions(win);

  WINDOW *game_win = newwin(22, 22, (LINES - 20) / 2, (COLS - 20) / 2);
  box(game_win, 0, 0);
  wrefresh(game_win);

  bool run = true;
  while (run) {
    int ch = getch();

    switch (ch) {
    case 113:
      run = false;
      break;
    }
  }

  delwin(win);
  delwin(game_win);
  quit();
}
