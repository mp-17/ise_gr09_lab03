#include "read.h"
#define POINT 'P'
#define LINE 'L'
#define ELLIPSE 'E'
#define xMax 128
#define yMax 128

// basicCmd contains
// - cmd: the letter which encodes the command
// - x1: first coordinate on the independent axis
// - x2: second coordinate on the independent axis
// - y1: first coordinate on the dependent axis
// - y2: second coordinate on the dependent axis
// - dx: length of the main axis (for ellipse)
// - dy: legth of the secondary axis (for ellipse)
// - m: specification for the command
typedef struct{
  char cmd;
  short unsigned int x1;
  short unsigned int x2;
  short unsigned int y1;
  short unsigned int y2;
  short unsigned int dx;
  short unsigned int dy;
  short unsigned int m;
} basicCmd;

// readChar() 
// reads from a peripheral input and returns a single char
//
// OUTPUT
// returns one read char from the stdin
// CALLED FUNCTIONS
// - getc
// MEMORY MODIFICATION
// no memory modification
char readChar(void);

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
short int readChar2Int(void);

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
short int readCommand(basicCmd* cmdStruc_pt);
