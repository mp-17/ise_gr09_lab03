#include "tb.h"
#include "shared.h"

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