#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = OK;
  if (result == NULL || rows <= 0 || columns <= 0) {
    error = ERROR_INCORRECT;
  } else {
    double **matrix = (double **)calloc(rows, sizeof(double *));
    if (!matrix) {
      error = ERROR_CALCULATION;
    } else {
      int ptr = 0;
      for (; ptr < rows; ptr++) {
        matrix[ptr] = (double *)calloc(columns, sizeof(double));
        if (!matrix[ptr]) {
          error = ERROR_CALCULATION;
          break;
        };
      }
      if (error == OK) {
        result->matrix = matrix;
        result->columns = columns;
        result->rows = rows;
      } else {
        for (int i = 0; i < ptr; i++) {
          free(matrix[i]);
        }
        free(matrix);
      }
    }
  }
  return error;
}

void s21_remove_matrix(matrix_t *A) {
  if (check_matrix(*A) == OK) {
    for (int i = 0; i < A->rows; i++)
      if (A->matrix[i] != NULL) free(A->matrix[i]);
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int error = SUCCESS;
  if (check_matrix(*A) == ERROR_INCORRECT ||
      check_matrix(*B) == ERROR_INCORRECT ||
      check_eq_size_matrix(*A, *B) == ERROR_CALCULATION) {
    error = FAILURE;
  } else {
    for (int i = 0; i < A->rows && error == SUCCESS; i++) {
      for (int j = 0; j < A->columns && error == SUCCESS; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
          error = FAILURE;
        }
      }
    }
  }
  return error;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = (check_matrix(*A) && check_matrix(*B));
  if (error == OK) {
    if (check_eq_size_matrix(*A, *B) || check_numb_mtx(*A) ||
        check_numb_mtx(*B)) {
      error = ERROR_CALCULATION;
    }
  }
  if (error == OK) {
    error = s21_create_matrix(A->rows, A->columns, result);
    if (error == OK) {
      for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }

  return error;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = (check_matrix(*A) || check_matrix(*B));
  if (error == OK) {
    if (check_eq_size_matrix(*A, *B) || check_numb_mtx(*A) ||
        check_numb_mtx(*B))
      error = ERROR_CALCULATION;
  }
  if (error == OK) {
    error = s21_create_matrix(A->rows, A->columns, result);
    if (error == OK) {
      for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }

  return error;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = check_matrix(*A);
  if (error == OK) {
    if (result == NULL) {
      error = ERROR_INCORRECT;
    }
  }
  if (error == OK) {
    if (check_numb_mtx(*A) || isnan(number) || isinf(number)) {
      error = ERROR_CALCULATION;
    }
    if (error == OK) {
      error = s21_create_matrix(A->rows, A->columns, result);
      if (error == OK) {
        for (int i = 0; i < A->rows; i++)
          for (int j = 0; j < A->columns; j++)
            result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }

  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = (check_matrix(*A) || check_matrix(*B) || result == NULL);
  if (error == OK) {
    if (A->columns != B->rows) {
      error = ERROR_CALCULATION;
    } else {
      double num = 0.0;
      error = s21_create_matrix(A->rows, B->columns, result);
      if (error == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < B->columns; j++) {
            for (int k = 0; k < A->columns; k++) {
              num += A->matrix[i][k] * B->matrix[k][j];
            }
            result->matrix[i][j] = num;
            num = 0.0;
          }
        }
      }
    }
  }

  return error;
}
int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = OK;
  error = (check_matrix(*A) || result == NULL);
  if (error == OK) {
    error = s21_create_matrix(A->columns, A->rows, result);
    if (error == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    }
  }
  return error;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = OK;
  if (check_matrix(*A) != OK || result == NULL) {
    error = ERROR_INCORRECT;
  } else if (check_square_matrix(*A) != OK || check_numb_mtx(*A) != OK) {
    error = ERROR_CALCULATION;
  } else {
    error = s21_create_matrix(A->rows, A->rows, result);
    if (error == OK) {
      if (A->rows == 1) {
        result->matrix[0][0] = A->matrix[0][0];
      } else {
        double det_minor = 0.0;
        for (int i = 0; i < A->rows && error == OK; i++) {
          for (int j = 0; j < A->columns && error == OK; j++) {
            matrix_t minor;
            s21_create_matrix(A->rows - 1, A->rows - 1, &minor);
            error = check_matrix(minor);
            if (error == OK) {
              get_minor(i, j, *A, &minor);
              error = s21_determinant(&minor, &det_minor);
              if (error == OK) {
                result->matrix[i][j] = det_minor * ((i + j) % 2 == 0 ? 1 : -1);
              }
              s21_remove_matrix(&minor);
              det_minor = 0.0;
            }
          }
        }
      }
    }
  }

  return error;
}
int s21_determinant(matrix_t *A, double *result) {
  int error = check_matrix(*A);
  if (error == OK) {
    if (check_square_matrix(*A) != OK || check_numb_mtx(*A) != OK ||
        result == NULL) {
      error = ERROR_CALCULATION;
    }
  }
  if (error == OK) {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      double det_minor = 0.0;
      for (int i = 0; i < A->columns && error == OK; i++) {
        matrix_t minor;
        error = s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
        if (error == OK) {
          get_minor(0, i, *A, &minor);
          error = check_matrix(minor);
          if (error == OK) {
            error = s21_determinant(&minor, &det_minor);
            if (error == OK) {
              *result += A->matrix[0][i] * det_minor * (i % 2 == 0 ? 1 : -1);
            }
            s21_remove_matrix(&minor);
            det_minor = 0.0;
          }
        }
      }
    }
  }

  return error;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = OK;
  double det = 0.;
  error = s21_determinant(A, &det);
  if (error == OK && result != NULL) {
    if (det != 0) {
      if (A->rows == 1) {
        error = s21_create_matrix(1, 1, result);
        if (error == OK) result->matrix[0][0] = 1 / A->matrix[0][0];
      } else {
        matrix_t minor_inverse;
        error = s21_calc_complements(A, &minor_inverse);
        if (error == OK) {
          matrix_t minor_inverse_t;
          error = s21_transpose(&minor_inverse, &minor_inverse_t);
          if (error == OK) {
            error = s21_mult_number(&minor_inverse_t, 1 / det, result);
          }
          s21_remove_matrix(&minor_inverse_t);
        }
        s21_remove_matrix(&minor_inverse);
      }

    } else {
      error = ERROR_CALCULATION;  // det == 0
    }
  }
  return error;
}

