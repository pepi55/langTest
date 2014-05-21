#include <stdio.h>

#include "linkedList.h"

const struct iStackClass iStack = {
	.push = &push
};

void push (int data) {
	iNode *newNode;
	newNode->data = data;
	newNode->next = NULL;

	if (.size == 0) {
	}
}

static struct iStack peek () {
	if (.tail != NULL) {
		return .tail->data;
	}
}
