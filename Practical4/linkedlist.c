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

/*Counts size of linked list
@head - first node of list
*/
int sizeOfLinkedList(Node head) {
    if (head == NULL) return 0;
    else return (sizeOfLinkedList(head->next) + 1);
}

/*Returns boolean signifying whether wire with given name is in linked list.
@head - first node of linked list.
@nodeStr - wire to find.
*/
bool linkedListContains(Node head, char* nodeStr) {
    //If first element equals NULL (before wire is found) return false
    if (head == NULL) {
        return false;
    } else {
        //If nodeStr matches wire name then return true
        if (!strcmp(head->wire->name, nodeStr)) return true;

        //Recursively call function until equal to nodeStr or NULL
        Node newNode = head->next;
        if (newNode != NULL) return linkedListContains(newNode, nodeStr);
    }

    return false;
}

/*Gets a node given a node's name
@head - first node in list
@nodeStr - name of node
*/
Wire* getNode(Node head, char* nodeStr) {
    //Returns NULL if head is NULL
    if (head == NULL) {
        return NULL;
    } else {
        Node newNode = head->next;

        //Returns wire if found
        if (!strcmp(head->wire->name, nodeStr)) return (head->wire);

        //Recursively calls getNode until found or NULL
        if (newNode != NULL) return getNode(newNode, nodeStr);
    }

    return NULL;
}

/*Resets value and next value of wire if wire is not 'one'
@head - first node of linked list
*/
void reset_wires(Node head) {
    //If head is not NULL
	if (head != NULL) {
        //Skips reseting of wire if name is one
        if (strcmp(head->wire->name, "one")) {
            head->wire->val = 0;
    		head->wire->nextVal = 0;
        }

        //recursively reset wires
		reset_wires(head->next);
	}
}

//Recursively frees linked list
void freeLinkedList(Node node) {
    Node newNode = node->next;
    free(node);
    if (newNode != NULL) freeLinkedList(newNode);
}
