#ifndef FINAL_SPLINE_H
#define FINAL_SPLINE_H

#include "matrix.h"

#define MAX_POINTS 5

typedef struct {
    int num;
    matrix xy;
} SplinePoints;

int spline_points_new(SplinePoints *Points, int num, matrix base);

int spline(SplinePoints Points, matrix *answer);

#endif //FINAL_SPLINE_H
