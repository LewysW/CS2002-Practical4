#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gates.h"

//List of valid operators.
const char* VALID_OPERATORS[8] = {"NOT", "AND", "OR", "NAND", "NOR", "XOR", "EQ", "IN"};

/*Outputs the truth table of a given circuit
@gateList - circuit to be printed as a truth table.
*/
void output_truth_table(ArrayList gateList) {
	//Prints names of wires to be displayed
	print_wire_attributes(gateList, "name");
	//Checks if a wire named out exists.
	bool containsOut = linkedListContains(wires, "out");
	//Print out if there is a wire called out
	if (containsOut) printf("out");
	printf("\n");

	//Increments of possible inputs to IN gates
	int numInputs = pow(2, get_num_IN(gateList));
	for (int i = 0; i < numInputs; i++) {
		//Updates inputs with new bits
		gateList = update_inputs(gateList, i);

		//Prints values of each wire to be displayed.
		print_wire_attributes(gateList, "val");

		//Checks if circuit has been stabilised
		bool stable = stabilise_circuit(gateList);
		//Print overall output of circuit with current inputs.
		print_circuit_output(stable, containsOut);
		//Reset wires to 0
		reset_wires(wires);
	}
}

/*Prints value of output of circuit (either value of 'out', 0, or ?)
@stable - whether circuit is stable
@containsOut - whether circuit contains a wire with the name 'out'
*/
void print_circuit_output(bool stable, bool containsOut) {
	if(stable) {
		//If a wire is called 'out' then print value of wire, else print 0
		if(containsOut) printf("%d\n", getNode(wires, "out")->val);
		else printf("0\n");
	//If not stable print '?'
	} else printf("?\n");
}

/*Prints the specified attribute of output wire of IN gates in the circuit.
@gateList - circuit
@attr - attribute of IN wire to be printed.
*/
void print_wire_attributes(ArrayList gateList, char* attr) {
	//Iterates over every gate in circuit
	for (int i = 0; i < gateList.size; i++) {
		//If gate operator is 'IN'
		if (!strcmp(gateList.gates[i].op, "IN")) {
			//If attribute is 'name' then print output wire name.
			if (!strcmp(attr, "name")) printf("%s ", gateList.gates[i].output->name);
			//Else if attribute is 'val' then print output wire value.
			else if (!strcmp(attr, "val")) printf("%d ", gateList.gates[i].output->val);
		}
	}
}

/*Populates a string input array with two to four tokens depending on the operator
of the gate input.
@line - line to tokenize.
@inputs - array of strings to populate with tokens for output, operator, input1 and input2
*/
void tokenize_line(char* line, char* inputs[]) {
	//Store seperator characters in string (size 3 to allow for \0)
	const char seps[3] = " \n";
	int index = 0;

	//Initialises tokens to NULL (used to validate IN and NOT gates)
	for (int i = 0; i == NUM_TOKENS; i++) {
		inputs[i] = NULL;
	}

	//Sets first element of inputs to output token
	inputs[index++] = strtok(line, seps);
	//Gets additional tokens while tokens are not NULL and number tokens is not
	//equal to 5 (one extra token is parsed to reject user input if they enter more than 4 tokens).
	while (index != (NUM_TOKENS + 1)) (inputs[index++] = strtok(NULL, seps));
}

/*Checks that tokenized operator is valid (is contained in list of valid operators)
@operator - operator to be validated.
*/
bool valid_operator(char* operator) {
	/*Iterates through valid operators list and returns true if operator equals
	one of the operators in the list.*/
	for (unsigned int i = 0; i < sizeof(VALID_OPERATORS) / sizeof(VALID_OPERATORS[0]); i++) {
		if (!strcmp(operator, VALID_OPERATORS[i])) return true;
	}

	//Otherwise return false.
	return false;
}

//TODO - mention as extension
//INPUT VALIDATION EXTENSION
/*Validates entered expressions
@expression[] - expression to validate.
@gateList - circuit
*/
bool valid_expression(char* expression[], ArrayList gateList) {
	//Returns false if operator is NULL or not in valid list of operators.
	if (expression[OPERATOR] == NULL || !valid_operator(expression[OPERATOR])) {
		printf("Invalid Operator\n");
		return false;
	}

	//If fifth token has been entered return false;
	if (expression[NUM_TOKENS] != NULL) {
		printf("Invalid Number of Tokens.\n");
		return false;
	}

	//If output wire is one or zero then return false.
	if (!strcmp(expression[OUTPUT], "one") || !strcmp(expression[OUTPUT], "zero")) {
		printf("'one' and 'zero' are invalid output names\n");
		return false;
	}

	/*If the output wire specified in the expression already exists and is used
	as the output of another wire then return false.*/
	Wire* wire = getNode(wires, expression[OUTPUT]);
	if (wire != NULL) {
		for (int i = 0; i < gateList.size; i++) {
			if (gateList.gates[i].output == wire) {
				printf("Cannot Create Duplicate Output Wire\n");
				return false;
			}
		}
	}

	int firstInput = expression[INPUT_ONE] != NULL;
	int secondInput = expression[INPUT_TWO] != NULL;

	//If inputs are NULL and operator is not NULL return false.
	if (!firstInput && !secondInput && strcmp("IN", expression[OPERATOR])) {
		printf("Invalid Number of Tokens.\n");
		return false;
	}

	//If only second input is NULL and operator is anything but NOT return false.
	if (firstInput && !secondInput && strcmp("NOT", expression[OPERATOR])) {
		printf("Invalid Number of Tokens.\n");
		return false;
	}

	//If both inputs are not NULL and the operator is IN or NOT then return false.
	if (firstInput && secondInput && (!strcmp("IN", expression[OPERATOR]) || !strcmp("NOT", expression[OPERATOR]))) {
		printf("Invalid Number of Tokens.\n");
		return false;
	}

	return true;
}
