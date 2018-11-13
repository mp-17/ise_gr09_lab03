#include "read.h"
#define POINT 'P'
#define LINE 'L'
#define ELLIPSE 'E'

// basicCmd contains
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
//
// it reads one character from the input peripheral, decode a single command and update a structure.
//
// INPUT
// - *basicCommand : pointer to basicCommand struct type (this struct has to be instantiated by the caller).
// OUTPUT
// - returns 0 if no error, otherwise 1
// CALLED FUNCTIONS
// - readChar()
// MEMORY MODIFICATION
// - *basicCommand memory locations
int readCommand(*basicCommand);
