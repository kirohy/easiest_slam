#ifndef FINAL_SPLINE_H
#define FINAL_SPLINE_H

#include "matrix.h"

#define MAX_POINTS 5

// matrix[n][0] = x, matrix[n][1] = y
typedef struct {
    int num;
    int xy[MAX_POINTS][2];
} SplineBasePoints;

void spline_points_sort(SplineBasePoints *Points);

int spline(SplineBasePoints Points, matrix *answer);

#endif //FINAL_SPLINE_H
