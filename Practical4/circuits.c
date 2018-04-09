 //Included to avoid implicit getline declaration
#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gates.h"

//Sets vals for one and zero wires
Wire zero_wire = (Wire){"zero", 0, 0};
Wire one_wire = (Wire){"one", 1, 1};

Wire* zero = &zero_wire;
Wire* one =  &one_wire;

//Initialises a wire*
Wire* make_wire(char* str, int val) {
	Wire* wire = malloc(sizeof(Wire));
	wire->name = strdup(str);
	wire->val = val;
	wire->nextVal = 0;
	return wire;
}


Wire* get_wire(char* wireStr) {
	if (!linkedListContains(wires, wireStr)) {
		Wire* wire = make_wire(wireStr, 0);
		wires = addNode(wires, wire);
		return wire;
	} else {
		return getNode(wires, wireStr);
	}
}

//Initialises a gate struct
Gate make_gate(char* output, char* operator, char* input1, char* input2) {
    Gate gate;
	gate.output = NULL;
	gate.op = NULL;
	gate.input1 = NULL;
	gate.input2 = NULL;

    gate.op = strdup(operator);

	if (strcmp(operator, "IN")) {
		gate.input1 = get_wire(input1);
	}

    if (strcmp(operator, "NOT") && strcmp(operator, "IN")) {
		gate.input2 = get_wire(input2);
	}

    gate.output = (get_wire(output));

    return gate;
}

//Gets the output of a gate based on the operator name
int get_output(Gate prev) {
	Gate gate = prev;

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

ArrayList compute_state(ArrayList gateList) {
	for (int i = 0; i < gateList.size; i++) {
		gateList.gates[i].output->nextVal = get_output(gateList.gates[i]);
	}

	return gateList;
}

ArrayList assign_next_state(ArrayList gateList) {
	for (int i = 0; i < gateList.size; i++) {
		gateList.gates[i].output->val = gateList.gates[i].output->nextVal;
	}
	return gateList;
}

//TODO -move to IO
void print_state(ArrayList gateList, bool isStable) {
	for (int i = 0; i < gateList.size; i++) {
		if (!strcmp(gateList.gates[i].op, "IN")) {
			printf("%d ", gateList.gates[i].output->val);
		} else if(!strcmp(gateList.gates[i].output->name, "out")) {
			if (isStable) printf("%d", gateList.gates[i].output->val);
			else printf("?");
		}
	}

	printf("\n");
}

ArrayList update_inputs(ArrayList gateList, int dec) {
	int* inputs;
	inputs = dec_to_binary(dec, get_num_IN(gateList));
	int bit = 0;

	for (int i = 0; i < gateList.size; i++) {
		if (!strcmp(gateList.gates[i].op, "IN")) {
			gateList.gates[i].output->val = *(inputs + (bit++));
		}
	}

	return gateList;
}

bool is_stable(ArrayList gateList) {
	for (int i = 0; i < gateList.size; i++) {
		if ((gateList.gates[i].output->val) != (gateList.gates[i].output->nextVal)) return false;
	}

	return true;
}


int* dec_to_binary(int dec, int numBits) {
	//Gets number of bits using logarithms
	int* binary = calloc(numBits, sizeof(int));

	for (int i = 0; i < numBits; i++) binary[i] = 0;

	for (int i = numBits - 1; dec > 0; i--) {
		binary[i] = dec % 2;
		dec = dec / 2;
	}

	return binary;
}

int get_num_IN(ArrayList gateList) {
	int numIN = 0;

	for (int i = 0; i < gateList.size; i++) {
		if (!strcmp(gateList.gates[i].op, "IN")) numIN++;
	}

	return numIN;
}

ArrayList generate_circuit(ArrayList gateList) {
	char** inputs;
	char* line = NULL;
	size_t len = 0;

	while (getline(&line, &len, stdin) != -1) {
		inputs = malloc(sizeof(char*) * NUM_TOKENS);
		tokenize_line(line, inputs);

		if (valid_expression(inputs, gateList)) {
			gateList = arrayListAdd(gateList, make_gate(*(inputs + OUTPUT), *(inputs + OPERATOR), *(inputs + INPUT_ONE), *(inputs + INPUT_TWO)));
		} else {
			printf("Invalid Input\n");
		}

		free(line);
		free(inputs);
	}

	return gateList;
}


/* Read lines from standard input, until user types Ctrl-D.
 */
int main(void) {

	//Creates a custom array list to store the gates
	ArrayList gateList = createArrayList(DEFAULT_CAPACITY);
	wires = addNode(wires, one);
	wires = addNode(wires, zero);

	gateList = generate_circuit(gateList);
	output_truth_table(gateList);

	//TODO - change loop condition for stabilisation or upper bound of iterations
	//TODO - print properly (display 0 or ? if no out value)
	//TODO - separate code into files
	//TODO - comments


	freeLinkedList(wires);
	freeArrayList(gateList);
    return 0;
}
