#include "tests.h"

START_TEST(eq_matrix_test_0) {
  matrix_t A, B;

  s21_create_matrix(3, 2, &A), s21_create_matrix(3, 2, &B);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = (double)i;
      B.matrix[i][j] = (double)i;
    }
  }

  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);

  s21_remove_matrix(&A), s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_test_1) {
  matrix_t A, B;
  double n = 0.322;

  s21_create_matrix(3, 2, &A), s21_create_matrix(3, 2, &B);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = (double)i;
      B.matrix[i][j] = n + (double)i;
    }
  }

  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);

  s21_remove_matrix(&A), s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_test_2) {
  matrix_t A, B;

  s21_create_matrix(3, 2, &A), s21_create_matrix(1, 1, &B);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = (double)(i * j);
    }
  }
  B.matrix[0][0] = 1e-1;

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

Suite* suite_eq_matrix(void) {
  Suite* s = suite_create("\033[42m-=S21_EQ_MATRIX=-\033[0m");
  TCase* tc1 = tcase_create("case_eq_matrix");

  tcase_add_test(tc1, eq_matrix_test_0);  // SUCCESS
  tcase_add_test(tc1, eq_matrix_test_1);  // FAILURE
  tcase_add_test(tc1, eq_matrix_test_2);  // FAILURE
  tcase_add_test(tc1, eq_matrix_test_3);  // SUCCESS

  suite_add_tcase(s, tc1);
  return s;
}