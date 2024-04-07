#include "tests.h"

START_TEST(sub_matrix_test_error_0) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A), s21_create_matrix(1, 1, &B);
  fill_matrix(&A, 0, 1), fill_matrix(&B, 0, 1);

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), ERROR_CALCULATION);
  s21_remove_matrix(&A), s21_remove_matrix(&B), s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_test_error_1) {
  matrix_t A, B, result;
  A.matrix = NULL;
  s21_create_matrix(1, 1, &B);
  fill_matrix(&A, 0, 1), fill_matrix(&B, 0, 1);

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), ERROR_INCORRECT);
  s21_remove_matrix(&A), s21_remove_matrix(&B), s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_test_0) {
  // 0.0000000 0.5000000
  // 0.5000000 1.0000000

  // 0.0000000 5.5000000
  // 5.5000000 11.0000000

  // 0.0000000 -5.0000000
  // -5.0000000 -10.0000000
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A), s21_create_matrix(2, 2, &B);
  fill_matrix(&A, 0, 1), fill_matrix(&B, 3, 8);

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  s21_remove_matrix(&A), s21_remove_matrix(&B), s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_test_1) {
  // 0.0000000 0.9344000 1.8688000
  // 0.9344000 1.8688000 2.8032000
  // 1.8688000 2.8032000 3.7376000

  // 0.0000000 4.9390000 9.8780000
  // 4.9390000 9.8780000 14.8170000
  // 9.8780000 14.8170000 19.7560000

  // 0.0000000 -4.0046000 -8.0092000
  // -4.0046000 -8.0092000 -12.0138000
  // -8.0092000 -12.0138000 -16.0184000
  matrix_t A, B, result;
  s21_create_matrix(3, 3, &A), s21_create_matrix(3, 3, &B);
  fill_matrix(&A, -3.2312, 5.1), fill_matrix(&B, -2.222, 12.1);

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  s21_remove_matrix(&A), s21_remove_matrix(&B), s21_remove_matrix(&result);
}
END_TEST

Suite* suite_sub_matrix(void) {
  Suite* s = suite_create("\033[42m-=S21_SUB_MATRIX=-\033[0m");
  TCase* tc = tcase_create("case_sub_matrix");

  tcase_add_test(tc, sub_matrix_test_error_0);
  tcase_add_test(tc, sub_matrix_test_error_1);
  tcase_add_test(tc, sub_matrix_test_0);
  tcase_add_test(tc, sub_matrix_test_1);

  suite_add_tcase(s, tc);
  return s;
}