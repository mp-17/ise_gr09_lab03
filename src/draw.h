#include <stdio.h>
//put here all the define
#define DRAW_MODE_CLEAR 0

typedef struct{
  int cmd;
  int x1;
  int x2;
  int y1;
  int y2;
  int dx;
  int dy;
  int m;
} basicCmd;

int readChar();
int readCommand();
int drawPoint(int x, int y, int m);
int drawLine(int x1, int y1, int x2, int y2, int m);
int drawEclipse(int xc, int yc, int dx, int dy, int m);
