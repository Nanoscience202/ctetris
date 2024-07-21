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

  int game_win_y = (LINES - 22) / 2;
  int game_win_x = (COLS - 22) / 2;
  WINDOW *game_win = newwin(22, 22, game_win_y, game_win_x);
  box(game_win, 0, 0);
  mvwprintw(game_win, 0, 9, "Play");
  wrefresh(game_win);

  WINDOW *hold_win = newwin(4, 12, game_win_y, game_win_x - 12);
  box(hold_win, 0, 0);
  mvwprintw(hold_win, 0, 4, "Hold");
  wrefresh(hold_win);

  WINDOW *next_win = newwin(10, 12, game_win_y, game_win_x + 22);
  box(next_win, 0, 0);
  mvwprintw(next_win, 0, 4, "Next");
  wrefresh(next_win);

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
  delwin(hold_win);
  delwin(next_win);
  quit();
}
