#include "tests.h"

START_TEST(eq_matrix_test_0) {
  matrix_t A, B;
  s21_create_matrix(3, 2, &A), s21_create_matrix(3, 2, &B);
  fill_matrix(&A, 2, 3.55), fill_matrix(&B, 2, 3.55);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A), s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_test_1) {
  matrix_t A, B;
  s21_create_matrix(3, 2, &A), s21_create_matrix(3, 2, &B);
  fill_matrix(&A, -3.12123, 2.854), fill_matrix(&B, 0, 8.888);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A), s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_test_2) {
  matrix_t A, B;
  s21_create_matrix(3, 2, &A), s21_create_matrix(1, 1, &B);
  fill_matrix(&A, -3.12123, 2.854), fill_matrix(&B, 0, 8.888);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A), s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_test_3) {
  matrix_t A, B;
  s21_create_matrix(1, 1, &A), s21_create_matrix(1, 1, &B);
  A.matrix[0][0] = 1e2;
  B.matrix[0][0] = 1e2;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A), s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_test_4) {
  matrix_t A, B;
  s21_create_matrix(1, 2, &A), s21_create_matrix(1, 1, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A), s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_test_5) {
  matrix_t A, B;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
}
END_TEST

START_TEST(eq_matrix_test_6) {
  matrix_t A = {}, B = {};
  s21_create_matrix(5, 5, &A), s21_create_matrix(5, 5, &B);
  fill_matrix(&A, 21, 1), fill_matrix(&B, 42, 1);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A), s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_test_7) {
  matrix_t A = {}, B = {};
  s21_create_matrix(5, 5, &A);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
}
END_TEST

Suite* suite_eq_matrix(void) {
  Suite* s = suite_create("\033[42m-=S21_EQ_MATRIX=-\033[0m");
  TCase* tc = tcase_create("case_eq_matrix");

  tcase_add_test(tc, eq_matrix_test_0);
  tcase_add_test(tc, eq_matrix_test_1);
  tcase_add_test(tc, eq_matrix_test_2);
  tcase_add_test(tc, eq_matrix_test_3);
  tcase_add_test(tc, eq_matrix_test_4);
  tcase_add_test(tc, eq_matrix_test_5);
  tcase_add_test(tc, eq_matrix_test_6);
  tcase_add_test(tc, eq_matrix_test_7);

  suite_add_tcase(s, tc);
  return s;
}