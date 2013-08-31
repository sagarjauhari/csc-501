#ifndef THREADQ_H
#define THREADQ_H

#include "mythread.h"

typedef struct node{
	MyThread this_t;
	struct node *next;
} Node;

Node *create_q();

void insert_q(MyThread *thread, Node *head);

MyThread *remove_q(Node *head);


#endif /* THREADQ_H */
