#include "threadq.h"
#include "mythread.h"
#include <stdlib.h>

Node *create(){
	Node *new = (Node *) malloc(sizeof(Node));
	return new;
}

void insert(MyThread *thread, Node *head){
	Node *new = (Node *) malloc(sizeof(Node));
	Node *current = head;
	while(current -> this_t){
		current = current -> next;
	}

	current -> this_t = *thread;
	current -> next = new;
}

MyThread *remove(Node *head){
	MyThread *t = &(head->this_t);
	Node *temp = head;
	head = head -> next;
	free(temp);

	return t;
}
