#include "draw.h"

int drawPoint(int x, int y, int m){
  
}

//drawLine ()
//DESCRIPTION
//   Draws a line which end points are specified as arguments.
//   Drawing methods have to be also specfied as last argument by caller.
//OUTPUT
//   Returns:
//           0 for drawing success
//           1 for errors
//MEMORY NEEDS
//   6*regular int
//MEMORY MODIFICATIONS
//   Modify the global matrix called frameBuffer

int drawLine(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,int m){
  if (x1 > rowsFrame || x2 > rowsFrame || y1 > colsFrame  || y2 > colsFrame)
    return 1;
  int dx,dy,eps,maxx;
  int i,j;
  
  dx=x2-x1;
  dy=y2-y1;
  eps=dy-dx;
  
  if (x1>x2)
    maxx=x1;
  else
    maxx=x2;

  if (y1<y2)
    j=y1;
  else
    j=y2;
  i=maxx;
  
  while (i<maxx) {
    switch (m) {
      
      case DRAW_MODE_CLEAR:
	frameBuffer[(colsFrame*8)/i][j]=frameBuffer[(colsFrame*8)/i][j]
    }
    if (eps>=0){
      j++;
      eps-=dx;
    }
    i++;
    eps+=dy;
  }
}

int drawEclipse(int xc, int yc, int dx, int dy, int m){

}
