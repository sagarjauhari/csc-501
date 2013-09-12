#include "threadq.h"
#include "mythread.h"
#include <stdlib.h>
#include <stdio.h>
#include <ucontext.h>

Node * q_create(){
	Node *new = (Node *) malloc(sizeof(Node));
	memset(new,0,sizeof(Node));
	return new;
}

void q_insert(_MyThread *thread, Node *head){
	Node *new = (Node *) malloc(sizeof(Node));
	memset(new,0,sizeof(Node));
	Node *current = head;
	while(current -> this_t){
		current = current -> next;
	}
	current -> this_t = thread;
	current -> next = new;
}

void q_set_tail_context(ucontext_t *context, Node *head){
	//If Q doesn't have any elements, then just return

	//Node *new = (Node *) malloc(sizeof(Node));
	Node *current = head;
	if(!current -> this_t){
		return;
	}
	
	while(current -> next){
		current = current -> next;
	}
	
	#ifdef DEBUG
		printf(COLOR_ON "Setting tail uclink: t%d" COLOR_OFF,
			current->this_t->id);
	#endif
	current -> this_t ->context_t -> uc_link = context;
}

_MyThread * q_remove(Node *head){
	_MyThread *t = &(head->this_t);
	Node *temp = head;
	head = head -> next;
	free(temp);
	return t;
}

void q_print(Node *head, int type){
	printf(COLOR_ON);
	int count = 0;
	Node* temp = head;
	while(temp->this_t){
		++count;
		printf("%d ",temp->this_t->id);
		temp = temp -> next;
	}
	printf(" - (Total=%d)\n",count);
	printf(COLOR_OFF);
}
