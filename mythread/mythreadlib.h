#ifndef MYTHREADLIB_H
#define MYTHREADLIB_H

#include <ucontext.h>

#define STACK_SIZE 8192 //8KB

typedef struct _MyThread_{
	struct _MyThread_ *child; 		//head of list of children
	struct _MyThread_ *next_sib; 	//next sibling
	struct _MyThread_ *parent; 		//parent
	ucontext_t *context_t;
	int blocked_on_join;
	int blocked_on_join_all;
	int id; //1 is for main thread
} _MyThread;

typedef struct q_node_{
	_MyThread * this_t;
	struct q_node_ * next;
} Node;

/**
typedef struct ready_q_{
	q_node * head;
} ready_q;

typedef struct block_q_{
	q_node * head;
} block_q;

**/
#endif //MYTHREADLIB_H
