//
// Created by kirohy on 19/07/07.
//

#ifndef FINAL_GLOBAL_PARAMETERS_H
#define FINAL_GLOBAL_PARAMETERS_H

#define WINDOW_SIZE 640
#define ACTIVE_SIZE 500
#define SPLINE_STEP 4

#define MAX_POINTS 5
#define MAX_OBJECT 5

typedef struct {
    double base[MAX_POINTS][4];
    double diff[MAX_POINTS][3];
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

extern int MapState[WINDOW_SIZE][WINDOW_SIZE];

extern int SplineDrawPoints[ACTIVE_SIZE / SPLINE_STEP + 1][2];

extern int ObjectNum;

extern PathCoefficients PathCoef;

extern Object CurrentObj;

extern Object ObjectList[MAX_OBJECT];

extern Mode CurrentMode;

#endif //FINAL_GLOBAL_PARAMETERS_H
