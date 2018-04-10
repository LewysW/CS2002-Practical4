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

//Circuits.c
Wire* make_wire(char* str, int value); //COMMENTED
Wire* get_wire(char* wireStr); //COMMENTED
Gate make_gate(char* output, char* operator, char* input1, char* input2); //COMMENTED
int get_output(Gate prev); //COMMENTED
ArrayList compute_state(ArrayList gateList); //COMMENTED
ArrayList update_inputs(ArrayList gateList, int dec); //COMMENTED
bool is_stable(ArrayList gateList); //COMMENTED
int* dec_to_binary(int dec, int numBits); //COMMENTED
int get_num_IN(ArrayList gateList);//COMMENTED
ArrayList generate_circuit(ArrayList gateList);//COMMENTED
bool stabilise_circuit(ArrayList gateList);//COMMENTED

void tokenize_line(char* line, char* inputs[]);
bool valid_operator(char* operator);
bool valid_expression(char* expression[], ArrayList gateList);
int get_num_IN(ArrayList gateList);
void reset_wires(Node head);
ArrayList assign_next_state(ArrayList gateList);
void print_state(ArrayList gateList, bool isStable);
void output_truth_table(ArrayList gateList);
void print_wire_attributes(ArrayList gateList, char* attr);
void print_circuit_output(bool stable, bool containsOut);
bool stabilise_circuit(ArrayList gateList);

//Linked list functions - TODO - delete unneccessary functions
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
