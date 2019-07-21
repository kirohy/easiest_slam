#include "global_parameters.h"

int MapState[MAP_SIZE + 2][MAP_SIZE + 2];

int SplineDrawPoints[ACTIVE_SIZE / SPLINE_STEP + 1][2];

double SplineDiff[ACTIVE_SIZE / SPLINE_STEP + 1];

PathCoefficients PathCoef;

SplineBasePoints SplinePoints = {2, {{70, 70}, {570, 570}, {0, 0}, {0, 0}, {0, 0}}};

SplineBasePoints SplinePoints_prev = {2, {{70, 70}, {570, 570}, {0, 0}, {0, 0}, {0, 0}}};

int ObjectNum = 0;

Object CurrentObj;

Object ObjectList[MAX_OBJECT];

Mode CurrentMode = PUT_POINT;

int CurrentPoint = 0;

ObservedPos ObservedPoint[ACTIVE_SIZE / SPLINE_STEP + 1][OBSERVE];

int time_animation = 0;

int time_interval = 100;