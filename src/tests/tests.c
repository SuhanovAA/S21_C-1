#include "tests.h"

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
  run_testcase(suite_calc_comp_matrix());
  run_testcase(suite_determinant_matrix());
  run_testcase(suite_inverse_matrix());

  return 0;
}