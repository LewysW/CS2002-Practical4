#define _GNU_SOURCE

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gates.h"

//Sets values for one and zero wires
Wire zero_wire = {"zero", 0};
Wire one_wire = {"one", 1};

Wire* zero = &zero_wire;
Wire* one =  &one_wire;

//Initialises a wire*
Wire* make_wire(char* str, int value) {
	Wire* wire = malloc(sizeof(Wire));
	wire->name = str;
	wire->value = value;
	return wire;
}

//Initialises a gate struct
Gate make_gate(char* output, char* operator, Wire* input1, Wire* input2) {
    Gate gate;
    gate.op = malloc(sizeof(operator));
    gate.op = operator;

	if (strcmp(operator, "IN")) {
		gate.input1 = malloc(sizeof(Wire));
	    gate.input1 = input1;
	}

    if (strcmp(operator, "NOT")) {
		gate.input2 = malloc(sizeof(Wire));
		gate.input2 = input2;
	}

    gate.output = (get_output(gate, output));
    return gate;
}

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
		stream = fopen(argv[0], "r");
	}

	char** inputs;
	char* line = NULL;
	size_t len = 0;
	while (getline(&line, &len, stdin) != -1) {
		tokenize_line(line, inputs);

		if (valid_expression(inputs)) {
			Gate gate;
		    gate = make_gate(*(inputs + OUTPUT), *(inputs + OPERATOR), one, one);
			printf("Output: %s, Operator: %s, Input1: %s, Input2: %s\n", gate.output->name, gate.op, gate.input1->name, gate.input2->name);
			printf("%d\n", gate.output->value);
		}
	}

	free(line);

    return 0;
}
