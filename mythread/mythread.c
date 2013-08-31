#include <stdlib.h>
#include "mythread.h"
#include <ucontext.h>
#include "threadq.h"
#include <pthread.h> //TODO: Remove library

Node* head_q;

typedef struct _MyThread_{
	ucontext_t pthread;
} _MyThread;

// Create a new thread.
MyThread MyThreadCreate(void(*start_funct)(void *), void *args){
	ucontext_t new_context;
	
}

// Yield invoking thread
void MyThreadYield(void){

}

// Join with a child thread
int MyThreadJoin(MyThread thread){

}

// Join with all children
void MyThreadJoinAll(void){

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
	pthread_t pth;
	
	head_q = create_q();
	pthread_create(&pth, NULL, (void *)start_funct, args);
	pthread_join(pth,NULL);
}
