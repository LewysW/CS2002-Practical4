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
	if (!contains(wires, wireStr)) {
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
		gate.input1 = malloc(sizeof(Wire));
		gate.input1 = get_wire(input1);
	}

    if (strcmp(operator, "NOT") && strcmp(operator, "IN")) {
		gate.input2 = malloc(sizeof(Wire));
		gate.input2 = get_wire(input2);
	}

    gate.output = (get_wire(output));

    return gate;
}

//Gets the output of a gate based on the operator name
int get_output(Gate prev) {
    int val;
	Gate gate = prev;

    if (!strcmp(gate.op, "NOT")) return !(gate.input1->val);
    else if (!strcmp(gate.op, "AND")) return (gate.input1->val && gate.input2->val);
    else if (!strcmp(gate.op, "OR")) return (gate.input1->val || gate.input2->val);
    else if (!strcmp(gate.op, "NAND")) return !(gate.input1->val && gate.input2->val);
	else if (!strcmp(gate.op, "NOR")) return !(gate.input1->val || gate.input2->val);
    else if (!strcmp(gate.op, "XOR")) return (gate.input1->val ^ gate.input2->val);
    else if (!strcmp(gate.op, "EQ")) return !(gate.input1->val ^ gate.input2->val);
	else if (!strcmp(gate.op, "IN")) return gate.output->val;
	//TODO - change IN for all combinations of inputs
	return -1;
}

ArrayList compute_state(ArrayList gateList) {
	for (int i = 0; i < gateList.size; i++) {
		gateList.gates[i].output->nextVal = get_output(gateList.gates[i]);
	}

	for (int i = 0; i < gateList.size; i++) {
		gateList.gates[i].output->val = gateList.gates[i].output->nextVal;
	}

	return gateList;
}




/* Read lines from standard input, until user types Ctrl-D.
 */
int main(void) {

	//Creates a custom array list to store the gates
	ArrayList gateList = createList(DEFAULT_CAPACITY);
	wires = addNode(wires, one);
	wires = addNode(wires, zero);

	char** inputs;
	char* line = NULL;
	size_t len = 0;
	int index = 0;

	//TODO - CHANGE stdin TO STREAM TO ALLOW FOR EITHER USER INPUT OR FILE IO
	while (getline(&line, &len, stdin) != -1) {
		inputs = malloc(sizeof(char*) * NUM_TOKENS);
		tokenize_line(line, inputs);

		if (valid_expression(inputs, gateList)) {
			gateList = arrayListAdd(gateList, make_gate(*(inputs + OUTPUT), *(inputs + OPERATOR), *(inputs + INPUT_ONE), *(inputs + INPUT_TWO)));
		} else {
			printf("Invalid Input\n");
		}
	}

	//TODO - change loop condition for stabilisation or upper bound of iterations
	while (index < 20) {
		gateList = compute_state(gateList);
		printf("%s: %d\n", gateList.gates[index % 4].output->name ,gateList.gates[index % 4].output->val);
		index++;
	}

	free(inputs);
	printLinkedList(wires);
	printArrayList(gateList);
	free(line);
    return 0;
}
