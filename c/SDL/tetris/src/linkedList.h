#pragma once

#define LINKED_LIST_H

struct iNode {
	int data;
	iNode *next;
};

struct iStack {
	iNode *head, *tail;

	int size;
};

extern const struct iStackClass {
	void (*push)(int data);
	void (*pop)();
	struct iStack (*peek)();

	int (*getSize)();
} iStack;
