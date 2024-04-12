#include "tests.h"

START_TEST(mult_matrix_test_error_0) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A), s21_create_matrix(1, 1, &B);
  fill_matrix(&A, 0, 1), fill_matrix(&B, 0, 1);

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), ERROR_CALCULATION);
  s21_remove_matrix(&A), s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix_test_error_1) {
  matrix_t A, B, result;
  A.matrix = NULL;
  s21_create_matrix(1, 1, &B);
  fill_matrix(&A, 0, 1), fill_matrix(&B, 0, 1);

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), ERROR_INCORRECT);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix_test_0) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A), s21_create_matrix(2, 2, &B);
  fill_matrix(&A, 0, 1), fill_matrix(&B, 3, 8);

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), OK);
  s21_remove_matrix(&A), s21_remove_matrix(&B), s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_matrix_test_1) {
  matrix_t A, B, result;
  s21_create_matrix(3, 3, &A), s21_create_matrix(3, 3, &B);
  fill_matrix(&A, -3.2312, 5.1), fill_matrix(&B, -2.222, 12.1);

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), OK);
  s21_remove_matrix(&A), s21_remove_matrix(&B), s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_matrix_test_2) {
  matrix_t A, B, result;
  s21_create_matrix(3, 2, &A), s21_create_matrix(2, 3, &B);
  fill_matrix(&A, -3.1, 5.9), fill_matrix(&B, -2.6, 12.1);

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), OK);
  s21_remove_matrix(&A), s21_remove_matrix(&B), s21_remove_matrix(&result);
}
END_TEST

Suite* suite_mult_matrix(void) {
  Suite* s = suite_create("\033[42m-=S21_MULT_MATRIX=-\033[0m");
  TCase* tc = tcase_create("case_mult_matrix");

  tcase_add_test(tc, mult_matrix_test_error_0);
  tcase_add_test(tc, mult_matrix_test_error_1);
  tcase_add_test(tc, mult_matrix_test_0);
  tcase_add_test(tc, mult_matrix_test_1);
  tcase_add_test(tc, mult_matrix_test_2);

  suite_add_tcase(s, tc);
  return s;
}