#ifndef HEADER
#define HEADER
#include <stdbool.h>

#define NUM_TOKENS 4
#define OUTPUT 0
#define OPERATOR 1
#define INPUT_ONE 2
#define INPUT_TWO 3
#define DEFAULT_CAPACITY 10

typedef struct Wire {
    char* name;
    int val;
    int nextVal;
} Wire;

typedef struct Gate {
    char* op;
    Wire* output;
    Wire* input1;
	Wire* input2;
} Gate;

struct LinkedList {
    Wire* wire;
    struct LinkedList* next;
};

//Allows declareation of LinkedList structs using Node keyword
typedef struct LinkedList* Node;

typedef struct ArrayList {
    Gate *gates;
    int size;
    int capacity;
} ArrayList;

Node wires;

Wire* make_wire(char* str, int value);
void tokenize_line(char* line, char* inputs[]);
int get_output(Gate prev);
Gate make_gate(char* output, char* operator, char* input1, char* input2);
Wire* get_wire(char* wireStr);
bool valid_operator(char* operator);
bool valid_expression(char* expression[], ArrayList gateList);
ArrayList compute_state(ArrayList gateList);
ArrayList update_inputs(ArrayList gateList, int dec);
int get_num_IN(ArrayList gateList);
int* dec_to_binary(int dec, int numBits);
void reset_wires(Node head);
ArrayList assign_next_state(ArrayList gateList);
bool is_stable(ArrayList gateList);
void print_state(ArrayList gateList, bool isStable);

//Linked list functions - TODO - deleted unneccessary functions
Node createNode();
Node addNode(Node head, Wire* wire);
bool linkedListContains(Node head, char* nodeStr);
Wire* getNode(Node head, char* nodeStr);
void printLinkedList(Node node);
void freeLinkedList(Node node);
void printLinkedList(Node node);
int sizeOfLinkedList(Node head);

//ArrayList functions - TODO - deleted unneccessary functions
ArrayList arrayListAdd(ArrayList list, Gate gate);
ArrayList arrayListExpand(ArrayList list);
ArrayList createArrayList(int capacity);
void printArrayList(ArrayList list);
void freeArrayList(ArrayList gateList);


#endif
