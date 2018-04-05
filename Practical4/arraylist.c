#include "gates.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ArrayList arrayListAdd(ArrayList list, Gate gate) {
    if (list.size == list.capacity) {
        list = arrayListExpand(list);
    }

    //Assigns gate to element at index of current size, then increments size.
    list.gates[list.size++] = gate;

    return list;
}

void printArrayList(ArrayList list) {
    if (list.size <= 0) {
        printf("Empty list\n");
        return;
    }

    for (int i = 0; i < list.size; i++) {
        if (list.gates[i].op && list.gates[i].output) printf("%s, %s", list.gates[i].op, list.gates[i].output->name);

        if (list.gates[i].input1) printf(", %s", list.gates[i].input1->name);

        if (list.gates[i].input2) printf(", %s", list.gates[i].input2->name);

        printf("\n");
    }
}


ArrayList arrayListExpand(ArrayList list) {
    ArrayList newList = createList(list.capacity + 100);

    for (int i = 0; i < list.size; i++) {
        newList.gates[i] = list.gates[i];
    }

    return newList;
}

ArrayList createList(int capacity) {
    if (capacity <= 0) capacity = DEFAULT_CAPACITY;

    ArrayList list;
    list.size = 0;
    list.capacity = capacity;
    list.gates = malloc(capacity * sizeof(Gate));

    return list;
}
