#include <stdio.h>

#define DRAW_MODE_CLEAR 0
#define DRAW_MODE_SET 1
#define DRAW_MODE_XOR 2

char frameBuffer[128][16];
int DrawPoint(int x, int y, int m);
void printBuffer();

//function to draw a point in the frameBuffer
//return 1 if an error occurs for wrong parameters
//return 0 if the drawing is successful
int main(int argc, char** argv){
  int a;
  a = DrawPoint(15,0,1);
  return a;
}

int DrawPoint(int x, int y, int m)
{
  for(int i=0; i<128; i++){
    for(int j=0; j<16; j++){
      frameBuffer[i][j] = '\0';
    }
  }
  //local variable to set the n bit to change
  int nBit= x%8;
  
  if(m == DRAW_MODE_CLEAR){
    // clear the n bit inverting the Byte 0x01 first
    // then an AND bitwise operation is done with the
    // wanted Byte to set to 0 the n bit
    // the n bit is the remainder of x/8
    frameBuffer[127-y][x/8] &= ~(0x01<<(7-nBit));
    printBuffer();
    
    return 0;
  }
  else if(m == DRAW_MODE_SET){
    // using the OR bitwise operation with
    // 0000 0001 a bit can be set to 1
    // the remainder of x/8 is the bit to set
    frameBuffer[127-y][x/8] |= 0x01<<(7-nBit);
    printBuffer();
      
    return 0;
  }
  else if(m == DRAW_MODE_XOR){
    // using the XOR bitwise operation the n bit
    // is toggled
    // the n bit is the remainder of x/8
    frameBuffer[127-y][x/8] ^= 0x01<<(7-nBit);
    printBuffer();
    
    return 0;
  }
  else{
    return 1;
  }

}

void printBuffer(){
  for(int i=0; i<128; i++){
    printf("%d ",127-i);
    for(int j=0; j<16; j++){
      for(int k=0; k<8; k++){
	printf("%d", !!(frameBuffer[i][j] & (1 << (7 - k))));
      }
      printf(" ");
    }
    printf("\n");
  }
}

