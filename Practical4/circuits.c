 //Included to avoid implicit getline declaration
#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "gates.h"

//Sets vals for one and zero wires
Wire zero_wire = (Wire){"zero", 0, 0};
Wire one_wire = (Wire){"one", 1, 1};

//Sets pointer to zero and one wires
Wire* zero = &zero_wire;
Wire* one =  &one_wire;

/*Initialises a wire* by setting its attributes (initially zero for values)
@str - value to use as name of wire
@val - value to set to val of wire
*/
Wire* make_wire(char* str, int val) {
	Wire* wire = malloc(sizeof(Wire));
	wire->name = strdup(str);
	wire->val = val;
	wire->nextVal = 0;
	return wire;
}

/* Gets a wire from the linked list of wires or creates it if it doesn't exist
@wireStr - name of wire
*/
Wire* get_wire(char* wireStr) {
	//If linked list does not contain wire
	if (!linkedListContains(wires, wireStr)) {
		//make wire and add to linked list
		Wire* wire = make_wire(wireStr, 0);
		wires = addNode(wires, wire);
		return wire;
	} else {
		//Otherwise get wire from linked list.
		return getNode(wires, wireStr);
	}
}

/*Initialises a gate struct with the appropriate operator and wires
@output - name of output wire
@operator - name of gate operator
@input1 - name of first input wire
@input2 - name of second input wire
*/
Gate make_gate(char* output, char* operator, char* input1, char* input2) {
	//Makes gate and initialises values to NULL
	Gate gate;
	gate.output = NULL;
	gate.op = NULL;
	gate.input1 = NULL;
	gate.input2 = NULL;

	//Sets gate operator to operator
    gate.op = strdup(operator);

	//Sets first input to input1 if any other gate than IN
	if (strcmp(operator, "IN")) {
		gate.input1 = get_wire(input1);
	}

	//Sets second input to input2 if any other gate than NOT and IN
    if (strcmp(operator, "NOT") && strcmp(operator, "IN")) {
		gate.input2 = get_wire(input2);
	}

	//Sets output to retrieved output wire
    gate.output = (get_wire(output));

    return gate;
}

/*Applies the logical operator of the given gate to the inputs of that gate
and returns the resulting value. If the gate is IN then the output value is returned.
@prev - previous gate to evaluate the output of.
*/
int get_output(Gate prev) {
	Gate gate = prev;

	//Evaluates the operators NOT, AND, OR, NAND, NOR, XOR, EQ (double implication), IN
    if (!strcmp(gate.op, "NOT")) return !(gate.input1->val);
    else if (!strcmp(gate.op, "AND")) return (gate.input1->val && gate.input2->val);
    else if (!strcmp(gate.op, "OR")) return (gate.input1->val || gate.input2->val);
    else if (!strcmp(gate.op, "NAND")) return !(gate.input1->val && gate.input2->val);
	else if (!strcmp(gate.op, "NOR")) return !(gate.input1->val || gate.input2->val);
    else if (!strcmp(gate.op, "XOR")) return (gate.input1->val ^ gate.input2->val);
    else if (!strcmp(gate.op, "EQ")) return !(gate.input1->val ^ gate.input2->val);
	else if (!strcmp(gate.op, "IN")) return gate.output->val;

	return -1;
}

/*Computes the next state of the circuit by setting the next value for each gate's output
to that evaluated by get_output.
@gateList - circuit to compute the state of.
*/
ArrayList compute_state(ArrayList gateList) {
	for (int i = 0; i < gateList.size; i++) {
		gateList.gates[i].output->nextVal = get_output(gateList.gates[i]);
	}

	return gateList;
}

/*Sets the current state of the circuit (the val variable of each output) to the
next state (value of the nextVal variable)
@gateList - circuit to assign next state of.
*/
ArrayList assign_next_state(ArrayList gateList) {
	for (int i = 0; i < gateList.size; i++) {
		gateList.gates[i].output->val = gateList.gates[i].output->nextVal;
	}
	return gateList;
}

/*Updates the inputs to use for the IN gates when evaluating the state of a circuit
@gateList - circuit to set inputs for.
@dec - decimal number to convert to binary circuit inputs.
*/
ArrayList update_inputs(ArrayList gateList, int dec) {
	int* inputs;

	//Converts decimal number to array of bits for use as inputs to circuit
	//number of bits required to store number is equal to number of IN gates
	inputs = dec_to_binary(dec, get_num_IN(gateList));

	//Sets output of IN gates to each bit from the bit array
	int bit = 0;
	for (int i = 0; i < gateList.size; i++) {
		if (!strcmp(gateList.gates[i].op, "IN")) {
			//Sets current bit in bit array to output value of IN gate.
			gateList.gates[i].output->val = *(inputs + (bit++));
		}
	}

	return gateList;
}

