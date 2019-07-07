//
// Created by kirohy on 19/07/07.
//

#ifndef FINAL_MAP_CALCULATOR_H
#define FINAL_MAP_CALCULATOR_H

#include "global_parameters.h"

void init_map(int map[WINDOW_SIZE][WINDOW_SIZE]);

void calc_draw_points();

void put_object(int map[WINDOW_SIZE][WINDOW_SIZE], Object obj);

#endif //FINAL_MAP_CALCULATOR_H
