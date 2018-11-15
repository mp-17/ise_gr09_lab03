#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
  int i;
  int num;
  char alf;
  printf("Insert a number:\n");
  scanf("%d", &num);
  alf=(char)num;
  num=(int)alf;
  if(num<0)
    num=256+num;
  for(i=7;i>=0;i--){
    printf("%d", num/(int)pow(2,i));
    num=num%(int)pow(2,i);
  }
  printf("\n");
  return 0;
}
