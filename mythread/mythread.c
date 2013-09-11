#include <stdlib.h>
#include <stdio.h>
#include "mythread.h"
#include <ucontext.h>
#include "mythreadlib.h"

#define DEBUG


Node *ready_q;
Node *block_q;
int gl_thread_id;


// Create a new thread.
MyThread MyThreadCreate(void(*start_funct)(void *), void *args){
#ifdef DEBUG
	printf(COLOR_ON "FUNC: '%s'\n" COLOR_OFF, __func__);
#endif
	
	int rc;
	ucontext_t *context_new;
	ucontext_t *context_old;
	_MyThread *new_thread;
	
	new_thread = (_MyThread*)malloc(sizeof(_MyThread));
	context_new = (ucontext_t*)malloc(sizeof(ucontext_t));
	char new_stack[STACK_SIZE];
	
	rc = getcontext(context_new);
    context_new->uc_link          = NULL;
    context_new->uc_stack.ss_sp   = new_stack;
    context_new->uc_stack.ss_size = sizeof(new_stack);
    
    makecontext(context_new, (void (*)(void)) start_funct, args);
	
	new_thread->context_t = context_new;
	new_thread->id = (gl_thread_id++);
	q_insert(new_thread, ready_q);

#ifdef DEBUG
	q_print(ready_q,0);
#endif

	return (MyThread)(void *)new_thread;
}

// Yield invoking thread
void MyThreadYield(void){
#ifdef DEBUG
	printf(COLOR_ON "FUNC: '%s'\n" COLOR_OFF, __func__);
#endif
	
	// Remove head and put at tail
	_MyThread *t;
	Node * temp = ready_q;
	ready_q = ready_q -> next;
	t = temp -> this_t;
	q_insert(t,ready_q);
	free(temp);

	

#ifdef DEBUG
	q_print(ready_q,0);
#endif

	
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
	printf(COLOR_ON "FUNC: '%s'\n" COLOR_OFF, __func__);
#endif
	
	int rc;
	ucontext_t *context_new;
	ucontext_t *context_old;
	_MyThread *main_thread;
	
	main_thread = (_MyThread*)malloc(sizeof(_MyThread));
	context_new = (ucontext_t*)malloc(sizeof(ucontext_t));
	context_old = (ucontext_t*)malloc(sizeof(ucontext_t));
	ready_q = q_create();
	block_q = q_create();
	char main_stack[STACK_SIZE]; //main thread stack
	
	rc = getcontext(context_new);
    context_new->uc_link          = context_old;
    context_new->uc_stack.ss_sp   = main_stack;
    context_new->uc_stack.ss_size = sizeof(main_stack);
    
    makecontext(context_new, (void (*)(void)) start_funct, args);
	
	main_thread->context_t = context_new;
	main_thread->id = (gl_thread_id++);
	q_insert(main_thread, ready_q);

#ifdef DEBUG
	q_print(ready_q,0);
#endif

	rc = swapcontext(context_old,context_new);
}








