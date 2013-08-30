#ifndef THREADQ_H
#define THREADQ_H

#include "mythread.h"

typedef struct node{
	MyThread this_t;
	struct node *next;
} Node;

Node *create();

void insert(MyThread *thread, Node *head);

MyThread *remove(Node *head);


#endif /* THREADQ_H */
