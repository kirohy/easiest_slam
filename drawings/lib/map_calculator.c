//
// Created by kirohy on 19/07/07.
//

#include "map_calculator.h"
#include "spline.h"

void init_map() {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            MapState[i][j] = 0;
        }
    }
}

void put_object(Object obj) {
    if (obj.type == POINT && SplinePoints.num < MAX_POINTS) {
        SplinePoints.xy[SplinePoints.num][0] = obj.x;
        SplinePoints.xy[SplinePoints.num][1] = obj.y;
    }
}

void calc_draw_points() {
    spline_points_sort(&SplinePoints);

    matrix coef = mat_new(4 * (SplinePoints.num - 1), 1);

    spline(SplinePoints, &coef);

    for (int i = 0; i < SplinePoints.num - 1; i++) {
        // 3次方程式係数
        PathCoef.base[i][0] = coef.main[i * 4][0];
        PathCoef.base[i][1] = coef.main[i * 4 + 1][0];
        PathCoef.base[i][2] = coef.main[i * 4 + 2][0];
        PathCoef.base[i][3] = coef.main[i * 4 + 3][0];
        // 微分値の係数
        PathCoef.diff[i][0] = coef.main[i * 4][0] * 3;
        PathCoef.diff[i][1] = coef.main[i * 4 + 1][0] * 2;
        PathCoef.diff[i][2] = coef.main[i * 4 + 2][0];
    }

    int x = SplinePoints.xy[0][0];

    int mode = 0;
    for (int i = 0; i < ACTIVE_SIZE / SPLINE_STEP + 1; i++) {
        // x
        SplineDrawPoints[i][0] = x;

        // y
        if (x > SplinePoints.xy[1][0]) {
            mode = 1;
            if (x > SplinePoints.xy[2][0]) {
                mode = 2;
                if (x > SplinePoints.xy[3][0]) {
                    mode = 3;
                }
            }
        }

        SplineDrawPoints[i][1] = (int) ((double) x * (double) x * (double) x * PathCoef.base[mode][0] +
                                        (double) x * (double) x * PathCoef.base[mode][1] +
                                        (double) x * PathCoef.base[mode][2] + PathCoef.base[mode][3]);
        // y'
        SplineDiff[i] = (double) x * (double) x * PathCoef.diff[mode][0] +
                        (double) x * PathCoef.diff[mode][1] + PathCoef.diff[mode][2];
        x += SPLINE_STEP;
    }
}
