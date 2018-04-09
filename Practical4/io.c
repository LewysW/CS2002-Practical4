#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gates.h"

const char* VALID_OPERATORS[8] = {"NOT", "AND", "OR", "NAND", "NOR", "XOR", "EQ", "IN"};
//Gets maximum of four tokens from input line
void tokenize_line(char* line, char* inputs[]) {
	const char seps[2] = " \n";
	int index = 0;

	for (int i = 0; i < NUM_TOKENS; i++) {
		inputs[i] = NULL;
	}

	inputs[index++] = strtok(line, seps);
	while (((inputs[index++] = strtok(NULL, seps)) != NULL) && index <= NUM_TOKENS);
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
	if (expression[OPERATOR] == NULL || !valid_operator(expression[OPERATOR])) return false;

	if (!strcmp(expression[OUTPUT], "one") || !strcmp(expression[OUTPUT], "zero")) return false;

	Wire* wire = getNode(wires, expression[OUTPUT]);

	if (wire != NULL) {
		for (int i = 0; i < gateList.size; i++) {
			if (gateList.gates[i].output == wire)
				return false;
		}
	}

	if (strcmp("IN", expression[OPERATOR]) && strcmp("NOT", expression[OPERATOR]) && (expression[INPUT_ONE] == NULL || expression[INPUT_TWO] == NULL)) return false;

	if (!strcmp("IN", expression[OPERATOR]) && expression[INPUT_ONE] != NULL) return false;

	if (!strcmp("NOT", expression[OPERATOR]) && expression[INPUT_TWO] != NULL) return false;

	return true;
}
