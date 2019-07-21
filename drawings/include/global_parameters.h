#ifndef FINAL_GLOBAL_PARAMETERS_H
#define FINAL_GLOBAL_PARAMETERS_H

#include "spline.h"

#define WINDOW_SIZE 650 // GTKの描画範囲
#define MAP_SIZE 640 // 実際のMAPの大きさ
#define ACTIVE_SIZE 500 // 移動可能範囲
#define SPLINE_STEP 4 // スプラインの描画周期(x)
#define CUBE_SIZE_ONE 50 // cube1の1辺
#define CUBE_SIZE_TWO 75 // cube2の対角線

#define MAX_POINTS 5 // スプライン補間元の点の数
#define MAX_OBJECT 5 // オブジェクト設置上限
#define OBSERVE 15 // 毎週期の観測点の数

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

// マップの状態[y][x]
extern int MapState[MAP_SIZE + 2][MAP_SIZE + 2];

// [n][0] = x, [n][1] = y
extern int SplineDrawPoints[ACTIVE_SIZE / SPLINE_STEP + 1][2];

// Splineの傾き
extern double SplineDiff[ACTIVE_SIZE / SPLINE_STEP + 1];

// スプラインの方程式の係数
extern PathCoefficients PathCoef;

// 補間のもとの点群
extern SplineBasePoints SplinePoints;

// 直前の点の状態を保持
extern SplineBasePoints SplinePoints_prev;

// 現在のオブジェクト数
extern int ObjectNum;

// 現在のオブジェクト状態を保持
extern Object CurrentObj;

// 設置済みオブジェクトの状態
extern Object ObjectList[MAX_OBJECT];

// 現在のモード
extern Mode CurrentMode;

// 現在のSplineDrawPointsのナンバー
extern int CurrentPoint;

// 観測点
extern ObservedPos ObservedPoint[ACTIVE_SIZE / SPLINE_STEP + 1][OBSERVE];

// アニメーション現在時間
extern int time_animation;

// 実行周期
extern int time_interval;

#endif //FINAL_GLOBAL_PARAMETERS_H
