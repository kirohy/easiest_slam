//
// Created by kirohy on 19/07/07.
//

#ifndef FINAL_MAP_CALCULATOR_H
#define FINAL_MAP_CALCULATOR_H

#include "global_parameters.h"

// MapStateを初期化
void init_map();

void put_object(Object obj);

// SplineDrawPointsに点情報を充填
int calc_draw_points();

static double calc_tan(double tan_default, double theta);

void init_observe();

void find_wall(int num);

#endif //FINAL_MAP_CALCULATOR_H
