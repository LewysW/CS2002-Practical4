#include "gates.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
Used this source - https://www.hackerearth.com/practice/data-structures/linked-list/singly-linked-list/tutorial/ -
to help implement struct, addNode and createNode
*/

//Creates a new node
Node createNode(void) {
    Node newNode;
    //Allocates memory for node
    newNode = malloc(sizeof(struct LinkedList));

    //Sets attribute value of next to NULL
    newNode->next = NULL;
    return newNode;
}


//Adds a node to the end of a linked list
Node addNode(Node head, Wire* wire) {
    Node newNode;
    Node tail;

    //Creates the node by allocating space and setting initial values.
    newNode = createNode();

    //Sets wire attribute to given wire.
    newNode->wire = wire;

    //If the head of the list is null (so list is empty) then set head to newNode
    if (head == NULL) {
        head = newNode;

    //Otherwise set head to tail
    } else {
        tail = head;

        //And keep updating tail to next element until the end of the list is reached
        while (tail->next != NULL) {
            tail = tail->next;
        }

        /*
        Finally at end of list, set tail->next to newNode and set the index of
        the newNode to 1 greater than the index of tail
        */
        tail->next = newNode;
    }

    return head;
}

int sizeOfLinkedList(Node head) {
    if (head == NULL) return 0;
    else return (sizeOfLinkedList(head->next) + 1);
}

bool linkedListContains(Node head, char* nodeStr) {
    if (head == NULL) {
        return false;
    } else {
        if (!strcmp(head->wire->name, nodeStr)) return true;

        Node newNode = head->next;
        if (newNode != NULL) return linkedListContains(newNode, nodeStr);
    }

    return false;
}

Wire* getNode(Node head, char* nodeStr) {
    if (head == NULL) {
        return NULL;
    } else {
        Node newNode = head->next;
        if (!strcmp(head->wire->name, nodeStr)) return (head->wire);

        if (newNode != NULL) return getNode(newNode, nodeStr);
    }

    return NULL;
}

//Resets value of wires to zero
void reset_wires(Node head) {
	if (head != NULL) {
		head->wire->val = 0;
		head->wire->nextVal = 0;

		reset_wires(head->next);
	}
}

//Recursively frees linked list
void freeLinkedList(Node node) {
    Node newNode = node->next;
    free(node);
    if (newNode != NULL) freeLinkedList(newNode);
}

void printLinkedList(Node node) {
    if (node != NULL) {
        Node newNode = node->next;
        if (newNode != NULL) printLinkedList(newNode);
    }
}
