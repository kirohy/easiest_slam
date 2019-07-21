#include <math.h>

#include "map_calculator.h"
#include "spline.h"

void init_map() {
    for (int i = 1; i <= MAP_SIZE; i++) {
        for (int j = 1; j <= MAP_SIZE; j++) {
            MapState[i][j] = 0;
        }
    }
    for (int i = 0; i < MAP_SIZE + 2; i++) {
        MapState[0][i] = 1;
        MapState[MAP_SIZE + 1][i] = 1;
        MapState[i][0] = 1;
        MapState[i][MAP_SIZE + 1] = 1;
    }

    SplineDrawPoints[0][0] = 70;
    SplineDrawPoints[0][1] = 70;
}

void put_object(Object obj) {
    if (obj.type == CUBE_ONE && ObjectNum < MAX_OBJECT) {
        for (int i = obj.x - CUBE_SIZE_ONE / 2; i < obj.x + CUBE_SIZE_ONE / 2; i++) {
            for (int j = obj.y - CUBE_SIZE_ONE / 2; j < obj.y + CUBE_SIZE_ONE / 2; j++) {
                MapState[i][j] = 1;
            }
        }
    } else if (obj.type == CUBE_TWO && ObjectNum < MAX_OBJECT) {
        for (int i = obj.y - (CUBE_SIZE_TWO - 1) / 2; i < obj.y; i++) {
            for (int j = obj.x - (i - obj.y + (CUBE_SIZE_TWO - 1) / 2);
                 j <= obj.x + (i - obj.y + (CUBE_SIZE_TWO - 1) / 2); j++) {
                MapState[j][i] = 1;
            }
        }
        for (int i = obj.y; i <= obj.y + (CUBE_SIZE_TWO - 1) / 2; i++) {
            for (int j = obj.x - (obj.y + (CUBE_SIZE_TWO - 1) / 2 - i);
                 j <= obj.x + (obj.y + (CUBE_SIZE_TWO - 1) / 2 - i); j++) {
                MapState[j][i] = 1;
            }
        }
    }
}

int calc_draw_points() {
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

        if (SplineDrawPoints[i][1] < 20 || SplineDrawPoints[i][1] > 620) {
            return 1;
        }
        // y'
        SplineDiff[i] = (double) x * (double) x * PathCoef.diff[mode][0] +
                        (double) x * PathCoef.diff[mode][1] + PathCoef.diff[mode][2];
        x += SPLINE_STEP;
    }

    return 0;
}

static double calc_tan(double tan_default, double theta) {
    return (tan_default + tan(theta)) / (1 - tan_default * tan(theta));
}

void init_observe() {
    for (int i = 0; i < ACTIVE_SIZE / SPLINE_STEP + 1; i++) {
        for (int j = 0; j < OBSERVE; j++) {
            ObservedPoint[i][j].x = 0;
            ObservedPoint[i][j].y = 0;
        }
    }
}

// レーザーの壁検知(i番目の描画点)
void find_wall(int num) {
    int x_origin = SplineDrawPoints[num][0];
    int y_origin = SplineDrawPoints[num][1];

    // xを足していくか引いていくか。前者が1,後者が-1
    int mode[OBSERVE];

    // 傾きを格納
    double laser_tan[OBSERVE];
    double offset = M_PI / (double) (OBSERVE + 1);
    for (int i = 0; i < OBSERVE; i++) {
        laser_tan[i] = calc_tan(SplineDiff[num], offset * (double) (i - (OBSERVE - 1) / 2));

        double theta_tmp = atan(SplineDiff[num]) + offset * (double) (i - (OBSERVE - 1) / 2);
        if (theta_tmp > -M_PI / 2.0 && theta_tmp < M_PI / 2.0) {
            mode[i] = 1;
        } else {
            mode[i] = -1;
        }
    }

    int x;
    int y;
    double tmp_y;

    int count = 0;

    for (int i = 0; i < OBSERVE; i++) {
        x = x_origin;
        tmp_y = (double) y_origin;
        count = 0;
        while (count < MAP_SIZE) {
            if (mode[i] == 1) {
                tmp_y += laser_tan[i];
                x += 1;
            } else {
                tmp_y -= laser_tan[i];
                x -= 1;
            }

            y = (int) tmp_y;

            if (y > MAP_SIZE) {
                ObservedPoint[num][i].x = x;
                ObservedPoint[num][i].y = MAP_SIZE + 1;
                break;
            } else if (y < 0) {
                ObservedPoint[num][i].x = x;
                ObservedPoint[num][i].y = 0;
                break;
            }

            if (MapState[x][y] == 1) {
                if (MapState[x - 1][y] == 1 && MapState[x + 1][y] == 1) {
                    int tmp = y;
                    while (MapState[x][tmp] == 1) {
                        if (mode[i] * laser_tan[i] > 0) {
                            tmp -= 1;
                        } else {
                            tmp += 1;
                        }
                    }
                    ObservedPoint[num][i].x = x;
                    ObservedPoint[num][i].y = tmp;
                } else {
                    ObservedPoint[num][i].x = x;
                    ObservedPoint[num][i].y = y;
                }
                break;
            }
            count += 1;
        }
    }
}