#ifndef GAME_H
#define GAME_H

#include "../blocks.h"
#include "../lib.h"
#include "../matrix/matrix.h"
#include "../settings.h"

#include <assert.h>
#include <ncurses.h>
#include <time.h>

void create_initial_queue(Block *queue) {
  int last_color = -1;

  for (int i = 0; i < 3; i++) {
    queue[i] = block_new(&last_color);
    queue[i].position.y = 3 * i + 1;
  }
}

void update_next_window(WINDOW *next_win, Block queue[]) {
  for (int i = 0; i < 3; i++) {
    block_wprint(next_win, queue[i]);
  }
  wrefresh(next_win);
}

void update_current(WINDOW *next_win, WINDOW *game_win, Block *queue,
                    Block *current) {
  // things related to queue window
  attrset(A_NORMAL);
  for (int i = 1; i < 9; i++) {
    mvwprintw(next_win, i, 1, "          ");
  }

  *current = queue[0];
  current->position.x = (22 - current->shape.n) / 2;
  current->position.y = 1;

  queue[0] = queue[1];
  queue[0].position.y -= 3;

  queue[1] = queue[2];
  queue[1].position.y -= 3;

  int last_color = queue[1].color;

  queue[2] = block_new(&last_color);
  queue[2].position.y = 2 * 3 + 1;

  update_next_window(next_win, queue);
}

int get_placement(Matrix grid, Block current) {
  int offset_y = current.position.y;
  int offset_x = (current.position.x - 1) / 2;

  for (; offset_y < grid.m - current.shape.m + 1; offset_y++) {
    for (int i = 0; i < current.shape.m; i++) {
      for (int k = 0; k < current.shape.n; k++) {
        if (matrix_get(grid, i + offset_y, k + offset_x) != 0 &&
            matrix_get(current.shape, i, k) == 1) {
          return offset_y - 1;
        }
      }
    }
  }
  return offset_y - 1;
}

void place_block(Matrix *grid, Block current, int placement) {
  int offset_y = placement;
  int offset_x = (current.position.x - 1) / 2;

  assert(placement <= grid->m - current.shape.m);

  for (int i = 0; i < current.shape.m; i++) {
    for (int k = 0; k < current.shape.n; k++) {
      if (matrix_get(current.shape, i, k) == 1) {
        matrix_set(grid, i + offset_y, k + offset_x, current.color);
      }
    }
  }
}

void update_grid(Matrix *grid) {
  for (int front = 19, back = 19; front >= 0; front--) {
    bool is_full = true;

    for (int i = 0; i < grid->n; i++) {
      if (matrix_get(*grid, front, i) == 0) {
        is_full = false;
        break;
      }
    }

    if (!is_full) {
      for (int i = 0; i < grid->n; i++) {
        matrix_set(grid, back, i, matrix_get(*grid, front, i));
      }
      back--;
    }
  }
}

#endif
