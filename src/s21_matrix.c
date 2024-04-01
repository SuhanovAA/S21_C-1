#include "s21_matrix.h"

int main(void) {
  int rows1, cols1, rows2, cols2;
  matrix_t temp1, temp2;

  scanf("%d %d", &rows1, &cols1);
  scanf("%d %d", &rows2, &cols2);

  s21_create_matrix(rows1, cols1, &temp1);
  s21_create_matrix(rows2, cols2, &temp2);

  matrix_init(&temp1);
  matrix_print(temp1);

  matrix_init(&temp2);
  matrix_print(temp2);

  printf("%d", s21_eq_matrix(&temp1, &temp2));

  s21_remove_matrix(&temp1);
  s21_remove_matrix(&temp2);

  return 0;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = OK;
  if (rows <= 0 || columns <= 0) {
    error = ERROR_INCORRECT;
  } else {
    result->columns = columns;
    result->rows = rows;
    result->matrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
      result->matrix[i] = (double *)malloc(columns * sizeof(double));
  }
  return error;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL && A->rows > 0 && A->columns > 0) {
    for (int i = 0; i < A->rows; i++) free(A->matrix[i]);
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result =
      ((check_matrix(*A) && check_matrix(*B)) && check_eq_matrix(*A, *B));
  if (result) {
    for (int i = 0; i < A->rows && result; i++) {
      for (int j = 0; j < A->columns && result; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) <= EPS) {
          result = SUCCESS;
        } else {
          result = FAILURE;
        }
      }
    }
  }
  return result;
}
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

void matrix_init(matrix_t *dst) {
  double num;
  for (int i = 0; i < dst->rows; i++) {
    for (int j = 0; j < dst->columns; j++) {
      printf("A[%d][%d] = ", i, j);
      scanf("%lf", &num);
      dst->matrix[i][j] = num;
      printf("\n");
    }
  }
}

void matrix_print(matrix_t value) {
  for (int i = 0; i < value.rows; i++) {
    for (int j = 0; j < value.columns; j++) {
      printf("%.7lf ", value.matrix[i][j]);
    }
    printf("\n");
  }
}

int check_matrix(matrix_t value) {
  int result = TRUE;
  if (value.matrix == NULL || !value.rows || !value.columns) result = FALSE;
  return result;
}

int check_eq_matrix(matrix_t value_1, matrix_t value_2) {
  int result = TRUE;
  if (value_1.rows != value_2.rows || value_1.columns != value_2.columns)
    result = FALSE;
  return result;
}