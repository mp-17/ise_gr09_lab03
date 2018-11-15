#include <stdio.h>
#include "shared.h"
#include "read.h"
#include "draw.h"

// main drawOnCmd function
// it instantiates a location in memory for cmdStruct, in which each command is stored.
// readCommand reads from the peripheral interface, decodes the command and updates cmdStruct.
// three different functions can draw a point, a line or an ellipsis in a 128 bits x 128 bits memory.
// there is a special command to quit the program.
// main returns 0 if no errors occured, otherwise it returns 1

int main(int argc, char** argv)
{
	char frameBuffer[rowsFrame][colsFrame];
	_Bool end_flag = 0;
	basicCmd cmdStruct;

	while(!end_flag) {
		if (!readCommand(&cmdStruct)) {
			switch (cmdStruct.cmd) {
		  	case POINT:
		  		drawPoint(cmdStruct.x1, cmdStruct.y1, cmdStruct.m);
		  	break;
		  	case LINE:
		  		drawLine(cmdStruct.x1, cmdStruct.x2, cmdStruct.y1, cmdStruct.y2, cmdStruct.m);
		  	break;
		  	case ELLIPSE:
		  		drawEllipse(cmdStruct.x1, cmdStruct.y1, cmdStruct.dx, cmdStruct.dy, cmdStruct.m);
		  	break;
		  	default:
		  		return 1;
		  	break;
		  	} 
	    }
	    else {
	    	return 2;
	    }
	}
  return 0;
}