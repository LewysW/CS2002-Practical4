#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "gates.h"


const char* VALID_OPERATORS[8] = {"NOT", "AND", "OR", "NAND", "NOR", "XOR", "EQ", "IN"};

void output_truth_table(ArrayList gateList) {
	int numWires = sizeOfLinkedList(wires) - 2; //Num wires excluding one and zero
	int upperBound = pow(2, numWires); //Upper bound of iteration for each input

	//TODO - MOVE - Prints variable name
	for (int i = 0; i < gateList.size; i++) {
		if (!strcmp(gateList.gates[i].op, "IN")) {
			printf("%s ", gateList.gates[i].output->name);
		}
	}

	//TODO - MOVE - checks for out for final output
	bool containsOut = linkedListContains(wires, "out");
	if (containsOut) printf("out");
	printf("\n");

	//TODO - increments over inputs and checks if stable
	int num_possibility = pow(2, get_num_IN(gateList));
	for (int i = 0; i < num_possibility; i++) {
		bool stable = false;
		//Updates inputs with new bits
		gateList = update_inputs(gateList, i);

		//TODO - MOVE -Outputs bits of each IN being tested
		for (int i = 0; i < gateList.size; i++) {
			if (!strcmp(gateList.gates[i].op, "IN")) {
				printf("%d ", gateList.gates[i].output->val);
			}
		}

		//TODO - MOVE - computes the next state and checks if stable
		for (int j = 0; j < upperBound; j++) {
			gateList = compute_state(gateList);

			stable = is_stable(gateList);
			if (stable) break;
			gateList = assign_next_state(gateList);
		}

		//TODO - MOve - prints value of out, 0 or ?
		if(stable) {
			if(containsOut) printf("%d\n", getNode(wires, "out")->val);
			else printf("0\n");
		}
		else printf("?\n");
		reset_wires(wires);
	}
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

//TODO - mentioned as extension
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
