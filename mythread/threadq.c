#include "threadq.h"
#include "mythread.h"
#include <stdlib.h>
#include <stdio.h>

Node *q_create(){
	Node *new = (Node *) malloc(sizeof(Node));
	return new;
}

void q_insert(_MyThread *thread, Node *head){
	Node *new = (Node *) malloc(sizeof(Node));
	Node *current = head;
	while(current -> this_t){
		current = current -> next;
	}

	current -> this_t = thread;
	current -> next = new;
}

_MyThread * q_remove(Node *head){
	_MyThread *t = &(head->this_t);
	Node *temp = head;
	head = head -> next;
	free(temp);
	return t;
}

void q_print(Node *head, int type){
	int count;
	Node* temp = head;
	if(type==0){
		printf("RQ: ");
	}else{
		printf("BQ: ");
	}
	while(temp->this_t){
		++count;
		printf("%d ",temp->this_t->id);
		temp = temp -> next;
	}
	printf(" - (Total=%d)\n",count);
}
