#include "tests.h"

START_TEST(inverse_matrix_test_0) {
  matrix_t A = {};
  matrix_t result = {};
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), ERROR_INCORRECT);
}
END_TEST

START_TEST(inverse_matrix_test_1) {
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(3, 3, &A);
  fill_matrix(&A, -1, 3);
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), ERROR_CALCULATION);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_test_2) {
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(5, 3, &A);
  fill_matrix(&A, -2.5, 3.12);
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), ERROR_CALCULATION);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_test_3) {
  matrix_t A = {}, result = {}, eq_matrix = {};
  s21_create_matrix(1, 1, &A), s21_create_matrix(1, 1, &eq_matrix);
  A.matrix[0][0] = 21;
  eq_matrix.matrix[0][0] = 1.0 / 21.0;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A), s21_remove_matrix(&result),
      s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(inverse_matrix_test_4) {
  matrix_t A = {}, result = {}, eq_matrix = {};
  s21_create_matrix(3, 3, &A), s21_create_matrix(3, 3, &eq_matrix);
  A.matrix[0][0] = 2, A.matrix[0][1] = 5, A.matrix[0][2] = 7;
  A.matrix[1][0] = 6, A.matrix[1][1] = 3, A.matrix[1][2] = 4;
  A.matrix[2][0] = 5, A.matrix[2][1] = -2, A.matrix[2][2] = -3;
  eq_matrix.matrix[0][0] = 1, eq_matrix.matrix[0][1] = -1,
  eq_matrix.matrix[0][2] = 1;
  eq_matrix.matrix[1][0] = -38, eq_matrix.matrix[1][1] = 41,
  eq_matrix.matrix[1][2] = -34;
  eq_matrix.matrix[2][0] = 27, eq_matrix.matrix[2][1] = -29,
  eq_matrix.matrix[2][2] = 24;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A), s21_remove_matrix(&result),
      s21_remove_matrix(&eq_matrix);
}
END_TEST

Suite* suite_inverse_matrix(void) {
  Suite* s = suite_create("\033[42m-=S21_INVERSE_MATRIX=-\033[0m");
  TCase* tc = tcase_create("case_inverse_matrix");

  tcase_add_test(tc, inverse_matrix_test_0);
  tcase_add_test(tc, inverse_matrix_test_1);
  tcase_add_test(tc, inverse_matrix_test_2);
  tcase_add_test(tc, inverse_matrix_test_3);
  tcase_add_test(tc, inverse_matrix_test_4);

  suite_add_tcase(s, tc);
  return s;
}