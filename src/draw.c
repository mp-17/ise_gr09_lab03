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
  if ((x1 > (colsFrame*wordPixels-1)) || (x2 > (colsFrame*wordPixels-1)) || (y1 > (rowsFrame-1))  || (y2 > (rowsFrame-1)))
    return 1;
  int di,dj,eps,maxX;
  int i,j;
  char startPoint;
  
  dj=x2-x1;
  di=y2-y1;
  eps=di-dj;
  
  if (x1>x2){
    maxX=x1;
    j=x2;
    i=y2;
    startPoint='2';
  }
  else{
    maxX=x2;
    j=x1;
    i=y1;
    startPoint='1';
  }
  while (j<maxX+1) {
    switch (m) {
      case DRAW_MODE_CLEAR: {
	frameBuffer[rowsFrame-1-i][j/8] &= ~(0x01<<(wordPixels-j%wordPixels-1));
	break;
      }
      case DRAW_MODE_SET: {
	frameBuffer[rowsFrame-1-i][j/8] |= (0x01<<(wordPixels-j%wordPixels-1));
	break;
      }
      case DRAW_MODE_XOR: {
	frameBuffer[rowsFrame-1-i][j/8] ^= (0x01<<(wordPixels-j%wordPixels-1));
	break;
      }
    }
    if (eps>=0){
      if (startPoint=='1'){
	if (y1>y2)
	  i--;
	else
	  i++;
      }
      else{
	 if (y2>y1)
	   i--;
         else
	   i++;
      }
      eps-=dj;
    }
    j++;
    eps+=di;
  }
  return 0;
}

int drawEclipse(int xc, int yc, int dx, int dy, int m){

}
