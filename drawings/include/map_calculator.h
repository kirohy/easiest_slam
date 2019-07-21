#ifndef FINAL_MAP_CALCULATOR_H
#define FINAL_MAP_CALCULATOR_H

#include "global_parameters.h"

// MapStateを初期化
void init_map();

// MapStateにオブジェクト情報を書き込み
void put_object(Object obj);

// SplineDrawPointsに点情報を充填
int calc_draw_points();

// tan加法定理
static double calc_tan(double tan_default, double theta);

// 観測点初期化
void init_observe();

// 観測点の計算と格納
void find_wall(int num);

#endif //FINAL_MAP_CALCULATOR_H
