#include "matrix.h"

int mat_alloc(matrix *self, int row, int col) {
    self->row = row;
    self->col = col;
    self->main = (double **) calloc(self->row, sizeof(double *));
    if (self->main == NULL) {
        return 1;
    } else {
        for (int i = 0; i < self->row; i++) {
            self->main[i] = (double *) calloc(self->col, sizeof(double));
            if (self->main[i] == NULL) {
                for (int j = i - 1; j >= 0; j--) {
                    free(self->main[i]);
                }
                return 1;
            }
        }
        return 0;
    }
}

matrix mat_new(int row, int col) {
    matrix new;
    mat_alloc(&new, row, col);
    return new;
}

void mat_free(matrix *self) {
    for (int i = 0; i < self->row; i++) {
        free(self->main[i]);
    }
    free(self->main);
}

void mat_print(matrix *self) {
    printf("[");
    for (int i = 0; i < self->row; i++) {
        if (i != 0) {
            printf(" ");
        }
        for (int j = 0; j < self->col; j++) {
            printf(" %11lf,", self->main[i][j]);
        }
        if (i != self->row - 1) {
            printf("\n");
        }
    }
    printf("]\n");
}

int mat_copy(matrix *copy, matrix origin) {
    if (copy->row == origin.row && copy->col == origin.col) {
        for (int i = 0; i < origin.row; i++) {
            for (int j = 0; j < origin.col; j++) {
                copy->main[i][j] = origin.main[i][j];
            }
        }
        return 0;
    } else {
        return 1;
    }
}

int mat_add(matrix *ans, matrix first, matrix second) {
    if (first.row == second.row && first.col == second.col) {
        for (int i = 0; i < first.row; i++) {
            for (int j = 0; j < first.col; j++) {
                ans->main[i][j] = first.main[i][j] + second.main[i][j];
            }
        }
        return 0;
    } else {
        return 1;
    }
}

int mat_sub(matrix *ans, matrix first, matrix second) {
    if (first.row == second.row && first.col == second.col) {
        for (int i = 0; i < first.row; i++) {
            for (int j = 0; j < first.col; j++) {
                ans->main[i][j] = first.main[i][j] - second.main[i][j];
            }
        }
        return 0;
    } else {
        return 1;
    }
}

int mat_mul(matrix *ans, matrix first, matrix second) {
    matrix tmp0;
    mat_alloc(&tmp0, first.row, first.col);
    mat_copy(&tmp0, first);
    matrix tmp1;
    mat_alloc(&tmp1, second.row, second.col);
    mat_copy(&tmp1, second);
    if (ans->row == first.row && first.col == second.row &&
        ans->col == second.col) {
        for (int i = 0; i < tmp0.row; i++) {
            for (int j = 0; j < tmp1.col; j++) {
                double sum = 0.0;
                for (int k = 0; k < tmp0.col; k++) {
                    sum += tmp0.main[i][k] * tmp1.main[k][j];
                }
                ans->main[i][j] = sum;
            }
        }
        return 0;
    } else {
        return 1;
    }
}

int mat_muls(matrix *ans, matrix origin, double c) {
    if (ans->row == origin.row && ans->col == origin.col) {
        for (int i = 0; i < origin.row; i++) {
            for (int j = 0; j < origin.col; j++) {
                double tmp = origin.main[i][j] * c;
                ans->main[i][j] = tmp;
            }
        }
        return 0;
    } else {
        return 1;
    }
}

int mat_trans(matrix *ans, matrix origin) {
    matrix tmp;
    mat_alloc(&tmp, origin.row, origin.col);
    mat_copy(&tmp, origin);

    if (ans->row == origin.col && ans->col == origin.row) {
        for (int i = 0; i < origin.row; i++) {
            for (int j = 0; j < origin.col; j++) {
                ans->main[i][j] = tmp.main[j][i];
            }
        }
        return 0;
    } else {
        return 1;
    }
}

