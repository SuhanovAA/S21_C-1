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

  return 0;
}