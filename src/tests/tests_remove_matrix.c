#include "tests.h"

START_TEST(remove_matrix_test_0) {
  matrix_t A;
  s21_create_matrix(1, 1, &A);
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
}
END_TEST

START_TEST(remove_matrix_test_1) {
  matrix_t A = {};
  s21_create_matrix(5, 5, &A);
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
}
END_TEST

START_TEST(remove_matrix_test_2) {
  matrix_t A = {};
  s21_remove_matrix(&A);
  ck_assert_int_eq(1, 1);
}
END_TEST

Suite* suite_remove_matrix(void) {
  Suite* s = suite_create("\033[42m-=S21_REMOVE_MATRIX=-\033[0m");
  TCase* tc = tcase_create("case_remove_matrix");

  tcase_add_test(tc, remove_matrix_test_0);
  tcase_add_test(tc, remove_matrix_test_1);
  tcase_add_test(tc, remove_matrix_test_2);

  suite_add_tcase(s, tc);
  return s;
}