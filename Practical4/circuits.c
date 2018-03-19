#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "gates.h"

static const Wire zero = {"zero", 0};
static const Wire one = {"one", 1};

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
    if (name != "NOT") gate.inputs[1] = input2;

    gate.output = get_output(gate);
    return gate;
}

Wire get_output(Gate gate) {
    int value;

    if (gate.op == "NOT") {
        value = !(gate.inputs[0].value);
        return make_wire("out", value);
    } else if (gate.op == "AND") {
        value = (gate.inputs[0].value && gate.inputs[1].value);
        return make_wire("out", value);
    } else if (gate.op == "OR") {
        value = (gate.inputs[0].value || gate.inputs[1].value);
        return make_wire("out", value);
    } else if (gate.op == "NAND") {
        value = !(gate.inputs[0].value && gate.inputs[1].value);
        return make_wire("out", value);
    } else if (gate.op == "NOR") {
        value = !(gate.inputs[0].value || gate.inputs[1].value);
        return make_wire("out", value);
    }  else if (gate.op == "XOR") {
        value = (gate.inputs[0].value ^ gate.inputs[1].value);
        return make_wire("out", value);
    } else if (gate.op == "EQ") {
        value = (!(gate.inputs[0].value) || (gate.inputs[1].value));
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

    Gate gate;
    gate = make_gate(one, zero, "NOT");
    printf("Output: %d\n", gate.output.value);
    return 0;
}