int check_matrix(matrix_t mtx) {
  int result = OK;
  if (mtx.matrix == NULL || mtx.rows <= 0 || mtx.columns <= 0) {
    result = ERROR_INCORRECT;
  }
  return result;
}

int check_numb_mtx(matrix_t mtx) {
  int result = OK;
  for (int i = 0; i < mtx.rows && result == OK; i++)
    for (int j = 0; j < mtx.columns && result == OK; j++)
      if (isinf(mtx.matrix[i][j]) || isnan(mtx.matrix[i][j]))
        result = ERROR_CALCULATION;
  return result;
}

int check_eq_size_matrix(matrix_t value_1, matrix_t value_2) {
  int result = OK;
  if (value_1.rows != value_2.rows || value_1.columns != value_2.columns)
    result = ERROR_CALCULATION;
  return result;
}

int check_square_matrix(matrix_t value) {
  int result = OK;
  if (value.rows != value.columns) result = ERROR_CALCULATION;
  return result;
}

void get_minor(int row, int column, matrix_t A, matrix_t *minor) {
  int row_minor = 0, col_minor = 0;
  for (int i = 0; i < A.rows; i++) {
    col_minor = 0;
    if (i != row) {
      for (int j = 0; j < A.columns; j++) {
        if (j != column) {
          minor->matrix[row_minor][col_minor] = A.matrix[i][j];
          col_minor++;
        }
      }
      row_minor++;
    }
  }
}

void fill_matrix(matrix_t *A, double start_value, double delta) {
  if (A != NULL && A->matrix != NULL) {
    double value = start_value;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        A->matrix[i][j] = value;
        value += delta;
      }
    }
  }
}