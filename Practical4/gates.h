#ifndef HEADER
#define HEADER

/* Node in list of names.
 */
typedef struct names {
	char* name;
	struct names* next;
} *Names;

typedef struct Wire {
    char* name;
    int value;
} Wire;

typedef struct Gate {
    char* op;
    Wire output;
    Wire inputs[2];
} Gate;

Wire make_wire(char* str, int value);
Names make_names(char* name, Names next);
void free_names(Names names);
void print_names(Names names);
int in_names(char* name, Names names);
void do_for_all_subsets(Names suffix, Names* end, Names* subset, void (*action)(Names));
void print_all_subsets(Names names);
void process_line(char* line);
Wire get_output(Gate gate);
Gate make_gate(Wire input1, Wire input2, char* name);


#endif
