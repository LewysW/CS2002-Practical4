#ifndef HEADER
#define HEADER
#include <stdbool.h>

#define NUM_TOKENS 4 //Max number of valid tokens
#define OUTPUT 0 //Index of output token
#define OPERATOR 1 //Index of operator token
#define INPUT_ONE 2 //Index of first input token
#define INPUT_TWO 3 //Index of second input token
#define DEFAULT_CAPACITY 10 //Default capacity of array list
#define MORE_SPACE 100 //Additional space if array list exceeds capacity

//Struct representing a wire
typedef struct Wire {
    //Stores name of wire, current val, and next value.
    char* name;
    int val;
    int nextVal;
} Wire;

//Struct representing Gate
typedef struct Gate {
    //Stores name of operator, and three wire pointers to output and input wires.
    char* op;
    Wire* output;
    Wire* input1;
	Wire* input2;
} Gate;

//Struct representing LinkedList to store wires
struct LinkedList {
    //Current wire at node
    Wire* wire;
    //Next node
    struct LinkedList* next;
};

//Allows declaration of LinkedList structs using Node keyword
typedef struct LinkedList* Node;

//Struct representing ArrayList
typedef struct ArrayList {
    //Array of gates
    Gate* gates;
    //Size of array list
    int size;
    //capacity of array list (number of elements in *gates)
    int capacity;
} ArrayList;

//Linked list of wires
Node wires;

//circuits.c
Wire* make_wire(char* str, int value);
Wire* get_wire(char* wireStr);
Gate make_gate(char* output, char* operator, char* input1, char* input2);
int get_output(Gate prev);
ArrayList compute_state(ArrayList gateList);
ArrayList update_inputs(ArrayList gateList, int dec);
bool is_stable(ArrayList gateList);
int* dec_to_binary(int dec, int numBits);
int get_num_IN(ArrayList gateList);
ArrayList generate_circuit(ArrayList gateList);
bool stabilise_circuit(ArrayList gateList);
ArrayList assign_next_state(ArrayList gateList);
bool stabilise_circuit(ArrayList gateList);

//io.c
void output_truth_table(ArrayList gateList);
void print_circuit_output(bool stable, bool containsOut);
void print_wire_attributes(ArrayList gateList, char* attr);
void tokenize_line(char* line, char* inputs[]);
bool valid_operator(char* operator);
bool valid_expression(char* expression[], ArrayList gateList);

//linkedlist.c
Node createNode();
Node addNode(Node head, Wire* wire);
int sizeOfLinkedList(Node head);
bool linkedListContains(Node head, char* nodeStr);
Wire* getNode(Node head, char* nodeStr);
void reset_wires(Node head);
void freeLinkedList(Node node);

//arraylist.c
ArrayList arrayListAdd(ArrayList list, Gate gate);
ArrayList arrayListExpand(ArrayList list);
ArrayList createArrayList(int capacity);
void freeArrayList(ArrayList gateList);


#endif
