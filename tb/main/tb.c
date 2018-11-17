#include "tb.h"

// print a word of the frame
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

// print the matrix
void printMtx(void) {
	for (i=0;i<rowsFrame;i++) {
		for (j=0;j<colsFrame;j++) {
			printWord(frameBuffer[i][j]);
		}
		printf("\n");
	}
}

// routine to flush the buffer
void flushInBuf(void) {
	char c;
	while ((c = getchar()) != '\n' && c != EOF);
}