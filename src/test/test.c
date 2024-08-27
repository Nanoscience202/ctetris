#include "../blocks.h"
#include "../matrix/matrix.h"

int main(void) {
  Matrix m;

  m = block_get_shape(I);
  matrix_print(m);
  m = matrix_rotate_left(m);
  matrix_print(m);

  m = block_get_shape(L);
  matrix_print(m);
  m = matrix_rotate_left(m);
  matrix_print(m);

  return 0;
}
