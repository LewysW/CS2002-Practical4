#include "gates.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Adds gate to arrayList
@list - arrayList to add gate to.
@gate - gate to add.
*/
ArrayList arrayListAdd(ArrayList list, Gate gate) {
    //If list is at capacity, then expand list.
    if (list.size == list.capacity) {
        list = arrayListExpand(list);
    }

    //Assigns gate to element at index of current size, then increments size.
    list.gates[list.size++] = gate;

    return list;
}

/*Creates a new array list with more space and copies elements over if number
of gates exceeds DEFAULT_CAPACITY
@list - arrayList to expand.
*/
ArrayList arrayListExpand(ArrayList list) {
    //Creates a larger arrayList
    ArrayList newList = createArrayList(list.capacity + MORE_SPACE);

    //Copies elements from list to newList
    for (int i = 0; i < list.size; i++) {
        newList.gates[i] = list.gates[i];
    }

    return newList;
}

/*Creates an arrayList with a given capacity or DEFAULT_CAPACITY.
@capacity - max size to initialise arrayList to.
*/
ArrayList createArrayList(int capacity) {
    //Use DEFAULT_CAPACITY if invalid capacity specified.
    if (capacity <= 0) capacity = DEFAULT_CAPACITY;

    //Sets initial attributes
    ArrayList list;
    list.size = 0;
    list.capacity = capacity;
    list.gates = malloc(capacity * sizeof(Gate));

    return list;
}

//Frees each gate in the given arrayList
void freeArrayList(ArrayList list) {
    for (int i = 0; i < list.size; i++) {
        free(list.gates[i].op);
    }

    free(list.gates);
}
