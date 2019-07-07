//
// Created by kirohy on 19/07/07.
//

#include "map_calculator.h"

void init_map(int map[WINDOW_SIZE][WINDOW_SIZE]) {
    for (int i = 0; i < WINDOW_SIZE; i++) {
        for (int j = 0; j < WINDOW_SIZE; j++) {
            map[i][j] = 0;
        }
    }
}

void put_object(int (*map)[WINDOW_SIZE], Object obj) {

}

void calc_draw_points() {
    int x_begin = (WINDOW_SIZE - ACTIVE_SIZE) / 2;
    int y_begin = (WINDOW_SIZE - ACTIVE_SIZE) / 2;
    int x_end = WINDOW_SIZE - (WINDOW_SIZE - ACTIVE_SIZE) / 2;
    int y_end = WINDOW_SIZE - (WINDOW_SIZE - ACTIVE_SIZE) / 2;

    SplineDrawPoints[0][0] = x_begin;
    SplineDrawPoints[0][1] = y_begin;
    SplineDrawPoints[ACTIVE_SIZE / SPLINE_STEP][0] = x_end;
    SplineDrawPoints[ACTIVE_SIZE / SPLINE_STEP][0] = y_end;

    int x = x_begin;
    int y;

    for (int i = 0; i < ACTIVE_SIZE / SPLINE_STEP; i++) {
    }
}
