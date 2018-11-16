#include <stdio.h>
#include "shared.h"
#define N 127
#define l 8

//put here all the define
//DRAWMODE DEFINE
#define DRAW_MODE_CLEAR 0
#define DRAW_MODE_SET   1
#define DRAW_MODE_XOR   2

int drawPoint(int x, int y, int m);
int drawLine(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,unsigned int m);
int drawEllipse(int xc, int yc, int dx, int dy, int m);
int abs(int num);
