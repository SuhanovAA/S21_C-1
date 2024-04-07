#include "tests.h"

START_TEST(transpose_matrix_test_error_0) {
  matrix_t A, result;
  s21_create_matrix(0, 6, &A);
  fill_matrix(&A, 0, 1);

  ck_assert_int_eq(s21_transpose(&A, &result), ERROR_INCORRECT);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(transpose_matrix_test_0) {
  // 0.0000000 0.5000000
  // 0.5000000 1.0000000
  // 1.0000000 1.5000000

  // 0.0000000 0.5000000 1.0000000
  // 0.5000000 1.0000000 1.5000000
  matrix_t A, result;
  s21_create_matrix(3, 2, &A);
  fill_matrix(&A, 0, 1);

  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  s21_remove_matrix(&A), s21_remove_matrix(&result);
}
END_TEST

Suite* suite_transpose_matrix(void) {
  Suite* s = suite_create("\033[42m-=S21_TRANSPOSE_MATRIX=-\033[0m");
  TCase* tc = tcase_create("case_transpose_matrix");

  tcase_add_test(tc, transpose_matrix_test_error_0);
  tcase_add_test(tc, transpose_matrix_test_0);

  suite_add_tcase(s, tc);
  return s;
}