int mat_unit(matrix *self) {
    if (self->row == self->col) {
        for (int i = 0; i < self->row; i++) {
            for (int j = 0; j < self->col; j++) {
                if (i == j) {
                    self->main[i][j] = 1.0;
                } else {
                    self->main[i][j] = 0.0;
                }
            }
        }
        return 0;
    } else {
        return 1;
    }
}

int mat_compare(matrix first, matrix second) {
    int flag = 0;
    if (first.row == second.row && first.col == second.col) {
        for (int i = 0; i < first.row; i++) {
            for (int j = 0; j < first.col; j++) {
                if (EPSILON < first.main[i][j] - second.main[i][j] ||
                    first.main[i][j] - second.main[i][j] < -EPSILON) {
                    flag = 1;
                }
            }
        }
        return flag;
    } else {
        return 1;
    }
}

int mat_solve(matrix *x, matrix a, matrix b) {
    matrix tmp;
    mat_alloc(&tmp, a.row, a.col);
    mat_copy(&tmp, a);

    matrix ans;
    mat_alloc(&ans, x->row, x->col);
    mat_copy(&ans, *x);

    matrix b_ref;
    mat_alloc(&b_ref, b.row, b.col);
    mat_copy(&b_ref, b);

    if (a.row == a.col && a.row == b.row && a.row == x->row && b.col == 1 &&
        x->col == 1) {
        for (int i = 0; i < a.row - 1; i++) {
            double max = fabs(tmp.main[i][i]);
            for (int j = i + 1; j < a.row; j++) {
                if (fabs(tmp.main[j][i]) > max) {
                    max = fabs(tmp.main[j][i]);
                }
            }
            for (int j = i; j < a.row; j++) {
                if (fabs(tmp.main[j][i]) == max) {
                    for (int t = 0; t < a.col; t++) {
                        double ref;
                        ref = tmp.main[i][t];
                        tmp.main[i][t] = tmp.main[j][t];
                        tmp.main[j][t] = ref;
                    }
                    double tmp_b;
                    tmp_b = b_ref.main[i][0];
                    b_ref.main[i][0] = b_ref.main[j][0];
                    b_ref.main[j][0] = tmp_b;
                }
            }

            for (int j = i + 1; j < a.row; j++) {
                double ref = tmp.main[j][i];
                for (int k = 0; k < a.col; k++) {
                    tmp.main[j][k] -= tmp.main[i][k] * ref / tmp.main[i][i];
                }
                b_ref.main[j][0] -= b_ref.main[i][0] * ref / tmp.main[i][i];
            }
        }

        ans.main[ans.row - 1][0] =
                b_ref.main[ans.row - 1][0] / tmp.main[tmp.row - 1][tmp.col - 1];

        for (int i = ans.row - 2; i >= 0; i--) {
            ans.main[i][0] = b_ref.main[i][0];
            for (int j = i + 1; j < ans.row; j++) {
                ans.main[i][0] -= tmp.main[i][j] * ans.main[j][0];
            }
            ans.main[i][0] /= tmp.main[i][i];
        }

        for (int i = 0; i < ans.row; i++) {
            x->main[i][0] = ans.main[i][0];
        }

        mat_free(&tmp);
        mat_free(&ans);
        mat_free(&b_ref);
        return 0;
    } else {
        return 1;
    }
}

int mat_inverse(matrix *s, matrix a) {
    if (a.row == a.col && a.row == s->row && a.col == s->col) {
        matrix ref;
        mat_alloc(&ref, a.row, a.col);

        for (int i = 0; i < a.col; i++) {
            for (int j = 0; j < a.row; j++) {
                matrix init;
                mat_alloc(&init, a.row, 1);
                for (int k = 0; k < a.row; k++) {
                    if (k == i) {
                        init.main[k][0] = 1;
                    } else {
                        init.main[k][0] = 0;
                    }
                }

                mat_solve(&init, a, init);

                ref.main[j][i] = init.main[j][0];
                mat_free(&init);
            }
        }

        mat_copy(s, ref);
        mat_free(&ref);
        return 0;
    } else {
        return 1;
    }
}
