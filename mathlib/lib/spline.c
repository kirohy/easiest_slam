//
// Created by kirohy on 19/06/25.
//

#include "spline.h"
#include "matrix.h"

int pow_int(int base, int exp) {
    int ans = 1;
    while (exp > 0) {
        ans *= base;
        exp -= 1;
    }
    return ans;
}

void spline_points_sort(SplineBasePoints *Points) {
    for (int i = 0; i < Points->num - 1; i++) {
        for (int j = i + 1; j < Points->num; j++) {
            if (Points->xy[i][0] > Points->xy[j][0]) {
                int tmp0 = Points->xy[i][0];
                int tmp1 = Points->xy[i][1];
                Points->xy[i][0] = Points->xy[j][0];
                Points->xy[i][1] = Points->xy[j][1];
                Points->xy[j][0] = tmp0;
                Points->xy[j][1] = tmp1;
            }
        }
    }
}

// answerの上から4つずつが3次関数の係数
int spline(SplineBasePoints Points, matrix *answer) {
    if (Points.num >= 3 && answer->row == (Points.num - 1) * 4 && answer->col == 1) {
        matrix A = mat_new((Points.num - 1) * 4, (Points.num - 1) * 4);
        matrix B = mat_new((Points.num - 1) * 4, 1);

        // A
        // 境界値連続
        for (int i = 0; i < Points.num - 1; i++) {
            A.main[2 * i][i * 4] = (double) pow_int(Points.xy[i][0], 3);
            A.main[2 * i][i * 4 + 1] = (double) pow_int(Points.xy[i][0], 2);
            A.main[2 * i][i * 4 + 2] = (double) Points.xy[i][0];
            A.main[2 * i][i * 4 + 3] = 1.0;
            A.main[2 * i + 1][i * 4] = (double) pow_int(Points.xy[i + 1][0], 3);
            A.main[2 * i + 1][i * 4 + 1] = (double) pow_int(Points.xy[i + 1][0], 2);
            A.main[2 * i + 1][i * 4 + 2] = (double) Points.xy[i + 1][0];
            A.main[2 * i + 1][i * 4 + 3] = 1.0;
            for (int j = (i + 1) * 4; j < A.col; j++) {
                A.main[2 * i][j] = 0.0;
                A.main[2 * i + 1][j] = 0.0;
            }
            for (int j = 0; j < i * 4; j++) {
                A.main[2 * i][j] = 0.0;
                A.main[2 * i + 1][j] = 0.0;
            }
        }

        // 1次微分連続
        for (int i = 0; i < Points.num - 2; i++) {
            int base_row = (Points.num - 1) * 2 + i;
            A.main[base_row][i * 4] = 3.0 * (double) pow_int(Points.xy[i + 1][0], 2);
            A.main[base_row][i * 4 + 1] = 2.0 * (double) Points.xy[i + 1][0];
            A.main[base_row][i * 4 + 2] = 1.0;
            A.main[base_row][i * 4 + 3] = 0.0;
            A.main[base_row][i * 4 + 4] = -3.0 * (double) pow_int(Points.xy[i + 1][0], 2);
            A.main[base_row][i * 4 + 5] = -2.0 * (double) Points.xy[i + 1][0];
            A.main[base_row][i * 4 + 6] = -1.0;
            A.main[base_row][i * 4 + 7] = 0.0;
            for (int j = 0; j < i * 4; j++) {
                A.main[base_row][j] = 0.0;
            }
            for (int j = i * 4 + 8; j < A.col; j++) {
                A.main[base_row][j] = 0.0;
            }
        }

        // 2次微分連続
        for (int i = 0; i < Points.num - 2; i++) {
            int base_row = Points.num * 3 - 4 + i;
            A.main[base_row][i * 4] = 6.0 * (double) Points.xy[i + 1][0];
            A.main[base_row][i * 4 + 1] = 2.0;
            A.main[base_row][i * 4 + 2] = 0.0;
            A.main[base_row][i * 4 + 3] = 0.0;
            A.main[base_row][i * 4 + 4] = -6.0 * (double) Points.xy[i + 1][0];
            A.main[base_row][i * 4 + 5] = -2.0;
            A.main[base_row][i * 4 + 6] = 0.0;
            A.main[base_row][i * 4 + 7] = 0.0;
            for (int j = 0; j < i * 4; j++) {
                A.main[base_row][j] = 0.0;
            }
            for (int j = i * 4 + 8; j < A.col; j++) {
                A.main[base_row][j] = 0.0;
            }
        }

        // 端点の2次微分0
        A.main[A.row - 2][0] = 6.0 * (double) Points.xy[0][0];
        A.main[A.row - 2][1] = 2.0;
        for (int i = 2; i < A.col; i++) {
            A.main[A.row - 2][i] = 0.0;
        }
        A.main[A.row - 1][A.col - 4] = 6.0 * (double) Points.xy[Points.num - 1][0];
        A.main[A.row - 1][A.col - 3] = 2.0;
        A.main[A.row - 1][A.col - 2] = 0.0;
        A.main[A.row - 1][A.col - 1] = 0.0;
        for (int i = 0; i < A.col - 4; i++) {
            A.main[A.row - 1][i] = 0.0;
        }

        // B
        for (int i = 0; i < Points.num - 1; i++) {
            B.main[i * 2][0] = (double) Points.xy[i][1];
            B.main[i * 2 + 1][0] = (double) Points.xy[i + 1][1];
        }
        for (int i = (Points.num - 1) * 2; i < B.row; i++) {
            B.main[i][0] = 0.0;
        }

        // mat_print(&A);
        // mat_print(&B);
        // mat_print(&Points.xy);

        mat_solve(answer, A, B);

        mat_free(&A);
        mat_free(&B);
        return 0;
    } else {
        return 1;
    }
}