#ifndef FINAL_SPLINE_H
#define FINAL_SPLINE_H

#include "matrix.h"

#define MAX_POINTS 5

typedef struct {
    int num;
    matrix xy;
} SplineBasePoints;

int spline_points_new(SplineBasePoints *Points, int num, matrix base);

int spline(SplineBasePoints Points, matrix *answer);

#endif //FINAL_SPLINE_H
