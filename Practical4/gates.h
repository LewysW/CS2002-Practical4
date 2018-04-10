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
    Gate *gates;
    //Size of array list
    int size;
    //capacity of array list (number of elements in *gates)
    int capacity;
} ArrayList;

//Linked list of wires
Node wires;

//circuits.c
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
ArrayList assign_next_state(ArrayList gateList);//COMMENTED
bool stabilise_circuit(ArrayList gateList);//COMMENTED

//io.c
void output_truth_table(ArrayList gateList); //COMMENTED
void print_circuit_output(bool stable, bool containsOut);//COMMENTED
void print_wire_attributes(ArrayList gateList, char* attr);//COMMENTED
void tokenize_line(char* line, char* inputs[]);//COMMENTED
bool valid_operator(char* operator);//COMMENTED
bool valid_expression(char* expression[], ArrayList gateList);//COMMENTED

//linkedlist.c
Node createNode();//COMMENTED
Node addNode(Node head, Wire* wire);//COMMENTED
int sizeOfLinkedList(Node head);//COMMENTED
bool linkedListContains(Node head, char* nodeStr);//COMMENTED
Wire* getNode(Node head, char* nodeStr);//COMMENTED
void reset_wires(Node head);//COMMENTED
void freeLinkedList(Node node);//COMMENTED

//arraylist.c
ArrayList arrayListAdd(ArrayList list, Gate gate);//COMMENTED
ArrayList arrayListExpand(ArrayList list);//COMMENTED
ArrayList createArrayList(int capacity);//COMMENTED
void freeArrayList(ArrayList gateList);//COMMENTED


#endif
