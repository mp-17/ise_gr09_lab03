#include "draw.h"

//drawPoint()
//DESCRIPTION
//  Draw a point in the frameBuffer
//  It receives two coordinates x y in the 0-127 range
//  It receives the draw mode m from the caller
//OUTPUT
//  If the draw mode is correct i.e. 0 1 2
//  0 is returned as a successful operation
//  otherwise 1 is asserted
//MEMORY NEEDS
//  a local variable is used to determine which bit
//  is going to be changed in the desired Byte block
//MEMORY MODIFICATION
//  a global variable frameBuffer is modified to draw the point

int drawPoint(int x, int y, int m){
  int nBit= x%8;

  if(m == DRAW_MODE_CLEAR){
    frameBuffer[127-y][x/8] &= ~(0x01 << nBit);
    return 0;
  }
  else if(m == DRAW_MODE_SET){
    frameBuffer[127-y][x/8] |= 0x01 << (nBit);
    return 0;
  } 
  else if(m == DRAW_MODE_XOR){
    frameBuffer[127-y][x/8] ^= (0x01 << (nBit));
    return 0;
  }
  else{
    return 1;
  }
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
