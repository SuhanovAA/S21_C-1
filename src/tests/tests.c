#include "tests.h"

void fill_matrix(matrix_t* dst, double min, double max) {
  double num = (min + max) / 2;
  for (int i = 0; i < dst->rows; i++) {
    for (int j = 0; j < dst->columns; j++) {
      dst->matrix[i][j] = num * (double)(i + j);
    }
  }
}

void run_testcase(Suite* testcase) {
  printf("\n");
  SRunner* sr = srunner_create(testcase);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}

int main(void) {
  run_testcase(suite_eq_matrix());

  return 0;
}