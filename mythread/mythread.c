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
	printf("FUNC: '%s'\n", __func__);
#endif
	_MyThread *mythread;
	ucontext_t context_new, context_old;
	
	
	return (MyThread)(void *)mythread;
}

// Yield invoking thread
void MyThreadYield(void){
#ifdef DEBUG
	printf("FUNC: '%s'\n", __func__);
#endif
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
	printf("FUNC: '%s'\n", __func__);
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
	
	getcontext(context_new);
    context_new->uc_link          = context_old;
    context_new->uc_stack.ss_sp   = main_stack;
    context_new->uc_stack.ss_size = sizeof(main_stack);
    
    makecontext(context_new, (void (*)(void)) start_funct, args);
	
	main_thread->context_t = context_new;
	main_thread->id = (++gl_thread_id);
	q_insert(&main_thread, ready_q);

#ifdef DEBUG
	q_print(ready_q,0);
#endif

	swapcontext(context_old,context_new);
}








