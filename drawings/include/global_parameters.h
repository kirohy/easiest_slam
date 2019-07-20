//
// Created by kirohy on 19/07/07.
//

#ifndef FINAL_GLOBAL_PARAMETERS_H
#define FINAL_GLOBAL_PARAMETERS_H

#include "spline.h"

#define WINDOW_SIZE 650
#define MAP_SIZE 640
#define ACTIVE_SIZE 500
#define SPLINE_STEP 4
#define CUBE_SIZE_ONE 50
#define CUBE_SIZE_TWO 75

#define MAX_POINTS 5
#define MAX_OBJECT 5

#define OBSERVE 15

// 左から順に方程式の係数
typedef struct {
    double base[MAX_POINTS - 1][4];
    double diff[MAX_POINTS - 1][3];
} PathCoefficients;

enum ObjectType {
    CUBE_ONE,
    CUBE_TWO,
    POINT,
};

typedef enum {
    PUT_CUBE_ONE,
    PUT_CUBE_TWO,
    PUT_POINT,
    RUN,
} Mode;

typedef struct {
    enum ObjectType type;
    int x;
    int y;
} Object;

typedef struct {
    int x;
    int y;
} ObservedPos;

extern int MapState[MAP_SIZE + 2][MAP_SIZE + 2];

// [n][0] = x, [n][1] = y
extern int SplineDrawPoints[ACTIVE_SIZE / SPLINE_STEP + 1][2];

// Splineの傾き
extern double SplineDiff[ACTIVE_SIZE / SPLINE_STEP + 1];

extern int ObjectNum;

// スプラインの方程式の係数
extern PathCoefficients PathCoef;

extern Object CurrentObj;

extern Object ObjectList[MAX_OBJECT];

extern Mode CurrentMode;

extern SplineBasePoints SplinePoints;

extern SplineBasePoints SplinePoints_prev;

// 現在のSplineDrawPointsのナンバー
extern int CurrentPoint;

// 観測点
extern ObservedPos ObservedPoint[ACTIVE_SIZE / SPLINE_STEP + 1][OBSERVE];

// アニメーション現在時間
extern int time_animation;

// 実行周期
extern int time_interval;

#endif //FINAL_GLOBAL_PARAMETERS_H
