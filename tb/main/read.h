#define POINT 'P'
#define LINE 'L'
#define ELLIPSE 'E'
#define minCmdLength 8
#define maxCmdLength 14
#define minCmdOffset 6 // maxCmdLength-minCmdLength
#define xMax 127
#define yMax 127

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
  unsigned short int x1;
  unsigned short int x2;
  unsigned short int y1;
  unsigned short int y2;
  unsigned short int dx;
  unsigned short int dy;
  unsigned short int m;
} basicCmd;

// readChar(void) 
// reads from a peripheral input and returns a single char
//
// OUTPUT
// returns one read char
// CALLED FUNCTIONS
// - getc
// MEMORY MODIFICATION
// no memory modification
char readChar(void);

// char2int(char charIn) 
// reads from input an ASCII/UTF char and returns the corresponding digit in short int format. If the char was not representing 
// a digit, it returns 10
//
// OUTPUT
// returns the digit which was represented in ASCII/UTF. If something goes wrong (i.e. the char was not a digit), 
// it returns 10 
// CALLED FUNCTIONS
// no function is called
// MEMORY NEEDS
// it needs 16 bits for a short int variable
// MEMORY MODIFICATION
// no memory modification
short int char2int(char charIn);

// readCommand(char* cmdBuffer, basicCmd* cmdStruc_pt)
// it reads an array in which a command can be present. If a valid command is recognized then the data structure is updated coherently
//
// INPUT
// - cmdBuffer: the buffer array in which char from input peripheral are stored. The length of cmdBuffer allows it to contain a valid command.
// - cmdStruc_pt: pointer to basicCommand struct type (this struct has to be instantiated by the caller).
// OUTPUT
// - returns a boolean 1 if a valid command is read, otherwise it returns a boolean 0
// CALLED FUNCTIONS
// - readChar()
// MEMORY NEEDS
// it needs 16 bits for a short int variable
// MEMORY MODIFICATION
// - *basicCommand memory locations: apart from the "cmd" field, the others are modificated even if the command is not valid
_Bool readCommand(char* cmdBuffer, basicCmd* cmdStruc_pt);