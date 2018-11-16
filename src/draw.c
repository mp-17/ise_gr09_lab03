#include "shared.h"
#include "draw.h"

static char frameBuffer[rowsFrame][colsFrame];

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

int drawEclipse(int xc, int yc, int dx, int dy, int m)
{
  //int xc = 5;
  //int yc = (N-1) - 7;
  //int width = 5; // <--- questa è l'altezza
  //int height = 5; // <--- questa è la larghezza
  //int i, j; //
  //int m = 0; //

  //int matrice[N][N]; //

  //for (i=0; i<N; i++) //
  //{
  //  for (j=0; j<N; j++) //
  //    {
  //      matrice[i][j] = 0; //
  //    }
  //}

    yc = N - yc; //algorithm correction: now, y axis goes from the bottom to the top of the frameBuffer
    int a2 = width * width;
    int b2 = height * height;
    int fa2 = 4 * a2, fb2 = 4 * b2;
    int x, y, sigma;
    int x_last, y_last;

    /* first half - the vertical one */
    for (x = 0, y = height, sigma = 2*b2+a2*(1-2*height); b2*x <= a2*y; x++)
    {

        //before writing the pixels, I check if the pixel position is correct, or, in other words, if its position doesn't fall out of the screen
        //writing the pixels - start
        if ((yc+x)>=0 && (yc+x)<=N)
        {
            if ((xc+y)>=0 && (xc+y)<=N)
            {	
		if ((yc+x) != (yc-x)) {
		  switch (m) {
		  case 0 :
		    frameBuffer[yc+x][(xc+y)/8] &= ~(1<<(7-((xc+y)%8)));
		    break;
		  case 1 :
		    frameBuffer[yc+x][(xc+y)/8] |= (1<<(7-((xc+y)%8)));
		    break;
		  case 2 :
		    frameBuffer[yc+x][(xc+y)/8] ^= (1<<(7-((xc+y)%8)));
		    break;
		  default :
		    break;
		  }
		  // matrice[yc+x][xc+y] ++;//
		}
            }
        }
        if ((yc-x)>=0 && (yc-x)<=N)
        {
            if ((xc+y)>=0 && (xc+y)<=N)
            {
	      switch (m) {
		  case 0 :
		    frameBuffer[yc-x][(xc+y)/8] &= ~(1<<(7-((xc+y)%8)));
		    break;
		  case 1 :
		    frameBuffer[yc-x][(xc+y)/8] |= (1<<(7-((xc+y)%8)));
		    break;
		  case 2 :
		    frameBuffer[yc-x][(xc+y)/8] ^= (1<<(7-((xc+y)%8)));
		    break;
		  default :
		    break;
		  }
	      //matrice[yc-x][xc+y] ++;//
            }
        }
        if ((yc+x)>=0 && (yc+x)<=N)
        {
            if ((xc-y)>=0 && (xc-y)<=N)
            {
                if ((yc-x) != (yc+x)) {
		  switch (m) {
		  case 0 :
		    frameBuffer[yc+x][(xc-y)/8] &= ~(1<<(7-((xc-y)%8)));
		    break;
		  case 1 :
		    frameBuffer[yc+x][(xc-y)/8] |= (1<<(7-((xc-y)%8)));
		    break;
		  case 2 :
		    frameBuffer[yc+x][(xc-y)/8] ^= (1<<(7-((xc-y)%8)));
		    break;
		  default :
		    break;
		  }
		  //matrice[yc+x][xc-y] ++;//
		}
            }
        }
        if ((yc-x)>=0 && (yc-x)<=N)
        {
            if ((xc-y)>=0 && (xc-y)<=N)
            {
	      switch (m) {
		  case 0 :
		    frameBuffer[yc-x][(xc-y)/8] &= ~(1<<(7-((xc-y)%8)));
		    break;
		  case 1 :
		    frameBuffer[yc-x][(xc-y)/8] |= (1<<(7-((xc-y)%8)));
		    break;
		  case 2 :
		    frameBuffer[yc-x][(xc-y)/8] ^= (1<<(7-((xc-y)%8)));
		    break;
		  default :
		    break;
		  }
	      //matrice[yc-x][xc-y] ++;//
            }
        }
        //writing the pixels - end
	x_last=x;
	y_last=y;

        if (sigma >= 0)
        {
            sigma += fa2 * (1 - y);
            y--;
        }
        sigma += b2 * ((4 * x) + 6);


        //for (i=0; i<N; i++) //
        //{
	//  for (j=0; j<N; j++) //
	//  {
        //      printf("%d", matrice[i][j]); //
	//  }
	//  printf ("\n"); //
        //}
        //printf("\n y = %d, x = %d \n, sigma = %d \n", y, x, sigma); //
    }

    /* second half - the horizontal one */
    for (x = width, y = 0, sigma = 2*a2+b2*(1-2*width); a2*y <= b2*x; y++)
    {
        //before writing the pixels, I check if the pixel position is correct, or, in other words, if its position doesn't fall out of the screen
        //writing the pixels - start
      if (x!=x_last || y!=y_last){
        if ((yc+x)>=0 && (yc+x)<=N)
        {
            if ((xc+y)>=0 && (xc+y)<=N)
            {
                if ((xc+y) != (xc-y)) {
		  switch (m) {
		  case 0 :
		    frameBuffer[yc+x][(xc+y)/8] &= ~(1<<(7-((xc+y)%8)));
		    break;
		  case 1 :
		    frameBuffer[yc+x][(xc+y)/8] |= (1<<(7-((xc+y)%8)));
		    break;
		  case 2 :
		    frameBuffer[yc+x][(xc+y)/8] ^= (1<<(7-((xc+y)%8)));
		    break;
		  default :
		    break;
		  }
		  //matrice[yc+x][xc+y] ++;//
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
		    frameBuffer[yc-x][(xc+y)/8] &= ~(1<<(7-((xc+y)%8)));
		    break;
		  case 1 :
		    frameBuffer[yc-x][(xc+y)/8] |= (1<<(7-((xc+y)%8)));
		    break;
		  case 2 :
		    frameBuffer[yc-x][(xc+y)/8] ^= (1<<(7-((xc+y)%8)));
		    break;
		  default :
		    break;
		  }
		  //matrice[yc-x][xc+y] ++;//
		}
            }
        }
        if ((yc+x)>=0 && (yc+x)<=N)
        {
            if ((xc-y)>=0 && (xc-y)<=N)
            {
	      switch (m) {
		  case 0 :
		    frameBuffer[yc+x][(xc-y)/8] &= ~(1<<(7-((xc-y)%8)));
		    break;
		  case 1 :
		    frameBuffer[yc+x][(xc-y)/8] |= (1<<(7-((xc-y)%8)));
		    break;
		  case 2 :
		    frameBuffer[yc+x][(xc-y)/8] ^= (1<<(7-((xc-y)%8)));
		    break;
		  default :
		    break;
		  }
	      //matrice[yc+x][xc-y] ++;//
            }
        }
        if ((yc-x)>=0 && (yc-x)<=N)
        {
            if ((xc-y)>=0 && (xc-y)<=N)
            {
	      switch (m) {
		  case 0 :
		    frameBuffer[yc-x][(xc-y)/8] &= ~(1<<(7-((xc-y)%8)));
		    break;
		  case 1 :
		    frameBuffer[yc-x][(xc-y)/8] |= (1<<(7-((xc-y)%8)));
		    break;
		  case 2 :
		    frameBuffer[yc-x][(xc-y)/8] ^= (1<<(7-((xc-y)%8)));
		    break;
		  default :
		    break;
		  }
	      //matrice[yc-x][xc-y] ++;//
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

    //for (i=0; i<N; i++) //
    //{
    // for (j=0; j<N; j++) //
    //  {
    //  printf("%d", matrice[i][j]); //
    //  }
    // printf ("\n"); //
    //}

    return 0;
}


int abs(int num){
  if (num<0)
    return -num;
  else
    return num;
}
