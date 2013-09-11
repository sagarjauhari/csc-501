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
	ucontext_t context_new, context_old;
	_MyThread main_thread;						//Initialize mainThread
	
	ready_q = q_create();
	block_q = q_create();
	
	main_thread.context_t = &context_new;
	main_thread.id = (++gl_thread_id);
	q_insert(&main_thread, ready_q);
	q_print(ready_q,0);
	q_remove(ready_q);
	q_print(ready_q,0);
}








