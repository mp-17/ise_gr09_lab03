#include <stdio.h>
#include "read.h"

// readChar() 
// reads from a peripheral input and returns a single char
//
// OUTPUT
// returns one read char
// CALLED FUNCTIONS
// - getc
// MEMORY MODIFICATION
// no memory modification
char readChar(void) {
	return getc(stdin);
};

// readChar2Int() 
// reads from a peripheral input an ASCII/UTF char and returns the corresponding digit. If the char was not representing 
// a digit, it returns 10
//
// OUTPUT
// returns the digit which was represented in ASCII/UTF. If something goes wrong (i.e. the char was not a digit), 
// it returns 10 
// CALLED FUNCTIONS
// - readChar()
// MEMORY NEEDS
// it needs 16 bits for a short int variable
// MEMORY MODIFICATION
// no memory modification
short int readChar2Int(void) {

	short unsigned int digit = 0;

	digit = (int)readChar() - '0';

	if (digit >= 0 && digit <= 9) {
		return digit;
	}
	else {
		return 10;
	}

}

// readCommand()
// it reads characters from the input peripheral, decodes a single command and updates a structure passed as a parameter.
//
// INPUT
// - cmdStruc_pt : pointer to basicCommand struct type (this struct has to be instantiated by the caller).
// OUTPUT
// - returns 0 if no error, otherwise it returns 1
// CALLED FUNCTIONS
// - readChar()
// MEMORY NEEDS
// it needs 16 bits for a short int variable
// MEMORY MODIFICATION
// - *basicCommand memory locations
short int readCommand(basicCmd* cmdStruc_pt) {

	short unsigned int buf = 0;

	*cmdStruc_pt.cmd = readChar();

	switch (*cmdStruc_pt.cmd) {
		case POINT:
			buf = readChar2Int()*100;
			buf += readChar2Int()*10;
			*cmdStruc_pt.x1 = buf + readChar2Int();
			buf = readChar2Int()*100;
			buf += readChar2Int()*10;
			*cmdStruc_pt.y1 = buf + readChar2Int();
			*cmdStruc_pt.m = readChar2Int();
			if ( !(*cmdStruc_pt.x1 <= xMax && *cmdStruc_pt.y1 <= yMax && *cmdStruc_pt.m < 3) ) {
				return 1;
			}
			break;
		case LINE:
			buf = readChar2Int()*100;
			buf += readChar2Int()*10;
			*cmdStruc_pt.x1 = buf + readChar2Int();
			buf = readChar2Int()*100;
			buf += readChar2Int()*10;
			*cmdStruc_pt.y1 = buf + readChar2Int();
			buf = readChar2Int()*100;
			buf += readChar2Int()*10;
			*cmdStruc_pt.x2 = buf + readChar2Int();
			buf = readChar2Int()*100;
			buf += readChar2Int()*10;
			*cmdStruc_pt.y2 = buf + readChar2Int();
			*cmdStruc_pt.m = readChar2Int();
			if ( !(*cmdStruc_pt.x1 <= xMax && *cmdStruc_pt.y1 <= yMax && *cmdStruc_pt.x2 <= xMax && *cmdStruc_pt.y2 <= yMax && *cmdStruc_pt.m < 3) ) {
				return 1;
			}
			break;
		case ELLIPSE:
			buf = readChar2Int()*100;
			buf += readChar2Int()*10;
			*cmdStruc_pt.x1 = buf + readChar2Int();
			buf = readChar2Int()*100;
			buf += readChar2Int()*10;
			*cmdStruc_pt.y1 = buf + readChar2Int();
			buf = readChar2Int()*100;
			buf += readChar2Int()*10;
			*cmdStruc_pt.dx = buf + readChar2Int();
			buf = readChar2Int()*100;
			buf += readChar2Int()*10;
			*cmdStruc_pt.dy = buf + readChar2Int();
			*cmdStruc_pt.m = readChar2Int();
			if ( !(*cmdStruc_pt.x1 <= xMax && *cmdStruc_pt.y1 <= yMax && *cmdStruc_pt.dx <= xMax && *cmdStruc_pt.dy <= yMax && *cmdStruc_pt.m < 3) ) {
				return 1;
			}
			break;
		default: 
			return 1;
			break;
	}
	return 0;
};