/*Checks if circuit is stable by comparing current val of gates to nextVal.
@gateList - circuit to check.
*/
bool is_stable(ArrayList gateList) {
	/*Iterates over gates of circuit, if any output values differ from the next
	output value then the circuit not stable and false is returned.
	*/
	for (int i = 0; i < gateList.size; i++) {
		if ((gateList.gates[i].output->val) != (gateList.gates[i].output->nextVal)) return false;
	}

	//Otherwise circuit must be stable and true is returned.
	return true;
}

/*Converts a decimal number to a binary number stored as an integer array of bits.
@dec - decimal number to be converted.
@numBits - number of bits required to store binary number.
source: https://www.javatpoint.com/c-program-to-convert-decimal-to-binary
*/
int* dec_to_binary(int dec, int numBits) {
	//Allocate space for each bit based on numBits (calloc sets memory to zero)
	int* binary = calloc(numBits, sizeof(int));

	//Set bits to initial values of zero.
	for (int i = 0; i < numBits; i++) binary[i] = 0;

	//Iterate while decimal number is greater than 0 and set bits from right to left
	for (int i = numBits - 1; dec > 0; i--) {
		//Get bit (0 if dec is even, 1 if dec is odd)
		binary[i] = dec % 2;
		//Divide dec by two
		dec = dec / 2;
	}

	return binary;
}

/*Counts number of IN gates in given circuit
@gateList - circuit to count number of IN gates.
*/
int get_num_IN(ArrayList gateList) {
	int numIN = 0;

	//Iterate over circuit
	for (int i = 0; i < gateList.size; i++) {
		//For each IN gate increment numIN.
		if (!strcmp(gateList.gates[i].op, "IN")) numIN++;
	}

	return numIN;
}

/* Generates a circuit from user input. Converts each line to a gate with possible
inputs and an output.
@gateList - circuit to generate.
*/
ArrayList generate_circuit(ArrayList gateList) {
	//Stores input tokens, line, and length of line.
	char** inputs;
	char* line = NULL;
	size_t len = 0;

	//Gets lines as input from stdin while user has not entered -1 (Ctrl-D)
	while (getline(&line, &len, stdin) != -1) {
		//Stores input tokens for output wire, operator, input1 and input2
		inputs = malloc(sizeof(char*) * NUM_TOKENS);

		//tokenizes input.
		tokenize_line(line, inputs);

		//If expression is valid, add gate to circuit.
		if (valid_expression(inputs, gateList)) {
			gateList = arrayListAdd(gateList, make_gate(*(inputs + OUTPUT), *(inputs + OPERATOR), *(inputs + INPUT_ONE), *(inputs + INPUT_TWO)));
		} else {
			//Otherwise print invalid input
			printf("Invalid Input\n");
		}

		//Free line and input pointers
		free(line);
		free(inputs);
	}

	return gateList;
}

/*Runs circuit with same inputs until either the circuit has stabilised or the
maximum number of iterations is reached.
@gateList - circuit to stabilise.
*/
bool stabilise_circuit(ArrayList gateList) {
	//Number of wires (excluding one and zero)
	int numWires = sizeOfLinkedList(wires) - 2;

	/*Max number of iterations required to stabilise circuit is (2^wires + 1). Plus
	one is required in case circuit stabilises on the final iteration so that
	it can be checked.*/
	int upperBound = pow(2, numWires) + 1;
	bool stable = false;

	//Iterates from 0 to 2^numWires + 1
	for (int j = 0; j < upperBound; j++) {
		//computes the next state
		gateList = compute_state(gateList);

		//Sets whether circuit is now stable.
		stable = is_stable(gateList);

		//Ends iteration if stable.
		if (stable) return stable;

		//Assigns next state.
		gateList = assign_next_state(gateList);
	}

	return stable;
}

/*
Main function.
*/
int main(void) {

	//Creates a custom array list to store the gateList (i.e. the circuit)
	ArrayList gateList = createArrayList(DEFAULT_CAPACITY);

	//Adds wires of one and zero to list of wires.
	wires = addNode(wires, one);
	wires = addNode(wires, zero);

	//Generates circuit.
	gateList = generate_circuit(gateList);

	//Outputs truth table for circuit.
	output_truth_table(gateList);

	//TODO - comments

	//Frees wires and circuit.
	freeLinkedList(wires);
	freeArrayList(gateList);
    return 0;
}
