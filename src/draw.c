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
    frameBuffer[127-y][x/8] &= ~(0x01 << (7-nBit));
    return 0;
  }
  else if(m == DRAW_MODE_SET){
    frameBuffer[127-y][x/8] |= 0x01 << (7-nBit);
    return 0;
  } 
  else if(m == DRAW_MODE_XOR){
    frameBuffer[127-y][x/8] ^= (0x01 << (7-nBit));
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
//   6*int + 1*char
//MEMORY MODIFICATIONS
//   Modify the global matrix called frameBuffer

int drawLine(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,int m){
  if ((x1 > (colsFrame*wordPixels-1)) || (x2 > (colsFrame*wordPixels-1)) || (y1 > (rowsFrame-1))  || (y2 > (rowsFrame-1)))
    return 1;
  int di,dj,eps,maxX;
  int i,j;
  char startPoint;
  
  dj=abs(x2-x1);
  di=abs(y2-y1);
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

//drawEllipse()
//DESCRIPTION
//  Draw an ellipse in the frameBuffer, an array of arrays of char corresponding to a virtual screen of pixels
//  It receives as inputs:
//  --xc and yc: they are the cartesian coordinates of the ellipse center
//  --dx and dy: they are respectively the horizantal and vertical diameters of the ellipse
//  --m : it is the draw mode of the function: if m=0, an ellipse is deleted on the screen; if m=1, an ellipse is drawn on the screen;
//        if m=2, the pixels of the ellipse to draw are cleared or drawn according to their previous state: if they are already drawn, they are cleared and viceversa.
//  WARNING: The parts of the ellipse to draw that fall out of the virtual screen, are not drawn.
//OUTPUT
//  It returns 0
//MEMORY NEEDS
//  it employs nine local variables
//MEMORY MODIFICATION
//  It accesses and modifies frameBuffer to draw the ellipse

int drawEclipse(int xc, int yc, int dx, int dy, int m){
    width = dy/2; //width is the vertical half diameter of the ellipse
    height = dx/2; //height is the horizontal half diameter of the ellipse
    int a2 = width * width;
    int b2 = height * height;
    int fa2 = 4 * a2, fb2 = 4 * b2;
    int x, y, sigma;
    int x_last, y_last;
    //BRESENHAM ALGORITHM - START
    //Writing the vertical parts  of ellipse - start
    for (x = 0, y = height, sigma = 2*b2+a2*(1-2*height); b2*x <= a2*y; x++)
    {

        
      if ((yc+x)>=0 && (yc+x)<=N) //before writing the pixels, I check if the pixel position is correct, or, in other words, if its position doesn't fall out of the screen
        {
            if ((xc+y)>=0 && (xc+y)<=N) //before writing the pixels, I check if the pixel position is correct, or, in other words, if its position doesn't fall out of the screen
            {	
	      if ((yc+x) != (yc-x)) { //Bresenham's algorithm first correction: we don't want write one pixel more than one time
		  switch (m) {
		  case 0 : //clear pixel
		    frameBuffer[yc+x][(xc+y)/l] &= ~(1<<(7-((xc+y)%l)));
		    break;
		  case 1 : //set pixel
		    frameBuffer[yc+x][(xc+y)/l] |= (1<<(7-((xc+y)%l)));
		    break;
		  case 2 : //xor pixel
		    frameBuffer[yc+x][(xc+y)/l] ^= (1<<(7-((xc+y)%l)));
		    break;
		  default :
		    break;
		  }
		}
            }
        }
        if ((yc-x)>=0 && (yc-x)<=N)
        {
            if ((xc+y)>=0 && (xc+y)<=N)
            {
	      switch (m) {
		  case 0 :
		    frameBuffer[yc-x][(xc+y)/l] &= ~(1<<(7-((xc+y)%l)));
		    break;
		  case 1 :
		    frameBuffer[yc-x][(xc+y)/l] |= (1<<(7-((xc+y)%l)));
		    break;
		  case 2 :
		    frameBuffer[yc-x][(xc+y)/l] ^= (1<<(7-((xc+y)%l)));
		    break;
		  default :
		    break;
		  }
            }
        }
        if ((yc+x)>=0 && (yc+x)<=N)
        {
            if ((xc-y)>=0 && (xc-y)<=N)
            {
                if ((yc-x) != (yc+x)) {
		  switch (m) {
		  case 0 :
		    frameBuffer[yc+x][(xc-y)/l] &= ~(1<<(7-((xc-y)%l)));
		    break;
		  case 1 :
		    frameBuffer[yc+x][(xc-y)/l] |= (1<<(7-((xc-y)%l)));
		    break;
		  case 2 :
		    frameBuffer[yc+x][(xc-y)/l] ^= (1<<(7-((xc-y)%l)));
		    break;
		  default :
		    break;
		    }
		}
            }
        }
        if ((yc-x)>=0 && (yc-x)<=N)
        {
            if ((xc-y)>=0 && (xc-y)<=N)
            {
	      switch (m) {
		  case 0 :
		    frameBuffer[yc-x][(xc-y)/l] &= ~(1<<(7-((xc-y)%l)));
		    break;
		  case 1 :
		    frameBuffer[yc-x][(xc-y)/l] |= (1<<(7-((xc-y)%l)));
		    break;
		  case 2 :
		    frameBuffer[yc-x][(xc-y)/l] ^= (1<<(7-((xc-y)%l)));
		    break;
		  default :
		    break;
		    }
            }
        }
        //writing the vertical part of ellipse - end
	x_last=x; //The last value of x and y will be used to the second correction of Bresenham algorithm
	y_last=y; //The last value of x and y will be used to the second correction of Bresenham algorithm

        if (sigma >= 0)
        {
            sigma += fa2 * (1 - y);
            y--;
        }
        sigma += b2 * ((4 * x) + 6);
    }

    //Writing the horizontal parts of ellipse - start
    for (x = width, y = 0, sigma = 2*a2+b2*(1-2*width); a2*y <= b2*x; y++)
    {
      if (x!=x_last || y!=y_last){ //Bresenham's algorithm second correction: we don't want to overwrite pixels of vertical and horizontal parts
        if ((yc+x)>=0 && (yc+x)<=N)
        {
            if ((xc+y)>=0 && (xc+y)<=N)
            {
                if ((xc+y) != (xc-y)) {
		  switch (m) {
		  case 0 :
		    frameBuffer[yc+x][(xc+y)/l] &= ~(1<<(7-((xc+y)%l)));
		    break;
		  case 1 :
		    frameBuffer[yc+x][(xc+y)/l] |= (1<<(7-((xc+y)%l)));
		    break;
		  case 2 :
		    frameBuffer[yc+x][(xc+y)/l] ^= (1<<(7-((xc+y)%l)));
		    break;
		  default :
		    break;
		    }
		}
            }
        }
        if ((yc-x)>=0 && (yc-x)<=N)
        {
            if ((xc+y)>=0 && (xc+y)<=N)
            {
                if ((xc+y) != (xc-y)) {
		  switch (m) {
		  case 0 :
		    frameBuffer[yc-x][(xc+y)/l] &= ~(1<<(7-((xc+y)%l)));
		    break;
		  case 1 :
		    frameBuffer[yc-x][(xc+y)/l] |= (1<<(7-((xc+y)%l)));
		    break;
		  case 2 :
		    frameBuffer[yc-x][(xc+y)/l] ^= (1<<(7-((xc+y)%l)));
		    break;
		  default :
		    break;
		    }
		}
            }
        }
        if ((yc+x)>=0 && (yc+x)<=N)
        {
            if ((xc-y)>=0 && (xc-y)<=N)
            {
	      switch (m) {
		  case 0 :
		    frameBuffer[yc+x][(xc-y)/l] &= ~(1<<(7-((xc-y)%l)));
		    break;
		  case 1 :
		    frameBuffer[yc+x][(xc-y)/l] |= (1<<(7-((xc-y)%l)));
		    break;
		  case 2 :
		    frameBuffer[yc+x][(xc-y)/l] ^= (1<<(7-((xc-y)%l)));
		    break;
		  default :
		    break;
		    }
            }
        }
        if ((yc-x)>=0 && (yc-x)<=N)
        {
            if ((xc-y)>=0 && (xc-y)<=N)
            {
	      switch (m) {
		  case 0 :
		    frameBuffer[yc-x][(xc-y)/l] &= ~(1<<(7-((xc-y)%l)));
		    break;
		  case 1 :
		    frameBuffer[yc-x][(xc-y)/l] |= (1<<(7-((xc-y)%l)));
		    break;
		  case 2 :
		    frameBuffer[yc-x][(xc-y)/l] ^= (1<<(7-((xc-y)%l)));
		    break;
		  default :
		    break;
		    }
            }
        }
      }
        //writing the pixels - end

        if (sigma >= 0)
        {
            sigma += fb2 * (1 - x);
            x--;
        }
        sigma += a2 * ((4 * y) + 6);
    }
    return 0;
}


int abs(int num){
  if (num<0)
    return -num;
  else
    return num;
}
