#define _GNU_SOURCE

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gates.h"

//Sets values for one and zero wires
Wire zero_wire = (Wire){"zero", 0};
Wire one_wire = (Wire){"one", 1};

Wire* zero = &zero_wire;
Wire* one =  &one_wire;

Node wires = NULL;

//Initialises a wire*
Wire* make_wire(char* str, int value) {
	Wire* wire = malloc(sizeof(Wire));
	wire->name = strdup(str);
	wire->value = value;
	return wire;
}

Wire* get_wire(char* wireStr) {
	if (!contains(wires, wireStr)) {
		Wire* wire = make_wire(wireStr, -1);
		wires = addNode(wires, wire);
		return wire;
	} else {
		return getNode(wires, wireStr);
	}
}

//Initialises a gate struct
Gate make_gate(char* output, char* operator, char* input1, char* input2) {
    Gate gate;
    gate.op = strdup(operator);

	if (strcmp(operator, "IN")) {
		gate.input1 = malloc(sizeof(Wire));
		gate.input1 = get_wire(input1);
	}

    if (strcmp(operator, "NOT")) {
		gate.input2 = malloc(sizeof(Wire));
		gate.input2 = get_wire(input2);
	}

    gate.output = (get_output(gate, output));
    return gate;
}

//TODO change make_wire for output wire to get_wire
//Gets the output of a gate based on the operator name
Wire* get_output(Gate gate, char* output) {
    int value;

    if (!strcmp(gate.op, "NOT")) {
        value = !(gate.input1->value);
        return make_wire(output, value);
    } else if (!strcmp(gate.op, "AND")) {
        value = (gate.input1->value && gate.input2->value);
        return make_wire(output, value);
    } else if (!strcmp(gate.op, "OR")) {
        value = (gate.input1->value || gate.input2->value);
        return make_wire(output, value);
    } else if (!strcmp(gate.op, "NAND")) {
        value = !(gate.input1->value && gate.input2->value);
        return make_wire(output, value);
    } else if (!strcmp(gate.op, "NOR")) {
        value = !(gate.input1->value || gate.input2->value);
        return make_wire(output, value);
    }  else if (!strcmp(gate.op, "XOR")) {
        value = (gate.input1->value ^ gate.input2->value);
        return make_wire(output, value);
    } else if (!strcmp(gate.op, "NOT")) {
        value = !(gate.input1->value ^ gate.input2->value);
        return make_wire(output, value);
    } else if (!strcmp(gate.op, "IN")) {
		return make_wire(output, -1); //Default value for IN
	}

    //Add assert or error message here.
    return NULL;
}


/* Read lines from standard input, until user types Ctrl-D.
 */
int main(int argc, char *argv[]) {
	FILE* stream;
	if (argc == 1) {
		stream = stdin;
	} else {
		stream = fopen(argv[1], "r");
	}

	char** inputs;
	char* line = NULL;
	size_t len = 0;

	//TODO - CHANGE stdin TO STREAM TO ALLOW FOR EITHER USER INPUT OR FILE IO
	while (getline(&line, &len, stdin) != -1) {
		tokenize_line(line, inputs);


		if (valid_expression(inputs)) {
			Gate gate = make_gate(*(inputs + OUTPUT), *(inputs + OPERATOR), *(inputs + INPUT_ONE), *(inputs + INPUT_TWO));
		}
	}

	printList(wires);
	free(line);
    return 0;
}
