#include "tests.h"

START_TEST(determinant_matrix_test_0) {
  matrix_t A = {};
  double det = 0;
  ck_assert_int_eq(s21_determinant(&A, &det), ERROR_INCORRECT);
}
END_TEST

START_TEST(determinant_matrix_test_1) {
  matrix_t A = {};
  double det = 0;
  s21_create_matrix(3, 2, &A);
  fill_matrix(&A, 1, 1);
  ck_assert_int_eq(s21_determinant(&A, &det), ERROR_CALCULATION);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_matrix_test_2) {
  matrix_t A = {};
  double det = 0;
  s21_create_matrix(3, 3, &A);
  fill_matrix(&A, 1, 1);
  ck_assert_int_eq(s21_determinant(&A, &det), OK);
  ck_assert_double_eq(det, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_matrix_test_3) {
  matrix_t A = {};
  double det = 0;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 21;
  ck_assert_int_eq(s21_determinant(&A, &det), OK);
  ck_assert_double_eq(det, 21);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_matrix_test_4) {
  const int size = 5;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) m.matrix[i][j] = j;
  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 0, 1e-6);
  ck_assert_int_eq(code, OK);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant_matrix_test_5) {
  const int size = 4;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) m.matrix[i][j] = j + i;
  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 0, 1e-6);
  ck_assert_int_eq(code, OK);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(determinant_matrix_test_6) {
  const int size = 5;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][1] = 6, m.matrix[0][2] = -2;
  m.matrix[0][3] = -1, m.matrix[0][4] = 5;
  m.matrix[1][3] = -9, m.matrix[1][4] = -7;
  m.matrix[2][1] = 15, m.matrix[2][2] = 35;
  m.matrix[3][1] = -1, m.matrix[3][2] = -11;
  m.matrix[3][3] = -2, m.matrix[3][4] = 1;
  m.matrix[4][0] = -2, m.matrix[4][1] = -2;
  m.matrix[4][2] = 3, m.matrix[4][4] = -2;
  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 2480, 1e-6);
  ck_assert_int_eq(code, OK);
  s21_remove_matrix(&m);
}
END_TEST

Suite* suite_determinant_matrix(void) {
  Suite* s = suite_create("\033[42m-=S21_DETERMINANT_MATRIX=-\033[0m");
  TCase* tc = tcase_create("case_determinant_matrix");

  tcase_add_test(tc, determinant_matrix_test_0);
  tcase_add_test(tc, determinant_matrix_test_1);
  tcase_add_test(tc, determinant_matrix_test_2);
  tcase_add_test(tc, determinant_matrix_test_3);
  tcase_add_test(tc, determinant_matrix_test_4);
  tcase_add_test(tc, determinant_matrix_test_5);
  tcase_add_test(tc, determinant_matrix_test_6);

  suite_add_tcase(s, tc);
  return s;
}