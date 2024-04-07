#include "tests.h"

START_TEST(mult_number_matrix_test_error_0) {
  matrix_t A, result;
  double number = 1.0 / 0.0;
  s21_create_matrix(2, 2, &A);
  fill_matrix(&A, 0, 1);

  ck_assert_int_eq(s21_mult_number(&A, number, &result), ERROR_INCORRECT);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_number_matrix_test_error_1) {
  matrix_t A, result;
  double number = 12.328;
  A.matrix = NULL;
  fill_matrix(&A, 0, 1);

  ck_assert_int_eq(s21_mult_number(&A, number, &result), ERROR_INCORRECT);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_number_matrix_test_0) {
  matrix_t A, result;
  double number = 0.0;
  s21_create_matrix(2, 2, &A);
  fill_matrix(&A, 0, 1);

  ck_assert_int_eq(s21_mult_number(&A, number, &result), OK);
  s21_remove_matrix(&A), s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_number_matrix_test_1) {
  // 0.0000000 0.9344000 1.8688000
  // 0.9344000 1.8688000 2.8032000
  // 1.8688000 2.8032000 3.7376000

  // 3.213140

  // 0.0000000 3.0023580 6.0047160
  // 3.0023580 6.0047160 9.0070740
  // 6.0047160 9.0070740 12.0094321
  matrix_t A, result;
  double number = 3.21314;
  s21_create_matrix(3, 3, &A);
  fill_matrix(&A, -3.2312, 5.1);

  ck_assert_int_eq(s21_mult_number(&A, number, &result), OK);
  s21_remove_matrix(&A), s21_remove_matrix(&result);
}
END_TEST

Suite* suite_mult_number_matrix(void) {
  Suite* s = suite_create("\033[42m-=S21_MULT_NUMBER_MATRIX=-\033[0m");
  TCase* tc = tcase_create("case_mult_number_matrix");

  tcase_add_test(tc, mult_number_matrix_test_error_0);
  tcase_add_test(tc, mult_number_matrix_test_error_1);
  tcase_add_test(tc, mult_number_matrix_test_0);
  tcase_add_test(tc, mult_number_matrix_test_1);

  suite_add_tcase(s, tc);
  return s;
}