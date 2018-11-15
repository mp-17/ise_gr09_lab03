#include <stdio.h>
#include <math.h>

#define DRAW_MODE_CLEAR 0
#define DRAW_MODE_SET   1
#define DRAW_MODE_XOR   2

#define rowsFrame 128
#define colsFrame  16
#define wordPixels  8
#define BASE        2

char frameBuffer[rowsFrame][colsFrame]={{0}};

int drawLine(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,int m);
void printWord(char word);

int main(int argc, char *argv[]){
  int i,j;
  int x1,x2,y1,y2,m;
  int try;
  printf("Insert a command:\n");
  scanf("%d %d %d %d %d", &x1, &x2, &y1, &y2, &m);
  try=drawLine(x1,x2,y1,y2,m);
  if(try==1)
    printf("errore in drawLine\n");
  for (i=0;i<rowsFrame;i++){
    for (j=0;j<colsFrame;j++){
       printWord(frameBuffer[i][j]);
    }
  printf("\n");
  }
  return 0;
}

int drawLine(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2,int m){
  
  if ((x1 > (colsFrame*wordPixels-1)) || (x2 > (colsFrame*wordPixels-1)) || (y1 > (rowsFrame-1))  || (y2 > (rowsFrame-1)))
    return 1;
  int di,dj,eps,maxX;
  int i,j;
  char startPoint;
  
  dj=x2-x1;
  di=y2-y1;
  eps=di-dj;
  
  //TBSTART
  printf("%d %d %d\n",dj,di,eps);
  //TBEND
  
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
  //TBSTART
  printf("%d %d %d %c\n",j,i,maxX,startPoint);
  int cnt=0;
  //TBEND
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
      //TBSTART
      printf("halo");
      //TBSTART
      if (startPoint=='1'){
	if (y1>y2){
	  i--;
	  //TBSTART
	  printf("halo");
	  //TBSTART
	}
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
  //TBSTART
  printf("%d\n",cnt );
  //TBEND
  return 0;
}

void printWord(char word){
  int i;
  int num;
  num=(int)word;
  if(num<0)
    num=2*rowsFrame+num;
  for(i=wordPixels-1;i>=0;i--){
    printf("%d", num/(int)pow(BASE,i));
    num=num%(int)pow(BASE,i);
  }
}
