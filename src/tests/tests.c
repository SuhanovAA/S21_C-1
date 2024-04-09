#include "tests.h"

void fill_matrix(matrix_t* dst, double min, double max) {
  double num = (min + max) / 2;
  for (int i = 0; i < dst->rows; i++)
    for (int j = 0; j < dst->columns; j++)
      dst->matrix[i][j] = num * (double)(i + j);
}

void s21_initialize_matrix(matrix_t* A, double start_value, double delta) {
  if (A != NULL && A->matrix != NULL) {
    double value = start_value;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        A->matrix[i][j] = value;
        value += delta;
      }
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
  run_testcase(suite_eq_matrix());           // OK
  run_testcase(suite_create_matrix());       // OK
  run_testcase(suite_remove_matrix());       // OK
  run_testcase(suite_sum_matrix());          // OK
  run_testcase(suite_sub_matrix());          // OK
  run_testcase(suite_mult_number_matrix());  // OK
  run_testcase(suite_mult_matrix());         // OK
  run_testcase(suite_transpose_matrix());
  run_testcase(suite_calc_comp_matrix());
  run_testcase(suite_determinant_matrix());
  run_testcase(suite_inverse_matrix());

  return 0;
}