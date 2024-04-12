#include "tests.h"

START_TEST(create_matrix_test_0) {
  matrix_t A = {};
  ck_assert_int_eq(s21_create_matrix(5, 5, &A), OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_matrix_test_1) {
  ck_assert_int_eq(s21_create_matrix(5, 5, NULL), ERROR_INCORRECT);
}
END_TEST

START_TEST(create_matrix_test_2) {
  matrix_t A = {};
  ck_assert_int_eq(s21_create_matrix(5, 0, &A), ERROR_INCORRECT);
}
END_TEST

START_TEST(create_matrix_test_3) {
  matrix_t A = {};
  ck_assert_int_eq(s21_create_matrix(0, 5, &A), ERROR_INCORRECT);
}
END_TEST

START_TEST(create_matrix_test_4) {
  matrix_t A;
  ck_assert_int_eq(s21_create_matrix(-3, 3, &A), ERROR_INCORRECT);
}
END_TEST

START_TEST(create_matrix_test_5) {
  matrix_t A;
  ck_assert_int_eq(s21_create_matrix(0, 0, &A), ERROR_INCORRECT);
}
END_TEST

START_TEST(create_matrix_test_6) {
  matrix_t A = {};
  ck_assert_int_eq(s21_create_matrix(-3, 5, &A), ERROR_INCORRECT);
}
END_TEST

Suite* suite_create_matrix(void) {
  Suite* s = suite_create("\033[42m-=S21_CREATE_MATRIX=-\033[0m");
  TCase* tc = tcase_create("case_create_matrix");

  tcase_add_test(tc, create_matrix_test_0);
  tcase_add_test(tc, create_matrix_test_1);
  tcase_add_test(tc, create_matrix_test_2);
  tcase_add_test(tc, create_matrix_test_3);
  tcase_add_test(tc, create_matrix_test_4);
  tcase_add_test(tc, create_matrix_test_5);
  tcase_add_test(tc, create_matrix_test_6);

  suite_add_tcase(s, tc);
  return s;
}