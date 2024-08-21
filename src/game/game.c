
#include "game.h"

void print_instructions(WINDOW *win) {
  char *instructions[] = {
      "LEFT - move piece left", "RIGHT - move piece right",
      "DOWN - soft drop",       "SPACE - hard drop",
      "z - rotate left",        "x - rotate right",
      "c - swap hold",          "q - quit",
  };

  for (int i = 0; i < 8; i++) {
    mvwprintw(win, i + 1, (COLS - 22) / 2 - 12, instructions[i]);
  }
  wrefresh(win);
}

WINDOW *create_window_box(int height, int width, int y, int x, char word[]) {
  WINDOW *win = newwin(height, width, y, x);
  box(win, 0, 0);
  mvwprintw(win, 0, (width - strlen(word)) / 2, word);
  wrefresh(win);

  return win;
}

void print_game_win(WINDOW *game_win, Matrix grid) {
  for (int i = 0; i < grid.m; i++) {
    for (int k = 0; k < grid.n; k++) {
      wattrset(game_win, COLOR_PAIR(matrix_get(grid, i, k)));
      mvwprintw(game_win, i + 1, k * 2 + 1, "  ");
    }
  }
  wattrset(game_win, A_NORMAL);
  wrefresh(game_win);
}

void game(enum State *game_state) {
  WINDOW *win = newwin(0, 0, 0, 0);
  wclear(win);
  wrefresh(win);

  print_instructions(win);

  dim_game.y = (LINES - dim_game.height) / 2;
  dim_game.x = (COLS - dim_game.width) / 2;

  dim_hold.y = dim_game.y;
  dim_hold.x = dim_game.x - dim_hold.width;

  dim_next.y = dim_game.y;
  dim_next.x = dim_game.x + dim_game.width;

  WINDOW *game_win = create_window_box(dim_game.height, dim_game.width,
                                       dim_game.y, dim_game.x, "Play");
  WINDOW *hold_win = create_window_box(dim_hold.height, dim_hold.width,
                                       dim_hold.y, dim_hold.x, "Hold");

  WINDOW *next_win = create_window_box(dim_next.height, dim_next.width,
                                       dim_next.y, dim_next.x, "Next");

  Matrix grid = matrix_new(20, 10);

  Block queue[3];
  create_initial_queue(queue);

  int last_color = queue[2].color;
  Block current = block_new(&last_color);
  current.position.x = (dim_game.width - current.shape.n) / 2;

  update_next_window(next_win, queue);

  bool run = true;
  clock_t now, then;
  now = clock();

  while (run) {
    int ch = getch();

    switch (ch) {
    case 'q':
      run = false;
      break;
    case ' ':
      update_current(next_win, game_win, queue, &current);
      break;
    case KEY_LEFT:
      if (current.position.x > 1) {
        block_wclear(game_win, current);
        current.position.x -= 2;
        block_wprint(game_win, current);
        wrefresh(game_win);
      }
      break;
    case KEY_RIGHT:
      if (current.position.x + current.shape.n < dim_game.width - 4) {
        block_wclear(game_win, current);
        current.position.x += 2;
        block_wprint(game_win, current);
        wrefresh(game_win);
      }
      break;
    case KEY_DOWN:
      if (current.position.y + current.shape.m < dim_game.height - 1) {
        block_wclear(game_win, current);
        current.position.y++;
        block_wprint(game_win, current);
        wrefresh(game_win);
      }
      break;
    }

    then = clock();

    if ((then - now) / CLOCKS_PER_SEC >= 1 &&
        current.position.y + current.shape.m < dim_game.height - 1) {
      block_wclear(game_win, current);
      current.position.y++;
      block_wprint(game_win, current);
      wrefresh(game_win);

      now = then;
    }
  }

  delwin(win);
  delwin(game_win);
  delwin(hold_win);
  delwin(next_win);
  quit();
}
