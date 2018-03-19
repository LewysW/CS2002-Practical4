#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "gates.h"

/* Make node in list of names.
 */
Names make_names(char* name, Names next) {
	Names names = malloc(sizeof(struct names));
	names->name = name;
	names->next = next;
	return names;
}

/* Free list of names, including the strings in it.
 */
void free_names(Names names) {
	if (names) {
		free(names->name);
		free_names(names->next);
		free(names);
	}
}

/* Print a list of names.
 */
void print_names(Names names) {
	if (names) {
		printf("%s ", names->name);
		print_names(names->next);
	} else {
		putchar('\n');
	}
}

/* Return whether name is in list of names.
 */
int in_names(char* name, Names names) {
	return names && (strcmp(name, names->name) == 0 || in_names(name, names->next));
}

/* Append each possible subset of suffix behind end,
 * then apply action to subset.
 */
void do_for_all_subsets(Names suffix, Names* end, Names* subset, void (*action)(Names)) {
	if (suffix) {
		// first, do not add next name
		do_for_all_subsets(suffix->next, end, subset, action);
		// second, do add next name
		*end = make_names(suffix->name, NULL);
		do_for_all_subsets(suffix->next, &(*end)->next, subset, action);
		free(*end);
		// to be on the safe side, restore end of list
		*end = NULL;
	} else {
		action(*subset);
	}
}

/* Print every subset of list.
 */
void print_all_subsets(Names names) {
	Names subset = NULL;
	do_for_all_subsets(names, &subset, &subset, print_names);
}

/* Parse line with names, ignoring duplicate names,
 * and list all subsets, on separate lines.
 * Do this as long as there are more lines in input.
 */
void process_line(char* line) {
	const char seps[2] = " \n";
	Names names = NULL;
	Names* end = &names;
	char* name;
	name = strtok(line, seps);
	while (name) {
		if (!in_names(name, names)) {
			*end = make_names(strdup(name), NULL);
			end = &(*end)->next;
		}
		name = strtok(NULL, seps);
	}
	print_all_subsets(names);
	free_names(names);
}
