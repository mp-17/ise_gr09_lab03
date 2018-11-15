#include <stdio.h>
#include "shared.h"
#include "read.h"

// main drawOnCmd TESTBENCH
// it simulates the behaviour of the normal main.c, but instead of calling a draw function, prints the results of the struct

int main(int argc, char** argv)
{
	char frameBuffer[rowsFrame][colsFrame];
	_Bool end_flag = 0;
	basicCmd cmdStruct;

	while(!end_flag) {
		printf("Please insert a command in one of the following forms:\n");
		printf("P'x1''y1''m'\n");
		printf("L'x1''y1'x2''y2''m'\n");
		printf("E'x1''y1'dx''dy''m'\n");
		printf("Where 'x1', 'x2, 'y1', 'y2' are numbes from 0 to 127, and 'm' is a number between 0 and 2.\n");
		printf("If you type something wrong, the program exits.\n");
		if (!readCommand(&cmdStruct)) {
			switch (cmdStruct.cmd) {
		  	case POINT:
		  		//drawPoint(cmdStruct.x1, cmdStruct.y1, cmdStruct.m);
		  		printf("Congratulations! You selected POINT command.\n");
		  		printf("cmd: %c\n", cmdStruct.cmd);
		  		printf("x1: %d\n", cmdStruct.x1);
		  		printf("y1: %d\n", cmdStruct.x2);
		  		printf("x2: %d\n", cmdStruct.y1);
		  		printf("y2: %d\n", cmdStruct.y2);
				printf("dx: %d\n", cmdStruct.dx);
		  		printf("dy: %d\n", cmdStruct.dy);
		  		printf("m: %d\n", cmdStruct.m);
		  	break;
		  	case LINE:
		  		//drawLine(cmdStruct.x1, cmdStruct.x2, cmdStruct.y1, cmdStruct.y2, cmdStruct.m);
		  		printf("Congratulations! You selected LINE command.\n");
		  		printf("cmd: %c\n", cmdStruct.cmd);
		  		printf("x1: %d\n", cmdStruct.x1);
		  		printf("y1: %d\n", cmdStruct.x2);
		  		printf("x2: %d\n", cmdStruct.y1);
		  		printf("y2: %d\n", cmdStruct.y2);
				printf("dx: %d\n", cmdStruct.dx);
		  		printf("dy: %d\n", cmdStruct.dy);
		  		printf("m: %d\n", cmdStruct.m);
		  	break;
		  	case ELLIPSE:
		  		//drawEllipse(cmdStruct.x1, cmdStruct.y1, cmdStruct.dx, cmdStruct.dy, cmdStruct.m);
		  		printf("Congratulations! You selected ELLIPSE command.\n");
		  		printf("cmd: %c\n", cmdStruct.cmd);
		  		printf("x1: %d\n", cmdStruct.x1);
		  		printf("y1: %d\n", cmdStruct.x2);
		  		printf("x2: %d\n", cmdStruct.y1);
		  		printf("y2: %d\n", cmdStruct.y2);
				printf("dx: %d\n", cmdStruct.dx);
		  		printf("dy: %d\n", cmdStruct.dy);
		  		printf("m: %d\n", cmdStruct.m);
		  	break;
		  	default:
		  		printf("Can't understand the command. Restart the program.\n");
		  		return 1;
		  	break;
		  	} 
	    }
	    else {
	    	printf("The command is not coherent with the specifics. Restart the program.");
	    	return 2;
	    }
	}
  return 0;
}