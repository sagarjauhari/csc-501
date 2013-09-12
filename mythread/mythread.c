#include <stdlib.h>
#include <stdio.h>
#include "mythread.h"
#include <ucontext.h>
#include "mythreadlib.h"

#define DEBUG


Node *ready_q;
Node *block_q;
static int gl_thread_id;
ucontext_t *context_old;


// Create a new thread.
MyThread MyThreadCreate(void(*start_funct)(void *), void *args){
	#ifdef DEBUG
		printf(COLOR_ON "FUNC: '%s'\n" COLOR_OFF, __func__);
	#endif
	
	#ifdef DEBUG
		q_print(ready_q,0);
	#endif
	
	int rc;
	ucontext_t *context_new;
	_MyThread *new_thread;
	
	new_thread = (_MyThread*)malloc(sizeof(_MyThread));
	context_new = (ucontext_t*)malloc(sizeof(ucontext_t));
	char * new_stack = (char*)malloc(STACK_SIZE);
	
	rc = getcontext(context_new);
    context_new->uc_link          = NULL;
    context_new->uc_stack.ss_sp   = new_stack;
    context_new->uc_stack.ss_size = STACK_SIZE;
    
    makecontext(context_new, (void (*)(void)) start_funct, args);
	
	new_thread->context_t = context_new;
	new_thread->id = (gl_thread_id++);
	new_thread -> parent = ready_q -> this_t;
	
	/* Add new thread to list of parent's children */
	_MyThread *last_child = ready_q->this_t->child;
	if(!last_child){
		ready_q -> this_t -> child = new_thread;
	}else{
		while(last_child->next_sib){
			last_child = last_child->next_sib;
		}
		last_child->next_sib = new_thread;
	}

	
	q_insert(new_thread, ready_q);

	return (MyThread)(void *)new_thread;
}

// Yield invoking thread
void MyThreadYield(void){

	#ifdef DEBUG
		printf( COLOR_ON "FUNC: '%s'\n" COLOR_OFF, __func__);
	#endif
	
	#ifdef DEBUG
		q_print(ready_q,0);
	#endif
	// Remove head and put at the tail 
	_MyThread *t;
	Node * temp = ready_q;
	ready_q = ready_q -> next;
	t = temp -> this_t;
	q_insert(t,ready_q);
	swapcontext(t->context_t,ready_q -> this_t -> context_t);
}

// Join with a child thread
int MyThreadJoin(MyThread thread){
	#ifdef DEBUG
		printf("FUNC: '%s'\n", __func__);
	#endif
}

// Join with all children
void MyThreadJoinAll(void){
	#ifdef DEBUG
		printf("FUNC: '%s'\n", __func__);
	#endif
}

// Terminate invoking thread
void MyThreadExit(void){
	#ifdef DEBUG
		printf( COLOR_ON "FUNC: '%s'\n" COLOR_OFF, __func__);
	#endif

	/* Remove element from ready q */
	Node * temp = ready_q;
	ready_q = ready_q -> next;
	
	/* Check if any parents waiting, say good bye to them */
	
	/* Set Context */
	if(ready_q -> this_t){
		/* Free Memory */
		free(temp);
		
		/* Change context */
		setcontext(ready_q -> this_t -> context_t);
	}else{ 
		/* Go back to main context */
		setcontext(context_old);
	}
}

// ****** SEMAPHORE OPERATIONS ****** 
// Create a semaphore
MySemaphore MySemaphoreInit(int initialValue){
}

// Signal a semaphore
void MySemaphoreSignal(MySemaphore sem){
}

// Wait on a semaphore
void MySemaphoreWait(MySemaphore sem){
}

// Destroy on a semaphore
int MySemaphoreDestroy(MySemaphore sem){
}

// ****** CALLS ONLY FOR UNIX PROCESS ****** 
// Create the "main" thread
void MyThreadInit(void(*start_funct)(void *), void *args){
	#ifdef DEBUG
		printf( COLOR_ON "FUNC: '%s'\n" COLOR_OFF, __func__);
	#endif
	
	int rc;
	_MyThread *main_thread;
	ucontext_t *context_new;
	
	main_thread = (_MyThread*)malloc(sizeof(_MyThread));
	context_new = (ucontext_t*)malloc(sizeof(ucontext_t));
	context_old = (ucontext_t*)malloc(sizeof(ucontext_t));
	ready_q = q_create();
	block_q = q_create();
	char * main_stack = (char*)malloc(STACK_SIZE);

	
	rc = getcontext(context_new);
    context_new->uc_link          = NULL;
    context_new->uc_stack.ss_sp   = main_stack;
    context_new->uc_stack.ss_size = STACK_SIZE;
    
    makecontext(context_new, (void (*)(void)) start_funct, args);
	
	main_thread->context_t = context_new;
	main_thread->id = (gl_thread_id++);
	main_thread -> parent = NULL;
	q_insert(main_thread, ready_q);

	rc = swapcontext(context_old,context_new);

	free(main_thread);
	free(context_new);
	free(context_old);
	free(ready_q);
	free(block_q);
	free(main_stack);
}
















