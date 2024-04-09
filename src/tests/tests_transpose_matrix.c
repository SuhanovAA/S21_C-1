#include "tests.h"

START_TEST(transpose_matrix_test_0) {
  matrix_t A, result;
  s21_create_matrix(0, 6, &A);
  fill_matrix(&A, 0, 1);

  ck_assert_int_eq(s21_transpose(&A, &result), ERROR_INCORRECT);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(transpose_matrix_test_1) {
  matrix_t A = {};
  matrix_t result = {};
  ck_assert_int_eq(s21_transpose(&A, &result), ERROR_INCORRECT);
}
END_TEST

START_TEST(transpose_matrix_test_2) {
  matrix_t A, result;
  s21_create_matrix(3, 2, &A);
  fill_matrix(&A, 0, 1);
  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  s21_remove_matrix(&A), s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_matrix_test_3) {
  matrix_t A = {}, result = {};
  s21_create_matrix(3, 2, &A);
  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 3);
  s21_remove_matrix(&A), s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_matrix_test_4) {
  matrix_t A = {}, result = {};
  s21_create_matrix(2, 3, &A);
  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 2);
  s21_remove_matrix(&A), s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_matrix_test_5) {
  matrix_t A = {}, result = {}, eq_matrix = {};
  s21_create_matrix(3, 2, &A), s21_create_matrix(2, 3, &eq_matrix);
  A.matrix[0][0] = 1, A.matrix[0][1] = 4;
  A.matrix[1][0] = 2, A.matrix[1][1] = 5;
  A.matrix[2][0] = 3, A.matrix[2][1] = 6;
  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  eq_matrix.matrix[0][0] = 1, eq_matrix.matrix[0][1] = 2,
  eq_matrix.matrix[0][2] = 3;
  eq_matrix.matrix[1][0] = 4, eq_matrix.matrix[1][1] = 5,
  eq_matrix.matrix[1][2] = 6;
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 3);
  s21_remove_matrix(&A), s21_remove_matrix(&eq_matrix),
      s21_remove_matrix(&result);
}
END_TEST

Suite* suite_transpose_matrix(void) {
  Suite* s = suite_create("\033[42m-=S21_TRANSPOSE_MATRIX=-\033[0m");
  TCase* tc = tcase_create("case_transpose_matrix");

  tcase_add_test(tc, transpose_matrix_test_0);
  tcase_add_test(tc, transpose_matrix_test_1);
  tcase_add_test(tc, transpose_matrix_test_2);
  tcase_add_test(tc, transpose_matrix_test_3);
  tcase_add_test(tc, transpose_matrix_test_4);
  tcase_add_test(tc, transpose_matrix_test_5);

  suite_add_tcase(s, tc);
  return s;
}