#include "read.h"
#define POINT 'P'
#define LINE 'L'
#define ELLIPSE 'E'
#define QUIT 'Q'

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
  int x1;
  int x2;
  int y1;
  int y2;
  int dx;
  int dy;
  int m;
} basicCmd;

// readChar reads from a peripheral input and returns a single char
char readChar();

// readCommand()
// it reads characters from the input peripheral, decodes a single command and updates a structure passed as a parameter.
//
// INPUT
// - cmdStruc_pt : pointer to basicCommand struct type (this struct has to be instantiated by the caller).
// OUTPUT
// - returns 0 if no error, otherwise it returns 1
// CALLED FUNCTIONS
// - readChar()
// MEMORY MODIFICATION
// - *basicCommand memory locations
int readCommand(basicCmd* cmdStruc_pt);
