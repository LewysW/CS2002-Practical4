#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "gates.h"

Wire make_wire(char* str, int value) {
	Wire wire;
	wire.name = malloc(sizeof(str));
	wire.name = str;
	wire.value = value;
	return wire;
}

Gate make_gate(Wire input1, Wire input2, char* name) {
    Gate gate;
    gate.op = malloc(sizeof(name));
    gate.op = name;
    gate.inputs[0] = input1;
    gate.inputs[1] = input2;
    gate.output = getOutput(gate);
    return gate;
}

Wire getOutput(Gate gate) {
    int value;

    if (gate.op == "NOT") {
        value = !(gate.inputs[0].value);
        return make_wire("out", value);
    } else if (gate.op == "AND") {
        value = (gate.inputs[0].value == 1 && gate.inputs[1].value == 1);
        return make_wire("out", value);
    } else if (gate.op == "OR") {
        value = (gate.inputs[0].value == 1 || gate.inputs[1].value == 1);
        return make_wire("out", value);
    } else if (gate.op == "NAND") {
        value = !(gate.inputs[0].value == 1 && gate.inputs[1].value == 1);
        return make_wire("out", value);
    } else if (gate.op == "NOR") {
        value = !(gate.inputs[0].value == 1 || gate.inputs[1].value == 1);
        return make_wire("out", value);
    }  else if (gate.op == "XOR") {
        value = (gate.inputs[0].value == 1 ^ gate.inputs[1].value == 1);
        return make_wire("out", value);
    }

    //Add assert or error message here.
    return;
}

/* Read lines from standard input, until user types Ctrl-D.
 */
int main(void) {
	char* line = NULL;
	size_t len = 0;
	while (getline(&line, &len, stdin) != -1)
		process_line(line);
	free(line);

	Wire one = make_wire("one", 1);
	Wire zero = make_wire("zero", 0);
	printf("Name: %s, Value: %d\n", one.name, one.value);
	printf("Name: %s, Value: %d\n", zero.name, zero.value);

    Gate gate;
    gate = make_gate(one, one, "XOR");
    printf("Name: %s, Input: %d, Input: %d, Output: %d\n", gate.op, gate.inputs[0].value, gate.inputs[1].value, gate.output.value);
    return 0;
}
