//
// Created by kirohy on 19/07/07.
//

#include "global_parameters.h"

int MapState[MAP_SIZE + 2][MAP_SIZE + 2];

int SplineDrawPoints[ACTIVE_SIZE / SPLINE_STEP + 1][2];

double SplineDiff[ACTIVE_SIZE / SPLINE_STEP + 1];

int ObjectNum = 0;

PathCoefficients PathCoef;

Object CurrentObj;

Object ObjectList[MAX_OBJECT];

Mode CurrentMode = PUT_CUBE;

SplineBasePoints SplinePoints = {2, {{70, 70}, {570, 570}, {0, 0}, {0, 0}, {0, 0}}};

int CurrentPoint = 0;
