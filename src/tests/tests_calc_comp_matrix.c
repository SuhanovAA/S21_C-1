#include "tests.h"

START_TEST(ccm_matrix_test_0) {
  matrix_t A = {};
  s21_create_matrix(3, 3, &A);
  ck_assert_int_eq(s21_calc_complements(&A, NULL), ERROR_INCORRECT);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(ccm_matrix_test_1) {
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(1, 3, &A);
  fill_matrix(&A, -3.2, 2.54);
  ck_assert_int_eq(s21_calc_complements(&A, &result), ERROR_CALCULATION);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(ccm_matrix_test_2) {
  matrix_t A = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &eq_matrix);
  A.matrix[0][0] = 1, A.matrix[0][1] = 2, A.matrix[0][2] = 3;
  A.matrix[1][0] = 0, A.matrix[1][1] = 4, A.matrix[1][2] = 2;
  A.matrix[2][0] = 5, A.matrix[2][1] = 2, A.matrix[2][2] = 1;
  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  eq_matrix.matrix[0][0] = 0, eq_matrix.matrix[0][1] = 10,
  eq_matrix.matrix[0][2] = -20;
  eq_matrix.matrix[1][0] = 4, eq_matrix.matrix[1][1] = -14,
  eq_matrix.matrix[1][2] = 8;
  eq_matrix.matrix[2][0] = -8, eq_matrix.matrix[2][1] = -2,
  eq_matrix.matrix[2][2] = 4;
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

Suite* suite_calc_comp_matrix(void) {
  Suite* s = suite_create("\033[42m-=S21_CALC_COMP_MATRIX=-\033[0m");
  TCase* tc = tcase_create("case_calc_comp_matrix");

  tcase_add_test(tc, ccm_matrix_test_0);
  tcase_add_test(tc, ccm_matrix_test_1);
  tcase_add_test(tc, ccm_matrix_test_2);

  suite_add_tcase(s, tc);
  return s;
}