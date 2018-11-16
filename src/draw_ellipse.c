#include <stdio.h>
//#include "shared.h"

#define N 127

int drawEllipse(int xc, int yc, int height, int weight, int m)
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
