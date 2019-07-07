#ifndef _MATRIX_H
#define _MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1.0e-8

typedef struct {
    int row;
    int col;
    double **main;
} matrix;

int mat_alloc(matrix *self, int row, int col);

matrix mat_new(int row, int col);

void mat_free(matrix *self);

void mat_print(matrix *self);

int mat_copy(matrix *copy, matrix origin);

int mat_add(matrix *ans, matrix first, matrix second);

int mat_sub(matrix *ans, matrix first, matrix second);

int mat_mul(matrix *ans, matrix first, matrix second);

int mat_muls(matrix *ans, matrix origin, double c);

int mat_trans(matrix *ans, matrix origin);

int mat_unit(matrix *self);

int mat_compare(matrix first, matrix second);

int mat_solve(matrix *x, matrix a, matrix b);

int mat_inverse(matrix *s, matrix a);

#endif
