#ifndef TESTS_MATRIX
#define TESTS_MATRIX

#include <check.h>
#include <stdio.h>

#include "../s21_matrix.h"

Suite* suite_eq_matrix(void);
Suite* suite_create_matrix(void);
Suite* suite_remove_matrix(void);
Suite* suite_sum_matrix(void);
Suite* suite_sub_matrix(void);
Suite* suite_mult_number_matrix(void);
Suite* suite_mult_matrix(void);
Suite* suite_transpose_matrix(void);
Suite* suite_calc_comp_matrix(void);
Suite* suite_determinant_matrix(void);
Suite* suite_inverse_matrix(void);

void run_testcase(Suite* testcase);

#endif  // TESTS_MATRIX