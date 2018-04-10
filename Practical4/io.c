#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gates.h"


const char* VALID_OPERATORS[8] = {"NOT", "AND", "OR", "NAND", "NOR", "XOR", "EQ", "IN"};

void output_truth_table(ArrayList gateList) {
	print_wire_attributes(gateList, "name");
	bool containsOut = linkedListContains(wires, "out");
	if (containsOut) printf("out");
	printf("\n");

	//increments over inputs and checks if stable
	int numInputs = pow(2, get_num_IN(gateList));
	for (int i = 0; i < numInputs; i++) {
		//Updates inputs with new bits
		gateList = update_inputs(gateList, i);

		print_wire_attributes(gateList, "val");
		bool stable = stabilise_circuit(gateList);
		print_circuit_output(stable, containsOut);
		reset_wires(wires);
	}
}

void print_circuit_output(bool stable, bool containsOut) {
	if(stable) {
		if(containsOut) printf("%d\n", getNode(wires, "out")->val);
		else printf("0\n");
	} else printf("?\n");
}

void print_wire_attributes(ArrayList gateList, char* attr) {
	for (int i = 0; i < gateList.size; i++) {
		if (!strcmp(gateList.gates[i].op, "IN")) {
			if (!strcmp(attr, "name")) printf("%s ", gateList.gates[i].output->name);
			else if (!strcmp(attr, "val")) printf("%d ", gateList.gates[i].output->val);
		}
	}
}

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

//TODO - mention as extension
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
