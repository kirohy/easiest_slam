//
// Created by kirohy on 19/07/07.
//

#ifndef FINAL_GLOBAL_PARAMETERS_H
#define FINAL_GLOBAL_PARAMETERS_H

#include "spline.h"

#define WINDOW_SIZE 700
#define MAP_SIZE 640
#define ACTIVE_SIZE 500
#define SPLINE_STEP 4
#define CUBE_SIZE 50

#define MAX_POINTS 5
#define MAX_OBJECT 5

// 左から順に方程式の係数
typedef struct {
    double base[MAX_POINTS - 1][4];
    double diff[MAX_POINTS - 1][3];
} PathCoefficients;

enum ObjectType {
    CUBE,
    CYLINDER,
    POINT,
};

typedef enum {
    PUT_CUBE,
    PUT_CYLINDER,
    PUT_POINT,
    RUN,
} Mode;

typedef struct {
    enum ObjectType type;
    int x;
    int y;
    int size;
} Object;

extern int MapState[MAP_SIZE + 2][MAP_SIZE + 2];

// [n][0] = x, [n][1] = y, [n][2] = y'
extern int SplineDrawPoints[ACTIVE_SIZE / SPLINE_STEP + 1][2];

extern double SplineDiff[ACTIVE_SIZE / SPLINE_STEP + 1];

extern int ObjectNum;

extern PathCoefficients PathCoef;

extern Object CurrentObj;

extern Object ObjectList[MAX_OBJECT];

extern Mode CurrentMode;

extern SplineBasePoints SplinePoints;

extern int CurrentPoint;

#endif //FINAL_GLOBAL_PARAMETERS_H
