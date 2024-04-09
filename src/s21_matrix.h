#ifndef S21_MATRIX_H_
#define S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPS 1e-7

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

enum result_code { OK, ERROR_INCORRECT, ERROR_CALCULATION };

/**
 * @brief Создает матрицу. Результат операции записывается в матрицу result.
 * @param rows - количество строк
 * @param columns - количество столбцов
 * @param result - указатель на матрицу
 * @return 0 - успех, 1/2 - ошибка
 */
int s21_create_matrix(int rows, int columns, matrix_t *result);

/**
 * @brief Удаляет матрицу
 * @param A - указатель на матрицу
 */
void s21_remove_matrix(matrix_t *A);

/**
 * @brief Сравнение матриц. Две матрицы A, B совпадают |A = B|, если совпадают
 * их размеры и соответствующие элементы равны, то есть при всех i, j A(i,j) =
 * B(i,j). Сравнение должно происходить вплоть до седьмого знака после запятой
 * включительно.
 * @param A - указатель на матрицу A
 * @param B - указатель на матрицу B
 * @return 0 - успех, 1/2 - ошибка
 */
int s21_eq_matrix(matrix_t *A, matrix_t *B);

/**
 * @brief Сложение матрицы A и B. Результат операции записывается в матрицу
 * result. Суммой двух матриц A = m × n и B = m × n одинаковых размеров
 * называется матрица C = m × n = A + B тех же размеров, элементы которой
 * определяются равенствами C(i,j) = A(i,j) + B(i,j).
 * @param A - указатель на матрицу A (слагаемое)
 * @param B - указатель на матрицу B (слагаемое)
 * @param result - указатель на матрицу result (сумма)
 * @return 0 - успех, 1/2 - ошибка
 */
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/**
 * @brief Вычитание из матрицы A матрицы B. Результат операции записывается в
 * матрицу result. Разностью двух матриц A = m × n и B = m × n одинаковых
 * размеров называется матрица C = m × n = A - B тех же размеров, элементы
 * которой определяются равенствами C(i,j) = A(i,j) - B(i,j).
 * @param A - указатель на матрицу A (уменьшаемое)
 * @param B - указатель на матрицу B (вычитаемое)
 * @param result - указатель на матрицу result (разность)
 * @return 0 - успех, 1/2 - ошибка
 */
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/**
 * @brief Умножение матрицы A на double-число. Результат операции записывается в
 * матрицу result. Произведением матрицы A = m × n на число λ называется матрица
 * B = m × n = λ × A, элементы которой определяются равенствами B = λ × A(i,j).
 * @param A - указатель на матрицу A (множитель)
 * @param number - double-число (множитель)
 * @param result - указатель на матрицу result (произведение)
 * @return 0 - успех, 1/2 - ошибка
 */
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

/**
 * @brief Умножение матрицы A на матрицу B. Результат операции записывается в
 * матрицу result. Произведением матрицы A = m × k на матрицу B = k × n
 * называется матрица C = m × n = A × B размера m × n, элементы которой
 * определяются равенством C(i,j) = A(i,1) × B(1,j) + A(i,2) × B(2,j) + … +
 * A(i,k) × B(k,j).
 * @param A - указатель на матрицу A (множитель)
 * @param B - указатель на матрицу B (множитель)
 * @param result - указатель на матрицу result (произведение)
 * @return 0 - успех, 1/2 - ошибка
 */
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/**
 * @brief Транспонирование матрицы. Результат операции записывается в матрицу.
 * Транспонирование матрицы А заключается в замене строк этой матрицы ее
 * столбцами с сохранением их номеров. result.
 * @param A - указатель на матрицу A
 * @param result - указатель на матрицу result
 * @return 0 - успех, 1/2 - ошибка
 */
int s21_transpose(matrix_t *A, matrix_t *result);

/**
 * @brief Минор матрицы и матрица алгебраических дополнений. Результат операции
 * записывается в матрицу result. Минором M(i,j) называется определитель
 * (n-1)-го порядка, полученный вычёркиванием из матрицы A i-й строки и j-го
 * столбца. Алгебраическим дополнением элемента матрицы является значение минора
 * умноженное на -1^(i+j).
 * @param A - указатель на матрицу A
 * @param result - указатель на матрицу result
 * @return 0 - успех, 1/2 - ошибка
 */
int s21_calc_complements(matrix_t *A, matrix_t *result);

/**
 * @brief Определитель матрицы. Результат операции записывается в
 * result. Определитель (детерминант) - это число, которое ставят в соответствие
 * каждой квадратной матрице и вычисляют из элементов по специальным формулам.
 * Tip: определитель может быть вычислен только для квадратной матрицы.
 * Определитель матрицы равен сумме произведений элементов строки (столбца) на
 * соответствующие алгебраические дополнения.
 * @param A - указатель на матрицу A
 * @param result - double-число
 * @return 0 - успех, 1/2 - ошибка
 */
int s21_determinant(matrix_t *A, double *result);

/**
 * @brief Обратная матрица (result) матрицы A. Результат операции записывается в
 * матрицу result. Матрицу A в степени -1 называют обратной к квадратной матрице
 * А, если произведение этих матриц равняется единичной матрице. Обратной
 * матрицы не существует, если определитель равен 0.
 * @param A - указатель на матрицу A
 * @param result - указатель на матрицу result
 * @return 0 - успех, 1/2 - ошибка
 */
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

/**
 * @briefЗаполнение матрицы числами double через scanf по индексам. Для отладки.
 * @param *dst матрица для заполнения
 */
void matrix_init(matrix_t *dst);

/**
 * @brief Вывод индексов матрицы
 * @param value
 */
void matrix_print(matrix_t value);

/**
 * @brief Проверка матрицы на NULL, rows <= 0, columns <= 0.
 * @param mtx
 * @return 0 - OK, 1 - ERROR_INCORRECT
 */
int check_matrix(matrix_t mtx);

/**
 * @brief Проверка чисел матрицы на inf и nan.
 * @param mtx
 * @return 0 - OK, 2 - ERROR_CALCULATION
 */
int check_numb_mtx(matrix_t mtx);

/**
 * @brief Проверка value_1.rows == value_2.rows и value_1.columns ==
 * value_2.columns.
 * @param value_1
 * @param value_2
 * @return 0 - OK, 2 - ERROR_CALCULATION
 */
int check_eq_size_matrix(matrix_t value_1, matrix_t value_2);

/**
 * @brief Проверка value_1.columns == value_2.rows.
 * @param value_1
 * @param value_2
 * @return 0 - OK, 1 - ERROR_INCORRECT
 */
int check_mult_size_matrix(matrix_t value_1, matrix_t value_2);

/**
 * @brief Проверка того, что матрица квадртная.
 * @param value
 * @return 0 - OK, 2 - ERROR_CALCULATION
 */
int check_square_matrix(matrix_t value);

/**
 * @brief Взятие минора из матрицы по номеру строки и столбца.
 * @param row № строки минора
 * @param column № колонки минора
 * @param A начальная матрица
 * @param *minor матрица миноров из А по row и column
 */
void get_minor(int row, int column, matrix_t A, matrix_t *minor);

#endif  // S21_MATRIX_H_