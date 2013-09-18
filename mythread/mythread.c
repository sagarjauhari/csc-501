#include <stdlib.h>
#include <stdio.h>
#include "mythread.h"
#include <ucontext.h>
#include "mythreadlib.h"

//#define DEBUG


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
		q_print(block_q,1);
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
    
    makecontext(context_new, (void (*)(void)) start_funct, 1,args);
	
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
		printf(COLOR_ON "FUNC: '%s'\n" COLOR_OFF, __func__);
	#endif
	
	int th_to_join_is_alive=0;
	/*
	See if thread for which we're waiting is present atleast
	on RQ or BQ. If not, then just insert calling thread in
	ready queue
	*/
	

	//Check on BQ
	Node * bq_temp = block_q;
	while(bq_temp -> this_t){
		if(bq_temp -> this_t -> context_t == ((_MyThread*)thread) -> context_t){
			th_to_join_is_alive=1;
			break;
		}
		bq_temp = bq_temp -> next;
	}
	
	//Check on RQ
	Node * rq_temp = ready_q;
	if(!th_to_join_is_alive){
		while(rq_temp -> this_t){
			if(rq_temp -> this_t -> context_t == ((_MyThread*)thread) -> context_t){
				th_to_join_is_alive=1;
				break;
			}
			rq_temp = rq_temp -> next;
		}
	}
	
	if(th_to_join_is_alive){
		#ifdef DEBUG
			printf(COLOR_ON "\tThread to be joined IS alive\n" COLOR_OFF);
		#endif
		
		/* Set blocked on join flag, coz we're actually blocking now'*/
		ready_q -> this_t -> blocked_on_join = 1;
		
		/* Remove from head of ready Q, add to BQ*/
		rq_temp = ready_q;
		_MyThread * t = rq_temp -> this_t;
		ready_q = ready_q -> next;
		q_insert(t, block_q);
		
		#ifdef DEBUG
			q_print(block_q,1);
		#endif
		
		swapcontext(t->context_t, ready_q->this_t->context_t);
	}else{
		/* just continue*/
		#ifdef DEBUG
			printf(COLOR_ON "\tThread to be joined NOT alive\n" COLOR_OFF);
		#endif
		return 0;
	}
	
	
	
}

// Join with all children
void MyThreadJoinAll(void){
	#ifdef DEBUG
		printf(COLOR_ON "FUNC: '%s'\n" COLOR_OFF, __func__);
		q_print(ready_q,0);
	#endif
	
	Node * rq_temp;

	// Find number of alive threads
	int num_alive_children = 0;
	_MyThread * child_temp_t;
	child_temp_t = ready_q -> this_t -> child;
	while(child_temp_t){
		if(!child_temp_t -> is_dead) num_alive_children++;					
		child_temp_t = child_temp_t -> next_sib;
	}
	
	#ifdef DEBUG
		printf(COLOR_ON "\t# of alive children: %d\n" COLOR_OFF, num_alive_children);
	#endif
	
	if(num_alive_children > 0){
		ready_q -> this_t -> blocked_on_join_all = 1;
		
		/* Remove from head of ready Q, add to BQ*/
		rq_temp = ready_q;
		_MyThread * t = rq_temp -> this_t;
		ready_q = ready_q -> next;
		q_insert(t, block_q);
		
		#ifdef DEBUG
			q_print(block_q,1);
		#endif
		
		swapcontext(t->context_t, ready_q->this_t->context_t);
	}
}

// Terminate invoking thread
void MyThreadExit(void){
	#ifdef DEBUG
		printf( COLOR_ON "FUNC: '%s'\n" COLOR_OFF, __func__);
	#endif

	/* Remove element from ready q */
	Node * old_head = ready_q;
	ready_q = ready_q -> next;
	Node * to_free;
	
	/* Check if any parent waiting, say good bye to them.
	   If parent waiting, bring it to ready Q */
	Node * bq_temp = block_q;
	_MyThread * child_temp;
	_MyThread * child_temp_t;
	int found_context_flag = 0;
	while(bq_temp -> this_t){
		child_temp = bq_temp -> this_t -> child;
		while(child_temp){
			if((!old_head -> this_t -> is_dead) && 
				child_temp -> context_t == old_head -> this_t -> context_t){
				/* Found context match */
				#ifdef DEBUG
					printf(COLOR_ON "\tFound context!\n" COLOR_OFF);
				#endif
				found_context_flag=1;
				if(bq_temp -> this_t -> blocked_on_join){ //JOIN
					// insert to head of ready Q
					bq_temp -> this_t -> blocked_on_join=0;
					q_insert(bq_temp -> this_t, ready_q);

					// remove thread from parent's child list
					old_head -> this_t -> is_dead = 1;
					
					//free node of BQ
					bq_temp -> this_t = bq_temp -> next -> this_t;
					to_free = bq_temp -> next;
					bq_temp -> next = bq_temp -> next -> next;
					free(to_free);
				}else if(bq_temp -> this_t -> blocked_on_join_all){//JOIN ALL
					// remove thread from parent's child list
					old_head -> this_t -> is_dead = 1;
					
					// find number of alive threads
					int num_alive_children = 0;
					
					child_temp_t = bq_temp -> this_t -> child;
					while(child_temp_t){
						if(!child_temp_t -> is_dead) num_alive_children++;					
						child_temp_t = child_temp_t -> next_sib;
					}
					
					if(num_alive_children==0){
						// insert to head of ready Q
						bq_temp -> this_t -> blocked_on_join_all=0;
						q_insert(bq_temp -> this_t, ready_q);
					
						//free node of BQ
						bq_temp -> this_t = bq_temp -> next -> this_t;
						to_free = bq_temp -> next;
						bq_temp -> next = bq_temp -> next -> next;
						free(to_free);
					}else{
						
					}
				}else{
					#ifdef DEBUG
						printf("\tError: Thread was in blocked Q with no join flags set!\n");
					#endif
				}
				break;
			}
			child_temp = child_temp -> next_sib;
		}
		if(found_context_flag){
			break;
		}
		bq_temp = bq_temp -> next;
	}
	
	/* Set Context */
	if(ready_q -> this_t){
		/* Free Memory */
		free(old_head);
		
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
    
    makecontext(context_new, (void (*)(void)) start_funct, 1, args);
	
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
















