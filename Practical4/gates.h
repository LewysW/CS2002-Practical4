#ifndef HEADER
#define HEADER
#include <stdbool.h>

#define NUM_TOKENS 4
#define OUTPUT 0
#define OPERATOR 1
#define INPUT_ONE 2
#define INPUT_TWO 3

typedef struct Wire {
    char* name;
    int value;
} Wire;

typedef struct Gate {
    char* op;
    Wire* output;
    Wire* input1;
	Wire* input2;
} Gate;

Wire* make_wire(char* str, int value);
void tokenize_line(char* line, char* inputs[]);
Wire* get_output(Gate gate, char* output);
Gate make_gate(char* output, char* operator, Wire* input1, Wire* input2);
bool valid_operator(char* operator);
bool valid_expression(char* expression[]);

#endif
