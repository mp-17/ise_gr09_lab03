#include <stdio.h>
#include "shared.h"
#include "read.h"
#include "draw.h"
#include "tb.h"
char frameBuffer[rowsFrame][colsFrame];
// main drawOnCmd TESTBENCH FILE (don't use draw function, but prints messages insted)
// it instantiates a location in memory for cmdStruct, in which each command is stored.
// readChar() reads from the peripheral interface, the cmdBuffer is updated 
// and readCommand() decodes the command and updates cmdStruct if the command is valid.
// three different functions can draw a point, a line or an ellipsis in a 128 bits x 128 bits memory.
// there is a special command to quit the program.
// main returns 0 if no errors occured, otherwise it returns 1

int main(int argc, char** argv)
{
  // variable definitions
  unsigned short int i=0, j=0;
  char cmdBuffer[maxCmdLength];
  basicCmd cmdStruct;
  _Bool end_flag = 0;

  // reset the buffer with harmless characters
  for (i = 0; i < maxCmdLength; i++) {
    cmdBuffer[i] = '\0';
  }

  // welcome screen
  printf("Please insert a command in one of the following forms:\n");
  printf("P'x1''y1''m'\n");
  printf("L'x1''y1'x2''y2''m'\n");
  printf("E'x1''y1'dx''dy''m'\n");
  printf("Where 'x1', 'x2, 'y1', 'y2' are numbes from 0 to 127, and 'm' is a number between 0 and 2.\n");
  printf("Simply digit it, there's no need for pressing enter\n");

  while (1) {
    printf("Insert 'p' if you want to print the matrix. Otherwise insert another character.\n");
    if (readChar() == 'p') {
    	// flush the input buffer
    	while (getchar() != '\n');
      for (i=0;i<rowsFrame;i++) {
	for (j=0;j<colsFrame;j++) {
	  printWord(frameBuffer[i][j]);
	}
	printf("\n");
      }
    }
    else {
    	// flush the input buffer
    	while (getchar() != '\n');
      printf("Do you wish to reset the end_flag? if yes, digit 'Y'. If not, digit another character.\n");
      if (readChar() == 'Y') {
      	// flush the input buffer
    	while (getchar() != '\n');
	    end_flag = 0;
      }
      printf("Now insert the commands you want to execute.\n");
      // main reading loop
      while (!end_flag) {
	end_flag = 0;
	// right shift the elements in the buffer
	for (i = 1; i < maxCmdLength; i++) {
	  cmdBuffer[i-1] = cmdBuffer[i];
	}
	// read the new character
	cmdBuffer[maxCmdLength-1] = readChar();
	// if there is a valid command in the buffer, execute it. Otherwise, loop
	if ( readCommand(cmdBuffer, &cmdStruct) ) {
	  switch (cmdStruct.cmd) {
	  case POINT:
	    //drawPoint(cmdStruct.x1, cmdStruct.y1, cmdStruct.m);
	    printf("Congratulations! You selected POINT command.\n");
	    printf("cmd: %c\n", cmdStruct.cmd);
	    printf("x1: %d\n", cmdStruct.x1);
	    printf("y1: %d\n", cmdStruct.y1);
	    printf("x2: %d\n", cmdStruct.x2);
	    printf("y2: %d\n", cmdStruct.y2);
	    printf("dx: %d\n", cmdStruct.dx);
	    printf("dy: %d\n", cmdStruct.dy);
	    printf("m: %d\n", cmdStruct.m);
	    end_flag = 1;
	    break;
	  case LINE:
	    //drawLine(cmdStruct.x1, cmdStruct.x2, cmdStruct.y1, cmdStruct.y2, cmdStruct.m);
	    printf("Congratulations! You selected LINE command.\n");
	    printf("cmd: %c\n", cmdStruct.cmd);
	    printf("x1: %d\n", cmdStruct.x1);
	    printf("y1: %d\n", cmdStruct.y1);
	    printf("x2: %d\n", cmdStruct.x2);
	    printf("y2: %d\n", cmdStruct.y2);
	    printf("dx: %d\n", cmdStruct.dx);
	    printf("dy: %d\n", cmdStruct.dy);
	    printf("m: %d\n", cmdStruct.m);
	    end_flag = 1;
	    break;
	  case ELLIPSE:
	    drawEllipse(cmdStruct.x1, cmdStruct.y1, cmdStruct.dx, cmdStruct.dy, cmdStruct.m);
	    printf("Congratulations! You selected ELLIPSE command.\n");
	    printf("cmd: %c\n", cmdStruct.cmd);
	    printf("x1: %d\n", cmdStruct.x1);
	    printf("y1: %d\n", cmdStruct.y1);
	    printf("x2: %d\n", cmdStruct.x2);
	    printf("y2: %d\n", cmdStruct.y2);
	    printf("dx: %d\n", cmdStruct.dx);
	    printf("dy: %d\n", cmdStruct.dy);
	    printf("m: %d\n", cmdStruct.m);
	    end_flag = 1;
	    break;
	    break;
	  default:
	    // error: the readCommand has returned a boolean 1 but the cmd field in the struct 
	    // is not coherent with a valid command
	    return 1;
	    break;
	  } 
	}
      }
    }
		
  }

  return 0;
}
