#ifndef TESTS_MATRIX
#define TESTS_MATRIX

#include <check.h>

#include "../s21_matrix.h"

Suite* suite_eq_matrix(void);

void fill_matrix(matrix_t* dst, double min, double max);
void run_testcase(Suite* testcase);

#endif  // TESTS_MATRIX