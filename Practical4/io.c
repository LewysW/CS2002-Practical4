#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gates.h"

const char* VALID_OPERATORS[8] = {"NOT", "AND", "OR", "NAND", "NOR", "XOR", "EQ", "IN"};
//Gets maximum of four tokens from input line
void tokenize_line(char* line, char* inputs[]) {
	const char seps[3] = "  \n";
	int index = 0;

	for (int i = 0; i < NUM_TOKENS; i++) {
		inputs[i] = NULL;
	}

	inputs[index++] = strtok(line, seps);
	while ((inputs[index++] = strtok(NULL, seps)) != NULL);
}

//Checks that an operator is valid
bool valid_operator(char* operator) {
	for (unsigned int i = 0; i < sizeof(VALID_OPERATORS) / sizeof(VALID_OPERATORS[0]); i++) {
		if (!strcmp(operator, VALID_OPERATORS[i])) return true;
	}

	return false;
}

//Checks that an expression is valid
bool valid_expression(char* expression[], ArrayList gateList) {
	if (!valid_operator(expression[OPERATOR])) return false;

	Wire* wire = getNode(wires, expression[OUTPUT]);


	if (wire != NULL) {
		for (int i = 0; i < gateList.size; i++) {
			if (gateList.gates[i].output == wire)
				return false;
		}
	}

	if (!strcmp("IN", expression[OPERATOR]) && expression[INPUT_ONE] != NULL) return false;

	if (!strcmp("NOT", expression[OPERATOR]) && expression[INPUT_TWO] != NULL) return false;

	return true;
}
