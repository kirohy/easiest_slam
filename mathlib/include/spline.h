#ifndef FINAL_SPLINE_H
#define FINAL_SPLINE_H

#include "matrix.h"

#define INF_POINTS 100

// matrix[n][0] = x, matrix[n][1] = y
typedef struct {
    int num;
    int xy[INF_POINTS][2];
} SplineBasePoints;

// 補間の計算の前に昇順ソート
void spline_points_sort(SplineBasePoints *Points);

// answerの上から4つずつが3次関数の係数
int spline(SplineBasePoints Points, matrix *answer);

#endif //FINAL_SPLINE_H
