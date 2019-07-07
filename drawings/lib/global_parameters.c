//
// Created by kirohy on 19/07/07.
//

#include "global_parameters.h"

int MapState[WINDOW_SIZE][WINDOW_SIZE];

int SplineDrawPoints[ACTIVE_SIZE / SPLINE_STEP + 1][2];

int ObjectNum = 0;

PathCoefficients PathCoef;

Object CurrentObj;

Object ObjectList[MAX_OBJECT];

Mode CurrentMode = PUT_CUBE;