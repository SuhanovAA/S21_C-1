#include "tests.h"

START_TEST(sub_matrix_test_0) {
  matrix_t A = {};
  matrix_t B = {};
  ck_assert_int_eq(s21_sub_matrix(&A, &B, NULL), ERROR_INCORRECT);
}
END_TEST

START_TEST(sub_matrix_test_1) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(5, 5, &B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), ERROR_CALCULATION);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix_test_2) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A), s21_create_matrix(2, 2, &B);
  fill_matrix(&A, 0, 1), fill_matrix(&B, 3, 8);

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  s21_remove_matrix(&A), s21_remove_matrix(&B), s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_test_3) {
  matrix_t A, B, result;
  s21_create_matrix(3, 3, &A), s21_create_matrix(3, 3, &B);
  fill_matrix(&A, -3.2312, 5.1), fill_matrix(&B, -2.222, 12.1);

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  s21_remove_matrix(&A), s21_remove_matrix(&B), s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_test_4) {
  matrix_t A = {}, B = {}, result = {};
  s21_create_matrix(5, 5, &A), s21_create_matrix(5, 5, &B);
  fill_matrix(&A, 1, 1), fill_matrix(&B, 1, 1);
  B.matrix[3][3] = INFINITY;
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), ERROR_CALCULATION);
  s21_remove_matrix(&A), s21_remove_matrix(&B), s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_test_5) {
  matrix_t A = {}, B = {}, result = {}, eq_matrix = {};
  s21_create_matrix(5, 5, &A), s21_create_matrix(5, 5, &B),
      s21_create_matrix(5, 5, &eq_matrix);
  fill_matrix(&A, 1, 1), fill_matrix(&B, 1, 1);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A), s21_remove_matrix(&B);
  s21_remove_matrix(&result), s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(sub_matrix_test_6) {
  matrix_t A = {}, B = {}, result = {}, eq_matrix = {};
  s21_create_matrix(3, 3, &A), s21_create_matrix(3, 3, &B),
      s21_create_matrix(3, 3, &eq_matrix);
  A.matrix[0][0] = 1, A.matrix[0][1] = 2, A.matrix[0][2] = 3;
  A.matrix[1][0] = 0, A.matrix[1][1] = 4, A.matrix[1][2] = 5;
  A.matrix[2][0] = 0, A.matrix[2][1] = 0, A.matrix[2][2] = 6;
  B.matrix[0][0] = 1, B.matrix[0][1] = 0, B.matrix[0][2] = 0;
  B.matrix[1][0] = 2, B.matrix[1][1] = 0, B.matrix[1][2] = 0;
  B.matrix[2][0] = 3, B.matrix[2][1] = 4, B.matrix[2][2] = 1;
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  eq_matrix.matrix[0][0] = 0, eq_matrix.matrix[0][1] = 2,
  eq_matrix.matrix[0][2] = 3;
  eq_matrix.matrix[1][0] = -2, eq_matrix.matrix[1][1] = 4,
  eq_matrix.matrix[1][2] = 5;
  eq_matrix.matrix[2][0] = -3, eq_matrix.matrix[2][1] = -4,
  eq_matrix.matrix[2][2] = 5;
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A), s21_remove_matrix(&B);
  s21_remove_matrix(&result), s21_remove_matrix(&eq_matrix);
}
END_TEST

Suite* suite_sub_matrix(void) {
  Suite* s = suite_create("\033[42m-=S21_SUB_MATRIX=-\033[0m");
  TCase* tc = tcase_create("case_sub_matrix");

  tcase_add_test(tc, sub_matrix_test_0);
  tcase_add_test(tc, sub_matrix_test_1);
  tcase_add_test(tc, sub_matrix_test_2);
  tcase_add_test(tc, sub_matrix_test_3);
  tcase_add_test(tc, sub_matrix_test_4);
  tcase_add_test(tc, sub_matrix_test_5);
  tcase_add_test(tc, sub_matrix_test_6);

  suite_add_tcase(s, tc);
  return s;
}