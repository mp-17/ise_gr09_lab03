#include <stdio.h>
#include "read.h"
#include "draw.h"

int main(int argc, char *argv[])
{
	basicCmd cmdStruct;
	
	while(readCommand(* cmdStruct) != 1) {
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
	  		printf("Error 1\n", );
	  	break;
	  	} 
	}
  return 0;
}