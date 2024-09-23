#ifndef GAME_H
#define GAME_H

#include "../blocks.h"
#include "../lib.h"
#include "../matrix/matrix.h"
#include "../settings.h"

#include <assert.h>
#include <ncurses.h>

enum Action { MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT, ROTATE_LEFT, ROTATE_RIGHT };

void create_initial_queue(Block *queue) {
  int last_color = -1;

  for (int i = 0; i < 3; i++) {
    queue[i] = block_new(&last_color);
    queue[i].position.y = 3 * i + 1;
  }
}

// FIX: queue window block printing
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
  current->position.x = 5;
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

bool is_block_overlap(Matrix grid, Matrix shape, int offset_y, int offset_x) {
  for (int i = 0; i < shape.m; i++) {
    for (int k = 0; k < shape.n; k++) {
      if (matrix_get(shape, i, k) == 1 &&
          matrix_get(grid, i + offset_y, k + offset_x) != 0) {
        return true;
      }
    }
  }

  return false;
}

int get_placement(Matrix grid, Block current) {
  int offset_y = current.position.y;
  int offset_x = (current.position.x - 1) / 2;

  int i = current.shape.m - 1;
  for (; i > 0; i--) {
    bool has_square = false;

    for (int k = 0; k < current.shape.n; k++) {
      if (matrix_get(current.shape, i, k) == 1) {
        has_square = true;
        break;
      }
    }

    if (!has_square) {
      break;
    }
  }

  for (; offset_y < grid.m - (current.shape.m - i); offset_y++) {
    if (is_block_overlap(grid, current.shape, offset_y, offset_x)) {
      break;
    }
  }

  return offset_y - 1;
}

void place_block(Matrix *grid, Block current, int placement) {
  int offset_y = placement;
  int offset_x = (current.position.x - 1) / 2;

  for (int i = 0; i < current.shape.m; i++) {
    for (int k = 0; k < current.shape.n; k++) {
      if (matrix_get(current.shape, i, k) == 1) {
        matrix_set(grid, i + offset_y, k + offset_x, current.color);
      }
    }
  }
}

int update_grid(Matrix *grid) {
  int front = 19;
  int back = 19;

  for (; front >= 0; front--) {
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
  return back - front;
}

void handle_rotate_left(Matrix grid, Block *current) {
  Matrix standby = matrix_rotate_left(current->shape);

  int offset_y = current->position.y - 1;
  int offset_x = (current->position.x - 1) / 2;

  if (offset_x + standby.n >= grid.n) {
    offset_x = grid.n - standby.n;
  }

  if (!is_block_overlap(grid, standby, offset_y, offset_x)) {
    current->position.x = offset_x * 2 + 1;
    current->shape = standby;
  }
}

void rotate_right(Matrix grid, Block *current) {}

bool can_move_left(Matrix grid, Block current) {
  if (current.position.x < 2) {
    return false;
  }

  int offset_y = current.position.y - 1;
  int offset_x = (current.position.x - 1) / 2 - 1;

  return !is_block_overlap(grid, current.shape, offset_y, offset_x);
}

bool can_move_right(Matrix grid, Block current) {
  if (current.position.x + current.shape.n * 2 >= dim_game.width - 2) {
    return false;
  }

  int offset_y = current.position.y - 1;
  int offset_x = (current.position.x - 1) / 2 + 1;

  return !is_block_overlap(grid, current.shape, offset_y, offset_x);
}

// FIX:block printing
void dispatch(WINDOW *game_win, enum Action action, Block *current,
              Matrix grid) {
  block_wclear(game_win, *current);

  switch (action) {
  case MOVE_RIGHT:
    if (can_move_right(grid, *current)) {
      current->position.x += 2;
    }
    break;
  case MOVE_LEFT:
    if (can_move_left(grid, *current)) {
      current->position.x -= 2;
    }
    break;
  case MOVE_DOWN:
    current->position.y++;
    break;
  case ROTATE_LEFT:
    handle_rotate_left(grid, current);
    break;
  case ROTATE_RIGHT:
    current->shape = matrix_rotate_right(current->shape);
    break;
  }

  block_wprint(game_win, *current);
  wrefresh(game_win);
}

#endif
