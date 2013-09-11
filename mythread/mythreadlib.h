#ifndef MYTHREADLIB_H
#define MYTHREADLIB_H

#include <ucontext.h>

#define STACK_SIZE 8192 //8KB

#define COLOR_ON    "\x1b[32m"
#define COLOR_OFF   "\x1b[0m"

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

#endif //MYTHREADLIB_H
