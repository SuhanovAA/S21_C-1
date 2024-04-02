#include "tests.h"

void fill_matrix(matrix_t* dst, double min, double max) {
  double num = (min + max) / 2;
  for (int i = 0; i < dst->rows; i++)
    for (int j = 0; j < dst->columns; j++)
      dst->matrix[i][j] = num * (double)(i + j);
}

void copy_matrix(matrix_t value, matrix_t* dst) {
  for (int i = 0; i < value.rows; i++)
    for (int j = 0; j < value.columns; j++)
      dst->matrix[i][j] = value.matrix[i][j];
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
  run_testcase(suite_create_matrix());
  run_testcase(suite_remove_matrix());
  run_testcase(suite_sum_matrix());
  run_testcase(suite_sub_matrix());
  run_testcase(suite_mult_number_matrix());
  run_testcase(suite_mult_matrix());
  run_testcase(suite_transpose_matrix());

  return 0;
}