#include "../test/test.h"
#include "matrix.h"

void matrix_test() {
  Matrix A = matrix_new(2, 2);
  matrix_set(&A, 0, 0, 1);
  matrix_set(&A, 0, 1, 2);
  matrix_set(&A, 1, 0, 3);
  matrix_set(&A, 1, 1, 4);

  int a[] = {1, 2, 3, 4};
  assert_matrix(test_matrix(A, matrix_from(2, 2, a), "test_from_and_set_1"));

  Matrix B = matrix_new(2, 3);
  matrix_set(&B, 0, 0, 1);
  matrix_set(&B, 0, 1, 2);
  matrix_set(&B, 0, 2, 3);
  matrix_set(&B, 1, 0, 4);
  matrix_set(&B, 1, 1, 5);
  matrix_set(&B, 1, 2, 6);

  Matrix C = matrix_mul(A, B);
  Matrix D = matrix_transpose(C);

  matrix_print(A);
  matrix_print(B);
  matrix_print(C);
  matrix_print(D);

  int arr[] = {0, 1, 0, 1, 1, 1};

  Matrix E = matrix_from(2, 3, arr);
  matrix_print(E);
}

int main(void) {
  matrix_test();
  return 0;
}
