#include <stdio.h>
//put here all the define
#define DRAW_MODE_CLEAR 0

// basicCmd contains
typedef struct{
  char cmd;
  int x1;
  int x2;
  int y1;
  int y2;
  int dx;
  int dy;
  int m;
} basicCmd;

int drawPoint(int x, int y, int m);
int drawLine(int x1, int y1, int x2, int y2, int m);
int drawEllipse(int xc, int yc, int dx, int dy, int m);
