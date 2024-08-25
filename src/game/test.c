#include "../test/test.h"
#include "game.h"
#include <assert.h>

void test_placement(Matrix grid) {
  Block b_I = {
      .color = 1,
      .type = I,
      .position = {.x = 1, .y = 1},
      .shape = block_get_shape(I),
  };

  int res = get_placement(grid, b_I);
  assert_bool(res == 19, "placement");
}

void test_place_block_1(Matrix *grid) {
  Block b_I = {
      .color = 1,
      .type = I,
      .position = {.x = 1, .y = 1},
      .shape = block_get_shape(I),
  };
  int res = get_placement(*grid, b_I);
  assert(res == 19);

  place_block(grid, b_I, res);

  Matrix ans = matrix_new(20, 10);
  matrix_set(&ans, 19, 0, 1);
  matrix_set(&ans, 19, 1, 1);
  matrix_set(&ans, 19, 2, 1);
  matrix_set(&ans, 19, 3, 1);

  assert_matrix(test_matrix(*grid, ans, "place_block_1"));
}

void test_place_block_2() {
  int t[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  };
  Matrix grid = matrix_from(20, 10, t);

  Block b_T = {.color = 1,
               .type = T,
               .position = {.x = 3, .y = 1},
               .shape = block_get_shape(T)};

  int res = get_placement(grid, b_T);

  assert(res == 18);
  place_block(&grid, b_T, res);

  int a[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
  };
  Matrix ans = matrix_from(20, 10, a);
  assert_matrix(test_matrix(ans, grid, "place_block_2"));
}

void test_place_block_3(Matrix *grid) {
  Block b_J = {
      .color = 2,
      .type = J,
      .position = {.x = 11, .y = 3},
      .shape = block_get_shape(J),
  };
  int placement = get_placement(*grid, b_J);
  assert(placement == 18);

  place_block(grid, b_J, placement);

  int a[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 1, 1, 1, 0, 2, 2, 2, 0, 0,
  };
  Matrix ans = matrix_from(20, 10, a);

  Result res = test_matrix(ans, *grid, "place_block_3");
  assert_matrix(res);
}

void test_place_block_above_1(Matrix *grid) {
  Block b_O = {.color = 3,
               .type = O,
               .position = {.x = 3, .y = 1},
               .shape = block_get_shape(O)};

  int placement = get_placement(*grid, b_O);
  assert(placement == 17);

  place_block(grid, b_O, placement);

  int a[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0,
      0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 2, 0, 0, 0, 0, 1, 1, 1, 1, 0, 2, 2, 2, 0, 0,
  };

  Matrix ans = matrix_from(20, 10, a);

  Result res = test_matrix(ans, *grid, "place_block_above_1");
  assert_matrix(res);
}

void test_place_block_above_2(Matrix *grid) {
  Block b_Z = {
      .color = 4,
      .type = Z,
      .position = {.x = 7 * 2 + 1, .y = 1},
      .shape = block_get_shape(Z),
  };

  int placement = get_placement(*grid, b_Z);
  assert(placement == 18);

  place_block(grid, b_Z, placement);

  int a[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0,
      0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 2, 0, 4, 4, 0, 1, 1, 1, 1, 0, 2, 2, 2, 4, 4,
  };

  Matrix ans = matrix_from(20, 10, a);
  assert_matrix(test_matrix(*grid, ans, "place_block_above_2"));
}

void test_rotate() {
  Block b_T = {.color = 1,
               .type = T,
               .position = {.x = 1, .y = 1},
               .shape = block_get_shape(T)};

  Matrix left = matrix_rotate_left(b_T.shape);

  int expected_left[] = {1, 0, 1, 1, 1, 0};
  assert_matrix(
      test_matrix(left, matrix_from(3, 2, expected_left), "rotate left"));

  Matrix right = matrix_rotate_right(b_T.shape);
  int expected_right[] = {0, 1, 1, 1, 0, 1};

  assert_matrix(
      test_matrix(right, matrix_from(3, 2, expected_right), "rotate right"));
}

void test_place_block_above_3(Matrix *grid) {
  Block b_T = {.color = 5,
               .type = T,
               .position = {.x = 3 * 2 + 1, .y = 1},
               .shape = block_get_shape(T)};

  b_T.shape = matrix_rotate_right(b_T.shape);

  int placement = get_placement(*grid, b_T);
  assert(placement == 17);

  place_block(grid, b_T, placement);

  int a[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 5,
      0, 0, 0, 0, 0, 0, 3, 3, 5, 5, 2, 0, 4, 4, 0, 1, 1, 1, 1, 5, 2, 2, 2, 4, 4,
  };

  assert_matrix(
      test_matrix(*grid, matrix_from(20, 10, a), "rotate right then place"));
}

int main(void) {
  Matrix grid = matrix_new(20, 10);

  test_placement(grid);
  test_place_block_1(&grid);
  test_place_block_2();
  test_place_block_3(&grid);
  test_place_block_above_1(&grid);
  test_place_block_above_2(&grid);
  test_rotate();
  test_place_block_above_3(&grid);

  matrix_print(grid);

  return 0;
}
