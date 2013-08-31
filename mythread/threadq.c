#include "threadq.h"
#include "mythread.h"
#include <stdlib.h>

Node *create_q(){
	Node *new = (Node *) malloc(sizeof(Node));
	return new;
}

void insert_q(MyThread *thread, Node *head){
	Node *new = (Node *) malloc(sizeof(Node));
	Node *current = head;
	while(current -> this_t){
		current = current -> next;
	}

	current -> this_t = *thread;
	current -> next = new;
}

MyThread *remove_q(Node *head){
	MyThread *t = &(head->this_t);
	Node *temp = head;
	head = head -> next;
	free(temp);

	return t;
}
